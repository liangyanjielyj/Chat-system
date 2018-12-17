#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sqlite3.h>
#include "../MyTalk/protocal.h"

#include <string.h>

#include <signal.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */

int remember_addr(struct jizhudizhi_st *z, struct sockaddr_in *a, int sd)
{
	int ret;

	sqlite3 *db;
	char *sql = "select * from addr_table where count=?";
	char sql1[256];
	char *sql2;
	struct sqlite3_stmt *stmt;
	struct liaotian_st haoyou_item;


	ret = sqlite3_open("./talk.sqlite", &db);
	if (ret != SQLITE_OK) {
		perror("sqlite3_open");
		return -1;
	}

	ret = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (ret != SQLITE_OK) {
		goto prepare_error;
	}	

	sqlite3_bind_text(stmt, 1, z->count, -1, NULL);

	ret = sqlite3_step(stmt);
	if (ret == SQLITE_ROW) {
		sql2 = "update addr_table set addr=? where count=?";
	}		

	if (ret == SQLITE_DONE) {
		sql2 = "insert into addr_table(addr, count) values(?,?)";
	}

	sqlite3_finalize(stmt);

	ret = sqlite3_prepare_v2(db, sql2, -1, &stmt, NULL);
	if (ret != SQLITE_OK) {
		goto prepare_error;
	}	

	sqlite3_bind_blob(stmt, 1, a, sizeof(*a), NULL);
	sqlite3_bind_text(stmt, 2, z->count, -1, NULL);


	ret = sqlite3_step(stmt);
	if (ret != SQLITE_DONE) {
		goto step_error;
	}		

	sqlite3_finalize(stmt);

	sprintf(sql1, "select * from table_%s", z->count);	
	ret = sqlite3_prepare_v2(db, sql1, -1, &stmt, NULL);
	if (ret != SQLITE_OK) {
		goto prepare_error;
	}	

	while (1) {
		ret = sqlite3_step(stmt);
		if (ret != SQLITE_ROW) {
			break;
		}		
		sprintf(haoyou_item.msg, "%s", sqlite3_column_text(stmt, 1));
		haoyou_item.status = HAOYOU_ITEM;
		sendto(sd, (void *)&haoyou_item, sizeof(haoyou_item), 0, (void *)a, sizeof(*a));
	}

	sqlite3_close(db);
	
	return 0;
step_error:
	sqlite3_finalize(stmt);
prepare_error:
	sqlite3_close(db);
	return -1;
}

int main(void)
{
	int sd;
	struct jizhudizhi_st jizhudizhi;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	int ret;
	pid_t pid;
	socklen_t addr_len = sizeof(client_addr);
	sqlite3 *db;
	char *sql = "create table if not exists addr_table(no integer primary key autoincrement not null, count text not null, addr blob not null)";

	struct sigaction act;

        act.sa_flags = SA_NOCLDWAIT;
        sigaction(SIGCHLD, &act, NULL);

	ret = sqlite3_open("./talk.sqlite", &db);
	if (ret != SQLITE_OK) {
		perror("sqlite3_open");
		exit(1);
	}

	ret = sqlite3_exec(db, sql, NULL, NULL, NULL);
	if (ret != SQLITE_OK) {
		perror("sqlite3_exec");
		exit(1);
	}

	sqlite3_close(db);
	
	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sd < 0) {
		perror("socket");
		exit(1);
	}	

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(JIZHUDIZHI_SERVER_PORT);	
	server_addr.sin_addr.s_addr = INADDR_ANY;

	ret = bind(sd, (void *)&server_addr, sizeof(server_addr));
	if (ret < 0) {
		perror("bind");
		exit(1);
	}

	while (1) {
		ret = recvfrom(sd, (void *)&jizhudizhi, sizeof(jizhudizhi), 0, (void *)&client_addr, &addr_len);
		if (ret < 0) {
			perror("recvfrom");
			continue;
		}
		
		pid = fork();
		if (pid < 0) {
			perror("fork");
			continue;
		}

		if (pid == 0) {
			ret = remember_addr(&jizhudizhi, &client_addr, sd);
			if (ret < 0) {
				jizhudizhi.status = JIZHUDIZHI_STATUS_ERROR;
			} else {
				jizhudizhi.status = JIZHUDIZHI_STATUS_OK;
			}
			exit(0);
		}	
	}	

	

	return 0;
}







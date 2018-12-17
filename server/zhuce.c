#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sqlite3.h>
#include "../MyTalk/protocal.h"

#include <signal.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */

int user_register(struct zhuce_st *z)
{
	int ret;

	sqlite3 *db;
	char *sql = "select * from register_table where count=?";
	char sql2[256];
	char *sql1 = "insert into register_table(count, name, password,mibao, sex) values(?,?,?,?,?)";
	struct sqlite3_stmt *stmt;

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
	if (ret != SQLITE_DONE) {
		goto step_error;
	}		

	sqlite3_finalize(stmt);

	//char sql1 = "insert into register_table(count, name, password, sex) values(?,?,?,?)";
	ret = sqlite3_prepare_v2(db, sql1, -1, &stmt, NULL);
	if (ret != SQLITE_OK) {
		goto prepare_error;
	}	

	sqlite3_bind_text(stmt, 1, z->count, -1, NULL);
	sqlite3_bind_text(stmt, 2, z->name, -1, NULL);
	sqlite3_bind_text(stmt, 3, z->password, -1, NULL);
	sqlite3_bind_text(stmt, 4, z->mibao,-1,NULL);
	sqlite3_bind_int(stmt, 5, z->sex);

	ret = sqlite3_step(stmt);
	if (ret != SQLITE_DONE) {
		goto step_error;
	}		
	
	sqlite3_finalize(stmt);

	sprintf(sql2, "create table if not exists table_%s(no integer primary key autoincrement not null, count text not null)", z->count);
	sqlite3_exec(db, sql2, NULL, NULL, NULL);

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
	struct zhuce_st zhuce;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	int ret;
	pid_t pid;
	socklen_t addr_len = sizeof(client_addr);
	sqlite3 *db;
	char *sql = "create table if not exists register_table(no integer primary key autoincrement not null, count text not null, name text, password text, mibao text, sex integer)";

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
	server_addr.sin_port = htons(ZHUCE_SERVER_PORT);	
	server_addr.sin_addr.s_addr = INADDR_ANY;

	ret = bind(sd, (void *)&server_addr, sizeof(server_addr));
	if (ret < 0) {
		perror("bind");
		exit(1);
	}

	while (1) {
		ret = recvfrom(sd, (void *)&zhuce, sizeof(zhuce), 0, (void *)&client_addr, &addr_len);
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
			ret = user_register(&zhuce);
			if (ret < 0) {
				zhuce.status = ZHUCE_STATUS_ERROR;
			} else {
				zhuce.status = ZHUCE_STATUS_OK;
			}
			sendto(sd, (void *)&zhuce, sizeof(zhuce), 0, (void *)&client_addr, sizeof(client_addr));
			exit(0);
		}	
	}	

	

	return 0;
}







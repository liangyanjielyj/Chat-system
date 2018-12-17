#ifndef PROTOCAL_H
#define PROTOCAL_H

#define DEFAULT_SERVER_IP               "192.168.191.4"

//<==================register================>
#define COUNT_SIZE                          32
#define ZHUCE_STATUS_OK                 0
#define ZHUCE_STATUS_ERROR          1
#define ZHUCE_SERVER_IP                 DEFAULT_SERVER_IP
#define ZHUCE_SERVER_PORT           1234

#define FEMALE                      0
#define MALE                        1

struct zhuce_st {
    char count[COUNT_SIZE];
    char name[COUNT_SIZE];
    char password[COUNT_SIZE];
    char mibao[COUNT_SIZE];
    int sex;
    int status;
};
//zhuce table
//id(integer, count text, name text, passwd text)

//<==================login================>
#define DENGLU_STATUS_OK                 0
#define DENGLU_STATUS_ERROR          1
#define DENGLU_SERVER_IP                 DEFAULT_SERVER_IP
#define DENGLU_SERVER_PORT           1235

struct denglu_st {
    char count[COUNT_SIZE];
    char password[COUNT_SIZE];
    int status;
};

//<=================know address===========>
#define JIZHUDIZHI_SERVER_IP                "192.168.191.4"
#define JIZHUDIZHI_SERVER_PORT          1236
#define JIZHUDIZHI_STATUS_OK                0
#define JIZHUDIZHI_STATUS_ERROR         1

struct jizhudizhi_st {
   char count[COUNT_SIZE];
   int status;
};

//denglu table
//denglu(id integer, count text, addr blob)

//<==================addFriend================>
#define TIANJIAHAOYOU_STATUS_OK                 0
#define TIANJIAHAOYOU_STATUS_ERROR          1
#define TIANJIAHAOYOU_SERVER_IP                 DEFAULT_SERVER_IP
#define TIANJIAHAOYOU_SERVER_PORT           1237
#define TIANJIAHAOYOU_STATUS_FRIEND     2
struct tianjiahaoyou_st {
    char src_count[COUNT_SIZE];
    char count[COUNT_SIZE];
    char name[COUNT_SIZE];//server write
    int status;
};

//hy_xxx table
//hy_xxx(id integer, count text, name text)

//<==================talk================>
#define LIAOTIAN_STATUS_OK                 0
#define LIAOTIAN_STATUS_ERROR          1
#define LIAOTIAN_SERVER_IP                 DEFAULT_SERVER_IP
#define LIAOTIAN_SERVER_PORT           1238
#define MSG_COUNT_SIZE                      1024

#define LIAOTIAN_CLIENT_PORT            8888

#define HAOYOU_ITEM                             2

struct liaotian_st {
    char src_count[COUNT_SIZE];
    char dst_count[COUNT_SIZE];
    char msg[MSG_COUNT_SIZE];
    int status;
};
#endif // PROTOCAL_H

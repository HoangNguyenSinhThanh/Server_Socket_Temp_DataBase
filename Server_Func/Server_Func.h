#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

typedef struct tm server_Time;

typedef struct {
    uint8_t id;
    char  name[24];
    server_Time date_birth;
    char  login_name[20];
    char  passwordHashed[32];
} server_User;

typedef struct list_User{
    server_User user;
    struct list_User * tail;
} server_UserInfo;


bool server_CompareName(char * name1, char * name2);
bool server_ComparePassword(char * name1, char * name2);
bool server_CheckLoginNameUnique(char *loginname);
bool server_CheckUserWithLoginName(char *loginName, char * passHashed);
void server_SignUp();
void server_LogIn();
void server_FindUserWithName();
void server_ListUser();
bool server_CheckEmptyList();

void server_SignUp_txt();
void server_LogIn_txt();
void server_FindUserWithName_txt();
void server_ListUser_txt();

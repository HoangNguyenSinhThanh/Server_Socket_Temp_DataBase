#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <openssl/sha.h>
#include "Server_Func.h"

static uint8_t server_ID = 0;
server_UserInfo * head = NULL;
server_UserInfo * current = NULL;

void server_SignUp()
{
    server_UserInfo *signup_User = (server_UserInfo *)malloc(sizeof(server_UserInfo));
    char passWord[32];
    char login_name[20];
    bool uniqueLoginName = false;

    if(head == NULL)
    {
        head = signup_User;
        current = signup_User;
        current->tail = NULL;
    }
    else{
        current->tail = signup_User;
        current = signup_User;
        current->tail = NULL;
    }
    printf("--------------------------------------------------------------------------------------------------\n");
    printf("----------------------------------Welcome to Server Provip!!!!!----------------------------------\n");
    printf("-----------------------------------Fill your information----------------------------------------\n");
    printf("\n Name: ");
    scanf("%s", signup_User->user.name);

    printf("\n User name for login: ");
    scanf("%s", login_name);
    uniqueLoginName = server_CheckLoginNameUnique(login_name);
    while(uniqueLoginName)
    {
        printf("Login name existed, please enter other login name: ");
        scanf("%s", login_name);
        uniqueLoginName = server_CheckLoginNameUnique(login_name);
    }
    strcpy(signup_User->user.login_name,login_name);
    printf("\n Password: ");
    scanf("%s", passWord);
    SHA256((unsigned char*)passWord, strlen(passWord), signup_User->user.passwordHashed);
    signup_User->user.id = server_ID;
    server_ID++;
}

void server_LogIn()
{
    printf("\n---------------------------------------LOGIN------------------------------------------\n");
    char login_name[20];
    char passWord[32];
    unsigned char tempLoginHashed[32] = {0};
    unsigned char passHashed[32];
    bool login_name_exist = false;
    bool check_password = false;
    if(server_CheckEmptyList())
    {
        printf("\nList user is empty!");
        return;
    }
    printf("Enter your login name: ");
    scanf("%s", login_name);
    login_name_exist = server_CheckUserWithLoginName(login_name, passHashed);
    while(!login_name_exist){
        printf("Login name not existed! Re-enter login name: ");
        scanf("%s", login_name);
        login_name_exist = server_CheckUserWithLoginName(login_name, passHashed);
    }
    //printf("Hashed Pw: %s", passHashed);

    printf("\nPassword: ");
    scanf("%s", passWord);
    SHA256((unsigned char*)passWord, strlen(passWord), tempLoginHashed);
    //printf("Hashed Pw: %s", tempLoginHashed);
    check_password = server_ComparePassword(tempLoginHashed, passHashed);
    while(!check_password){
        printf("\nPassword is incorrect! Please enter again your pass: ");
        scanf("%s", passWord);
        SHA256((unsigned char*)passWord, strlen(passWord), tempLoginHashed);
        check_password = server_ComparePassword(tempLoginHashed, passHashed);
    }
    printf("\n LOGGED IN SUCCESSFULLY!!!!!!!!!!!!!!!!!!");
}

void server_FindUserWithName()
{
    printf("\n-----------------------------------Search user Info----------------------------------------\n");
    char name[20];
    uint8_t exist_UserCount = 0;
    bool end_list = false;
    printf("\nEnter user name you find: ");
    scanf("%s", name);

    server_UserInfo * pointer_Find = head;

    while(!end_list)
    {
        if(pointer_Find == NULL)
        {
            end_list = true;
        }
        else
        {
            if(server_CompareName(pointer_Find->user.name, name)){
                exist_UserCount++;
                printf("Login name: %s and ID: %d", pointer_Find->user.login_name,pointer_Find->user.id);
            }
            pointer_Find = pointer_Find->tail;
            if(pointer_Find == NULL)
            {
                end_list = true;
            }
        }
    }
    if(exist_UserCount == 0)
    {
        printf("There is no name like that!!");
    }
}

void server_ListUser()
{
    server_UserInfo * pointer_Find = head;
    bool end_list = false;

    printf("\n-----------------------------------List of User----------------------------------------\n");

    while(!end_list)
    {
        if(pointer_Find == NULL)
        {
            end_list = true;
        }
        else
        {
            printf("\nLogin name: %s  -  ID: %d .", pointer_Find->user.login_name,pointer_Find->user.id);
            pointer_Find = pointer_Find->tail;
            if(pointer_Find == NULL)
            {
                end_list = true;
            }
        }
    }

    printf("\nEnd of list!!");
}

bool server_CompareName(char * name1, char * name2)
{
    bool compare_Result = false;
    if(strlen(name1) != strlen(name2))
    {
        compare_Result = false;
    }
    else
    {
        for(uint8_t i = 0; i < strlen(name1); i++)
        {
            if(name1[i] != name2[i]){
                compare_Result = false;
                return compare_Result;
            }
            else{
                compare_Result = true;
            }
        }
    }
    return compare_Result;
}

bool server_ComparePassword(char * name1, char * name2)
{
    bool compare_Result = false;

    for(uint8_t i = 0; i < 32; i++)
    {
        if(name1[i] != name2[i]){
            compare_Result = false;
            return compare_Result;
        }
        else{
            compare_Result = true;
        }
    }

    return compare_Result;
}

bool server_CheckLoginNameUnique(char *loginname){
    bool exist_UserLogin = false;
    bool end_list = false;

    server_UserInfo * pointer_Find = head;

    while(!end_list)
    {
        if(pointer_Find == NULL)
        {
            end_list = true;
        }
        else
        {
            if(server_CompareName(pointer_Find->user.login_name, loginname)){
                exist_UserLogin = true;
                return exist_UserLogin;
            }
            pointer_Find = pointer_Find->tail;
            if(pointer_Find == NULL)
            {
                end_list = true;
            }
        }
    }
    return exist_UserLogin;
}

bool server_CheckUserWithLoginName(char *loginName, char *passHashed)
{
    bool exist_UserAccCount = false;
    bool end_list = false;
    server_UserInfo * pointer_Find = head;

    while(!end_list)
    {
        if(pointer_Find == NULL)
        {
            end_list = true;
        }
        else
        {
            if(server_CompareName(pointer_Find->user.login_name, loginName)){
                exist_UserAccCount = true;
                memcpy(passHashed, pointer_Find->user.passwordHashed, strlen(pointer_Find->user.passwordHashed));
                return exist_UserAccCount;
            }
            pointer_Find = pointer_Find->tail;
            if(pointer_Find == NULL)
            {
                end_list = true;
            }
        }
    }
    return exist_UserAccCount;
}

bool server_CheckEmptyList()
{
    bool checkEmpList = true;
    if(head != NULL)
    {
        checkEmpList = false;
    }
    return checkEmpList;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include "Server_Func/Server_Func.h"

#define VERSION_LINKLIST
//#define VERSION_TXTDATABASE

struct tm *localTime;
time_t rawTime;

void server_PrintGuideLine(){
    printf("\n--------------------------DATABASE_SERVER-------------------------------\n");
    printf("\n-------------------------------Guide table---------------------------------------\n");
    printf("                Type 'a' to sign up\n");
    printf("                Type 'b' to log in\n");
    printf("                Type 'c' to find user\n");
    printf("                Type 'd' to list all users\n");
}

int main()
{
    time(&rawTime);
    localTime = localtime(&rawTime);
    printf("Time %d - %d - %d\n", localTime->tm_mday, localTime->tm_mon + 1, localTime->tm_year + 1900);
    server_PrintGuideLine();

    char cha_Button = '0';

    while(cha_Button != 'q'){
        cha_Button = getch();

        switch(cha_Button){
            case 'a':
                server_PrintGuideLine();
                #ifdef VERSION_LINKLIST
                    server_SignUp();
                #elifdef VERSION_TXTDATABASE
                    server_SignUp_txt();
                #endif
                break;
            case 'b':
                server_PrintGuideLine();
                #ifdef VERSION_LINKLIST
                    server_LogIn();
                #elifdef VERSION_TXTDATABASE
                    server_LogIn_txt();
                #endif
                break;
            case 'c':
                server_PrintGuideLine();
                #ifdef VERSION_LINKLIST
                    server_FindUserWithName();
                #elifdef VERSION_TXTDATABASE
                    server_FindUserWithName_txt();
                #endif
                break;
            case 'd':
                server_PrintGuideLine();
                #ifdef VERSION_LINKLIST
                    server_ListUser();
                #elifdef VERSION_TXTDATABASE
                    server_ListUser_txt();
                #endif
                break;
            case 'q':
                system("cls");
                printf("\nEXIT\n");
                break;
            default:
                printf("\nFollow the guide!\n");
                break;
        }
    }
    return 0;
}

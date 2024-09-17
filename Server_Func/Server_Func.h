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


/** \brief Function is used for user to sign up account- Linked list
 */
void server_SignUp();

/** \brief Function is used for user to log in- Linked list
 */
void server_LogIn();

/** \brief Function is used for user to find user name- Linked list
 */
void server_FindUserWithName();

/** \brief Function is used for user to list user- Linked list
 */
void server_ListUser();

/** \brief Function is used for checking whether list is empty or not- Linked list
 *
 * \return result of checking
 *
 */
bool server_CheckEmptyList();

/** \brief Function is used for comparing 2 names
 *
 * \param name1 the first name
 * \param name2 the second name
 * \return result of checking
 *
 */
bool server_CompareName(char * name1, char * name2);

/** \brief Function is used for comparing 2 passwords
 *
 * \param pass1
 * \param pass2
 * \return result of checking
 *
 */
bool server_ComparePassword(char * pass1, char * pass2);
bool server_CheckLoginNameUnique(char *loginname);
bool server_CheckUserWithLoginName(char *loginName, char * passHashed);

/** \brief Sign up user information to database
 */
void server_SignUp_DataCSV();

/** \brief Function for login to server
 */
void server_LogIn_DataCSV();

/** \brief Find user with name(to be define)
 */
void server_FindUserWithName_DataCSV();

/** \brief Function to list all user signed in server
 */
void server_ListUser_DataCSV();

/** \brief
 *
 * \param loginname string of login name
 * \param f pointer to file
 * \param line char array to save all data in a line
 * \return result of checking
 *
 */
bool server_CheckLoginNameUnique_DataCSV(char *loginname, FILE *f, char *line);
bool server_CheckEmptyList_DataCSV(FILE *f);
bool server_CheckUserWithLoginName_DataCSV(char *loginName, char *passHashed, FILE *f, char * buffer_line);

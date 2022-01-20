/*****************************************************************
//
//  NAME:        Yong-Sung Masuda 
//
//  PROJECT:     1
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        October 21, 2021 
//
//  FILE:        user_interface.c
//
//  DESCRIPTION: Contains the driver and user interface functions
//               for PROJECT 1, the banking database program.
//               Calls functions defined in database.c
// 
//
//
****************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "record.h"
#include "database.h"

int debugmode = 0;

void getAddress();

void flushBuffer();

/*****************************************************************
//
//  Function name: main
//
//  DESCRIPTION:   This is the entry point for the program homework3b
//                 It serves as the main user interface and calls
//                 functions defined in database.c as well as 2
//                 helper functions getAddress and flushBuffer. 
//
//  Parameters:    int argc, char *argv[]
//
//  
//  Return values: int
//
****************************************************************/

int main(int argc, char *argv[])
{
    int i = 0;
    int invalidArg = 0;
    int exitEarly = 0;
    int menuOption = 0;
    int endLoop = 0;
    int accountno = 0;
    char accountnoString[25];
    char name[25];
    char address[50];
    int addressLength = 50;
    char utilityString[50];
    struct record * start = NULL;
    char userInput[25];
    size_t inputLength;
    char option1[] = "add";
    char option2[] = "printall";
    char option3[] = "find";
    char option4[] = "delete";
    char option5[] = "quit";

    if(argc == 2)
    {
        if(strcmp(argv[1],"debug") == 0)
        {
            debugmode = 1;
        }
        else
        {
            printf("%s is an invalid argument. Exiting program.\n", argv[1]);
            exitEarly = 1;
        }
    }
    else if(argc > 2)
    {
        for(i = 1; i < argc; i++)
        {
            if(strcmp(argv[i],"debug") != 0)
            {
                invalidArg++;
            }
        }
        if(invalidArg == 0)
        {
            printf("Why have you typed debug multiple times?\n");
        }
        if(invalidArg == 1)
        {
            for(i = 1; i < argc; i++)
            {
                if(strcmp(argv[i],"debug") != 0)
                {
                    printf("%s is an invalid argument. Exiting program.\n", argv[i]);
                }
            }
        }
        if(invalidArg > 1)
        {
            for(i = 1; i < argc; i++)
            {
                if(strcmp(argv[i],"debug") != 0)
                {
                    printf("%s\n", argv[i]);
                }
            }
            printf("The above arguments are invalid. Exiting program.\n");
        }
        exitEarly = 1;
    }

    if(exitEarly == 0)
    {
        readfile(&start, "data.txt");
        printf("\n-------------------------------------------------------------\n");
        printf("| Welcome to the user interface for the database of bank x. |\n");
        printf("-------------------------------------------------------------\n");

        do
        {
            menuOption = 0;
            printf("\nType all or part of a menu option and hit 'Enter'\n\n");
            printf("%s:      Add a record to the database.\n", option1);
            printf("%s: Print all records in the database.\n", option2);
            printf("%s:     Find a record in the database.\n", option3);
            printf("%s:   Delete a record from the database.\n", option4);
            printf("%s:     Quit this program.\n", option5);
            do
            {
                fgets(userInput, 25, stdin);
                if(userInput[strlen(userInput) - 1] != '\n')
                {
                    flushBuffer(userInput);
                }
            }
            while(strcmp(userInput, "\n") == 0);
            
            userInput[strlen(userInput) - 1] = '\0';
            inputLength = strlen(userInput);

            if(strncmp(userInput, option1, inputLength) == 0 && inputLength <= strlen(option1))
            {
                 menuOption = 1;
            }
            else if(strncmp(userInput, option2, inputLength) == 0 && inputLength <= strlen(option2))
            {
                 menuOption = 2;
            }
            else if(strncmp(userInput, option3, inputLength) == 0 && inputLength <= strlen(option3))
            {
                 menuOption = 3;
            }
            else if(strncmp(userInput, option4, inputLength) == 0 && inputLength <= strlen(option4))
            {
                 menuOption = 4;
            }
            else if(strncmp(userInput, option5, inputLength) == 0 && inputLength <= strlen(option5))
            {
                 endLoop = 1;
                 writefile(start, "data.txt");
                 cleanup(&start);
            }
            else
            {
                 printf("%s is an invalid input\n", userInput);
            }
                 
            switch(menuOption)
            {
                case 1:
                    accountno = 0;

                    do
                    {
                        printf("Enter your account number: ");
                        fgets(accountnoString, 25, stdin);
                        if(accountnoString[strlen(accountnoString) - 1] != '\n')
                        {
                            flushBuffer();
                        }
                        accountnoString[strlen(accountnoString) - 1] = '\0';
                        accountno = atoi(accountnoString);
                        strcpy(utilityString, "");
                        sprintf(utilityString, "%d", accountno);
                        if(strlen(accountnoString) > 9 || accountno <= 0)
                        {
                            printf("Error. Account number must be positive and no longer than 9 digits.\n"); 
                        }
                        else if(strcmp(accountnoString, utilityString) != 0)
                        {
                            printf("Error. Account number must not contain spaces or any other non-numerical characters.\n");
                        }
                    }
                    while(strlen(accountnoString) > 9 || accountno <= 0 || strcmp(accountnoString, utilityString) != 0);
                    
                    do
                    {
                        printf("Enter your full name: ");
                        fgets(utilityString, 50, stdin);
                        if(utilityString[strlen(utilityString) - 1] != '\n')
                        {
                            flushBuffer();
                        }
 
                        if(strlen(utilityString) <= 25)
                        {
                            utilityString[strlen(utilityString) - 1] = '\0';
                            strncpy(name, utilityString, 25);    
                        }
                        else
                        {
                            printf("The name you have entered exceeds the character limit.\n");
                        }
                    }
                    while(strlen(utilityString) > 24);

                    printf("Type your address and hit 'Enter' twice when finished:\n");
                    getAddress(address, addressLength);
                    if(addRecord(&start, accountno, name, address) == 0)
                    {
                        printf("The record has been successfully added to the database.\n");
                    }
                    else
                    {
                        printf("The account number you entered already has an account associated to it.\n");
                    }
                    break;

                case 2:
                    printAllRecords(start);
                break;

                case 3:
                    accountno = 0;

                    do
                    {
                        printf("Enter your account number: ");
                        fgets(accountnoString, 25, stdin);
                        if(accountnoString[strlen(accountnoString) - 1] != '\n')
                        {
                            flushBuffer();
                        }
                        accountnoString[strlen(accountnoString) - 1] = '\0';
                        accountno = atoi(accountnoString);
                        strcpy(utilityString, "");
                        sprintf(utilityString, "%d", accountno);
                        if(strlen(accountnoString) > 9 || accountno <= 0)
                        {
                            printf("Error. Account number must be positive and no longer than 9 digits.\n"); 
                        }
                        else if(strcmp(accountnoString, utilityString) != 0)
                        {
                            printf("Error. Account number must not contain spaces or any other non-numerical characters.\n");
                        }
                    }
                    while(strlen(accountnoString) > 9 || accountno <= 0 || strcmp(accountnoString, utilityString) != 0);

                    if(findRecord(start, accountno) == -1)
                    {
                        printf("No account is associated with account# %d\n", accountno);
                    }
                    break;

                case 4:
                    accountno = 0;

                    do
                    {
                        printf("Enter the number of the account to be deleted : ");
                        fgets(accountnoString, 25, stdin);
                        if(accountnoString[strlen(accountnoString) - 1] != '\n')
                        {
                            flushBuffer();
                        }
                        accountnoString[strlen(accountnoString) - 1] = '\0';
                        accountno = atoi(accountnoString);
                        strcpy(utilityString, "");
                        sprintf(utilityString, "%d", accountno);
                        if(strlen(accountnoString) > 9 || accountno <= 0)
                        {
                            printf("Error. Account number must be positive and no longer than 9 digits.\n"); 
                        }
                        else if(strcmp(accountnoString, utilityString) != 0)
                        {
                            printf("Error. Account number must not contain spaces or any other non-numerical characters.\n");
                        }
                    }
                    while(strlen(accountnoString) > 9 || accountno <= 0 || strcmp(accountnoString, utilityString) != 0);

                    if(deleteRecord(&start, accountno) == 0)
                    {
                        printf("The record has been successfully deleted from the database.\n");
                    }
                    else
                    {
                        printf("No record has been deleted.\n");
                    }
                    break;
            }
            menuOption = 0;
            strcpy(userInput, "");
        }
        while(endLoop == 0);
    }
    return 0;
}

/*****************************************************************
//
//  Function name: getAddress
//
//  DESCRIPTION:   A user interface function.
//                 This function obtains the address input by the user. 
//
//  Parameters:    char* address
//
//  
//  Return values: void 
//
****************************************************************/

void getAddress(char *address, int maxLength)
{
    char util[100];

    strcpy(util, "");
    strcpy(address, "");
 
    if(debugmode == 1)
    {
        printf("\n----------***DEBUG INFO***----------\n");
        printf("Function call: getAddress\n");
        printf("Parameters   : address   = %s\n", address);
        printf("               maxLength = %d\n", maxLength);
        printf("------------------------------------\n\n");
    }

    do
    {
        fgets(util, 100, stdin);
        if(strcmp(util, "\n") != 0)
        {
            if(strlen(util) + strlen(address) < maxLength)
            {
                strcat(address, util);
            }
            else
            {
                printf("Error. You have exceeded the maximum number of characters. \nPlease re-enter your address:\n");
                strcpy(address, "");
            }
        }
    }
    while(strcmp(util, "\n") != 0);

    if(address[strlen(address) - 1] == '\n')
    {
        address[strlen(address) - 1] = '\0';
    }
}

/*****************************************************************
//
//  Function name: flushBuffer
//
//  DESCRIPTION:   A user interface function.
//                 This function flushes the keyboard buffer stdin
//                 and is called if a user input too many
//                 characters.
//                 
//
//  Parameters:    none 
//
//  
//  Return values: void 
//
****************************************************************/

void flushBuffer()
{
    char trash[25];

    if(debugmode == 1)
    {
        printf("\n----------***DEBUG INFO***----------\n");
        printf("Function call: flushBuffer\n");
        printf("Parameters   : none\n");
        printf("------------------------------------\n\n");
    }

    do
    {
        fgets(trash, 25, stdin);
    }
    while(trash[strlen(trash) - 1] != '\n');
}

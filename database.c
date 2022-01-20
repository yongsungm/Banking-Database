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
//  FILE:        database.c
//
//  DESCRIPTION: This file contains the definitions for the 
//               functions declared in database.h and called
//               in user_interface.c.
// 
//
//
****************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "record.h"
#include "database.h"

/*****************************************************************
//
//  Function name: addRecord
//
//  DESCRIPTION:   Adds a record to the linked list.
//
//  Parameters:    struct record **pstart, int accountno,
//                 char *name, char *address 
//
//  Return values: int
//
****************************************************************/

int addRecord(struct record **pstart, int accountno, char name[],char address[])
{
    int duplicateAccountno = 0;
    struct record *index = *pstart;
    struct record *previous = NULL;
    struct record *newRecord = NULL;
    if(debugmode == 1)

    {
        printf("\n----------***DEBUG INFO***----------\n");
        printf("Function call: addRecord\n");
        printf("Parameters   : accountno = %d\n", accountno);
        printf("               name      = %s\n", name);
        printf("               address   = %s\n", address);
        printf("------------------------------------\n\n");
    }
    
    if(*pstart == NULL)
    {
        newRecord = malloc(sizeof(struct record));
        *pstart = newRecord;
        (*newRecord).next = NULL;
        (*newRecord).accountno = accountno;
        if(strcmp(name, "") != 0)
        {
            strcpy((*newRecord).name, name);
        }
        else
        {
            strcpy((*newRecord).name, "(left blank)");
        }
        if(strcmp(address, "") != 0)
        {
            strcpy((*newRecord).address, address);
        }
        else
        {
            strcpy((*newRecord).address, "(left blank)");
        }
    }
    else
    {
        while(index != NULL && (*index).accountno > accountno)
        {
            previous = index;
            index = (*index).next;
        }
        if(index != NULL)
        {
            if((*index).accountno == accountno)
            {
                duplicateAccountno = -1;
            }
        }
        if(duplicateAccountno == 0)
        {
            newRecord = malloc(sizeof(struct record));
            (*newRecord).next = index;
            (*newRecord).accountno = accountno;
            if(strcmp(name, "") != 0)
            {
                strcpy((*newRecord).name, name);
            }
            else
            {
                strcpy((*newRecord).name, "(left blank)");
            }
            if(strcmp(address, "") != 0)
            {
                strcpy((*newRecord).address, address);
            }
            else
            {
                strcpy((*newRecord).address, "(left blank)");
            }
            if(previous == NULL) {
                *pstart = newRecord;
            }
            else
            {
                (*previous).next = newRecord;
            }
        }
    }
    return duplicateAccountno;
}

/*****************************************************************
//
//  Function name: printAllRecords
//
//  DESCRIPTION:   Displays the data of each record to the console.
//
//  Parameters:    struct record *start 
//  
//  Return values: void 
//
****************************************************************/

void printAllRecords(struct record *start)
{
    struct record *index = start;
    if(debugmode == 1)
    {
        printf("\n----------***DEBUG INFO***----------\n");
        printf("Function call: printAllRecords\n");
        printf("Parameters   : none (except for start)\n");
        printf("------------------------------------\n\n");
    }
    if(start != NULL)
    {
        printf("\n------------------------------------\n");
        printf("     List of accounts at Bank x\n");
        printf("------------------------------------\n\n");
    }
    else
    {
        printf("There are currently no records in the database.\n");
    }
    while(index != NULL)
    {
        printf("Account#: %d\n", (*index).accountno);
        printf("Name: %s\n", (*index).name);
        printf("Address:\n%s\n\n", (*index).address);
        index = (*index).next;
    }
    printf("-------------------------------------------------------------\n");
}

/*****************************************************************
//
//  Function name: findRecord 
//
//  DESCRIPTION:   Performs a linear search on the linked list for
//                 a record with an account number that matches
//                 the one which was passed.
//                 Displays the information to the console if found.
//
//  Parameters:    struct record *start, int accountno,
//
//  Return values: int
//
****************************************************************/

int findRecord(struct record *start, int accountno)
{
    int returnValue = 0;
    struct record *index = start;

    if(debugmode == 1)
    {
        printf("\n----------***DEBUG INFO***----------\n");
        printf("Function call: findRecord\n");
        printf("Parameters   : accountno = %d\n", accountno);
        printf("------------------------------------\n\n");
    }
    
    while(index != NULL && (*index).accountno != accountno)
    {
        index = (*index).next;
    }
    if(index == NULL)
    {
        returnValue = -1;
    }
    else
    {
        printf("\n------------------------------------\n");
        printf("           Search results\n");
        printf("------------------------------------\n\n");
        printf("Account#: %d\n", (*index).accountno);
        printf("Name: %s\n", (*index).name);
        printf("Address:\n%s\n", (*index).address);
    }
    return returnValue;
}

/*****************************************************************
//
//  Function name: deleteRecord
//
//  DESCRIPTION:   Removes a record from the linked list and frees
//                 its heap space
//
//  Parameters:    struct record **pstart, int accountno,
//
//  Return values: int
//
****************************************************************/

int deleteRecord(struct record **pstart, int accountno)
{
    int returnValue = 0;
    struct record *index = *pstart;
    struct record *previous = NULL;

    if(debugmode == 1)
    {
        printf("\n----------***DEBUG INFO***----------\n");
        printf("Function call: deleteRecord\n");
        printf("Parameters   : accountno = %d\n", accountno);
        printf("------------------------------------\n\n");
    }
    
    while(index != NULL && accountno != (*index).accountno)
    {
        previous = index;
        index = (*index).next;
    }
    if(index == NULL)
    {
        returnValue = -1;
    }
    else
    {
        if(previous == NULL)
        {
            *pstart = (*index).next;
        }
        else
        {
            (*previous).next = (*index).next;
        }
        free(index);
    }
    return returnValue;
}

/*****************************************************************
//
//  Function name: readfile
//
//  DESCRIPTION:   Reads a text file and stores the data on the
//                 heap by calling addRecord.
//
//  Parameters:    struct record **pstart, char *filename
//
//  Return values: int
//
****************************************************************/

int readfile(struct record **pstart, char filename[])
{
    int cursorPos = 0;
    int lastPos = 1;
    int accountno = 0;
    char accountnoString[25];
    char util[50];
    char name[25];
    char address[50] = "";
    int functionSuccess = 0;
    FILE *fileBuffer;
    if(debugmode == 1)
    {
        printf("\n----------***DEBUG INFO***----------\n");
        printf("Function call: readfile\n");
        printf("Parameters   : filename = %s\n", filename);
        printf("------------------------------------\n\n");
    }
    fileBuffer = fopen(filename, "r");
    if(fileBuffer != NULL)
    {
        while(cursorPos != lastPos)
        {
            lastPos = cursorPos;
            fgets(accountnoString, 25, fileBuffer);
            accountno = atoi(accountnoString);    
            fgets(name, 25, fileBuffer);
            if(name[strlen(name) - 1] == '\n')
            {
                name[strlen(name) - 1] = '\0';
            }
            else
            {
                fgets(util, 25, fileBuffer);
            }
            do
            {
                fgets(util, 50, fileBuffer);
                strcat(address, util);
            }
            while(strcmp(util, "\n") != 0 && strcmp(util,"") != 0);
            address[strlen(address) - 1] = '\0';
            address[strlen(address) - 1] = '\0';
            if(accountno != 0)
            {
                addRecord(pstart, accountno, name, address);
            }
            cursorPos = ftell(fileBuffer);
            strcpy(address, "");
            strcpy(accountnoString, "");
        }
        fclose(fileBuffer);
    }
    else
    {
        functionSuccess = -1;
    }
    return functionSuccess;
}

/*****************************************************************
//
//  Function name: writefile
//
//  DESCRIPTION:   Writes the information from the linked list to a text file
//
//  Parameters:    struct record *start, char *filename
//
//  Return values: int
//
****************************************************************/

int writefile(struct record *start, char filename[])
{
    struct record *index = start;
    int functionSuccess = 0;
    FILE *fileBuffer;
    if(debugmode == 1)
    {
        printf("\n----------***DEBUG INFO***----------\n");
        printf("Function call: writefile\n");
        printf("Parameters   : filename = %s\n", filename);
        printf("------------------------------------\n\n");
    }
    fileBuffer = fopen(filename, "w");
    if(fileBuffer != NULL && start != NULL)
    {
        while(index != NULL)
        {
            fprintf(fileBuffer, "%d\n%s\n%s\n\n", (*index).accountno, (*index).name, (*index).address);
            index = (*index).next;
        }
        fclose(fileBuffer);
    }
    else
    {
        functionSuccess = -1;
    }
    return functionSuccess;
}

/*****************************************************************
//
//  Function name: cleanup
//
//  DESCRIPTION:   Frees the heap space when called //
//  Parameters:    struct record **pstart
//
//  Return values: none
//
****************************************************************/

void cleanup(struct record **pstart)
{
    struct record *index = *pstart;
    struct record *previous = NULL;
    if(debugmode == 1)
    {
        printf("\n----------***DEBUG INFO***----------\n");
        printf("Function call: cleanup\n");
        printf("Parameters   : none (except for &start)\n");
        printf("------------------------------------\n\n");
    }
    while(index != NULL)
    {
        previous = index;
        index = (*index).next;
        free(previous);
    }
    *pstart = NULL;
}

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
//  FILE:        database.h
//
//  DESCRIPTION: This file contains the declarations for the functions
//               defined in database.c
//               It also contains the declaration for the global
//               variable debugmode.
// 
//
//
****************************************************************/

extern int debugmode;

int addRecord(struct record **, int, char[], char[]);
void printAllRecords(struct record*);
int findRecord(struct record *, int);
int deleteRecord(struct record **, int);
int readfile(struct record **, char[]);
int writefile(struct record *, char[]);
void cleanup(struct record **);

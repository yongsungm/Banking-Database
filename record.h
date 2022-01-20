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
//  FILE:        record.h
//
//  DESCRIPTION: This is a data type created for account records.
// 
//
//
****************************************************************/

struct record
{
    int accountno;
    char name[25];
    char address[50];
    struct record* next;
};

#pragma once
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#pragma warning(disable:4996)

#ifdef _MSC_VER 
#define strncasecmp _strnicmp
#define strcasecmp _stricmp
#endif

#define MAX 10000
#define SIZE 300000
#define _CRT_SECURE_NO_WARNINGS

typedef struct DATA {
	char *word;
	char *part;
	char *meaning;
}DATA;

void make_dict1(char buffer[]);

void make_dict2(char first[],char second[],char third[]);

void read_dict(char *token);

void size_dict();

void find_dict1(char *token);

int find_dict2(char *token, int start, int end);

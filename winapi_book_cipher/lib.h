#pragma once
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <windows.h>

#define SIZE 1000

#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3
#define ENCRYPT 4
#define DECRYPT 5

using namespace std;

void AddMenus(HWND);
void AddControls(HWND);

int how_many_lines(string sentence);

int max_length_of_line(string sentence);

void matrix_filler(char** matrix, string sentence);

string encrypt(char** matrix, int new_lines, int line_length, char to_find[]);

string decrypt(char** matrix, int new_lines, int line_length, char to_find[]);
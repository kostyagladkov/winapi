#include "lib.h"

void matrix_filler(char** matrix, string sentence){

    int length = sentence.length();

    // ! Filling the matrix and printing in '_' for the rest symbols if the length of the line is less than max_length
    int columns = 0, rows = 0;
    for (int i = 0; i < length - 1; i++){
        if (sentence[i] == '\n'){
            for (int k = rows; k < max_length_of_line(sentence); k++){
                matrix[columns][k] = '_';
            }
            columns++;
            rows = 0;
        }
        else {
            matrix[columns][rows] = sentence[i];
            rows++;
        }
    }

}

int how_many_lines(string sentence){

    int length = sentence.length();

    // ! Getting the amount of new lines in our sentence
    int new_lines = 0;
    for (int i = 0; i < length; i++){
        if (sentence[i] == '\n'){
            new_lines++;
        }
    }
    // ! It counts the last word with a new line, so we have to remove it
    new_lines--;

    return new_lines;
}

int max_length_of_line(string sentence){

    int length = sentence.length();

    // ! Counting the max size of the line in our sentence
    int max_length_of_line = 0;
    int temp = 0;
    for (int i = 0; i < length; i++) {
        if (sentence[i] != '\n')
            max_length_of_line++;
        else {
            temp = max(temp, max_length_of_line);
            max_length_of_line = 0;
        }
    }
    max_length_of_line = max(temp, max_length_of_line);

    return max_length_of_line;
}

string encrypt(char** matrix, int new_lines, int line_length, char to_find[]){

    fflush(stdin);

    char result[strlen(to_find) * 4];

    int counter = 0;
    int index = 0;
    for (int i = 0; i < strlen(to_find); i++){
        for (int j = 0; j < new_lines; j++){
            int flag = 0;
            for (int k = 0; k < line_length; k++){
                if (to_find[i] == matrix[j][k]){
                    result[index++] = j + '0';
                    counter++;
                    result[index++] = '/';
                    counter++;
                    result[index++] = k + '0';
                    counter++;
                    result[index++] = ',';
                    counter++;
                    flag = 1;
                    break;
                }
            }
            if (flag == 1){
                break;
            }
        }

    }

    for (int i = counter - 1; i < strlen(to_find) * 5 + 1; i++){
        result[i] = ' ';
    }

    return result;
}

string decrypt(char** matrix, int new_lines, int line_length, char to_find[]){

    int size_to_find = strlen(to_find);

    char result[size_to_find];

    int index = 0;
    int x, y;
    for (int i = 0; i < size_to_find ; i++){
        x = to_find[i] - 48;
        i = i + 2;
        y = to_find[i] - 48;
        result[index++] = matrix[x][y];
        i = i + 1;
    }

    return result;
}

/*
*   satius, The better VM (main.c)
*   Copyright (C) 2024 Lilly H. St Claire
*
*            This program is free software: you can redistribute it and/or modify
*            it under the terms of the GNU General Public License as published by
*            the Free Software Foundation, either version 3 of the License, or (at
*            your option) any later version.
*
*            This program is distributed in the hope that it will be useful, but
*            WITHOUT ANY WARRANTY; without even the implied warranty of
*            MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*            General Public License for more details.
*
*            You should have received a copy of the GNU General Public License
*            along with this program.  If not, see <https://www.gnu.org/licenses/>.
*
*/

#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char **argv) {
    FILE      *fp;
    BUFFER     file_buffer;
    if(argc < 2) {
        printf("Error: Usage: %s <sat file>\n", argv[0]);
        exit(1);
    } 
    fp = fopen(argv[1], "r");
    if(!fp) {
        printf("Error: file %s could not be opened\n", argv[1]);
        exit(1);
    }
    fseek(fp, 0L, SEEK_END);
    file_buffer.length = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    file_buffer.content = malloc(file_buffer.length);
    fread(file_buffer.content, 1, file_buffer.length, fp);
    fclose(fp);
    interpret(file_buffer);
    free(file_buffer.content);
    return 0;
}

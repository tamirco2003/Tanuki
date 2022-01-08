#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <stdio.h>

typedef struct _file_t {
	FILE* fp;
	char current;
	char next;
} File_t;

File_t FileHandler_OpenFile(const char* path);
void FileHandler_CloseFile(File_t* file);
void FileHandler_Advance(File_t* file);

#endif  // FILE_HANDLER_H
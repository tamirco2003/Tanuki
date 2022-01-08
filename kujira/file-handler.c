#include "file-handler.h"

File_t FileHandler_OpenFile(const char* path) {
	File_t file;
	file.fp = fopen(path, "r");
	file.current = fgetc(file.fp);
	file.next = fgetc(file.fp);

	return file;
}

void FileHandler_CloseFile(File_t* file) { fclose(file->fp); }

void FileHandler_Advance(File_t* file) {
	file->current = file->next;
	file->next = fgetc(file->fp);
}
#ifndef FILE_H
#define FILE_H

char* get_file_path(const char* local_file);

char* file_get_cwd();

char* file_read_local(const char* local_file);

char* file_read(const char* file_path);

#endif
#include "file.h"
#include "seethe.h"
#include <stdio.h>
#include <stdlib.h>
#include <direct.h>

char* get_file_path(const char* local_file)
{
	char* cwd = file_get_cwd();

	size_t full_directory_size = strlen(cwd) + strlen(local_file) + 1;
	char* full_directory = malloc(full_directory_size);

	if (full_directory == NULL) 
	{
		char errorMsg[512];
		sprintf_s(errorMsg, sizeof(errorMsg), "Unable to allocate memory for filepath: %s", local_file);
		log_error(errorMsg);

		free(cwd);

		return NULL;
	}

	snprintf(full_directory, full_directory_size, "%s%s", cwd, local_file);
	free(cwd);

	return full_directory;
}

char* file_get_cwd()
{
	char* cwd = getcwd(NULL, 0);
	return cwd;
}

char* file_read_local(const char* local_file)
{
	char* local_file_path = get_file_path(local_file);

	if (local_file_path == NULL)
		return NULL;

	char* local_file_data = file_read(local_file_path);

	free(local_file_path);

	return local_file_data;
}

char* file_read(const char* file_path)
{
	//open file in binary mode
	FILE* file = fopen(file_path, "rb");

	if (!file) 
	{
		char errorMsg[512];
		sprintf_s(errorMsg, sizeof(errorMsg), "Unable to open filepath: %s", file_path);
		log_error(errorMsg);

		return NULL;
	}

	//seek to the end to get file size
	fseek(file, 0, SEEK_END);
	long length = ftell(file);

	//go back to the beginning
	rewind(file);

	//allocate memory for file contents + null terminator
	char* buffer = malloc((size_t)length + 1);
	if (!buffer) 
	{
		char errorMsg[512];
		sprintf_s(errorMsg, sizeof(errorMsg), "unable to allocate memory for file: %s", file_path);
		log_error(errorMsg);
		fclose(file);

		return NULL;
	}

	//read file content into buffer
	size_t read_size = fread(buffer, 1, (size_t)length, file);
	if (read_size != (size_t)length) 
	{
		free(buffer);
		fclose(file);
		return NULL;
	}

	buffer[length] = '\0'; // Null terminate
	fclose(file);

	return buffer;
}
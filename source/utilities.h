#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

time_t read_file_time(char* path)
{
    struct stat filestat;
    stat(path, &filestat);

    return filestat.st_mtime;
}

char* read_file(char* path)
{
    FILE* file_to_read;
#if defined(__WIN32__) || defined(__WINRT__) || defined(_WIN64)
    fopen_s(&file_to_read, path, "rb");
#else
    file_to_read = fopen(path, "rb");
#endif
    if (file_to_read != NULL) {
        fseek(file_to_read, 0, SEEK_END);
        int file_size = ftell(file_to_read);
        fseek(file_to_read, 0, SEEK_SET);

        char* file_contents = (char*)calloc(file_size, sizeof(char));
        fread(file_contents, 1, file_size, file_to_read);
        // Ensure that weird or random characters
        // do not terminate this string.
        file_contents[file_size] = '\0';
        fclose(file_to_read);

        return file_contents;
    }
    return "";
}

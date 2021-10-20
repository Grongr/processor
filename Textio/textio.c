#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/io.h>

#include "textio.h"

FileLog input(char** buffer, const char *input_file) {

    assert(input_file != NULL);

    FILE* fin = fopen(input_file, "r");

    if (fin == NULL)
        return CANNOT_FIND_FILE;

    struct stat information;
    stat(input_file, &information);

    *buffer = (char*) calloc((size_t) information.st_size + 4UL, sizeof(char));
    if (*buffer == NULL)
        return NO_MEMORY;

    ssize_t size = fread(*buffer, sizeof(char),
                         (size_t) information.st_size, fin);

    if (size < 0)
        return CANNOT_READ_FILE;

    *(*buffer + size + 1) = '\n';
    *(*buffer + size + 2) = '\0';

    fclose(fin);
    return FILE_OK;
}

string* parser(char* buffer, size_t* count, char ch) {

    assert(buffer != NULL);
    assert(count  != NULL);

    char* iter = buffer;
    *count = 0;

    while ( (iter = strchr(iter, ch)) != NULL ) {

        while (*iter == ch)
            ++iter;
        ++(*count);
    }

    string* text = (string*) calloc(*count, sizeof(string));

    if (text == NULL)
        return NULL;

    iter = buffer;
    char*  last   = buffer;
    size_t length = 0;

    for (int i = 0; i < *count; ++i) {

        (text + i)->ptr = iter;
        last = iter;

        iter = strchr(iter, ch);
        length = (size_t) (iter - last);
        (text + i)->length = length;

        while (*iter == ch) ++iter;
    }

    for (int i = 0; i < *count; ++i) {

        *((text + i)->ptr + (text + i)->length) = '\0';
    }

    return text;
}

FileLog write_result(string* text, int count, const char* output) {

    assert(text != NULL);

    FILE* fout = fopen(output, "a");

    if (fout == NULL)
        return CANNOT_WRITE_FILE;

    for (int i = 0; i < count; ++i) {

        fputs((text + i)->ptr, fout);
        fputs("\n", fout);
    }

    // To separate different texts
    fputs("\n\n", fout);

    fclose(fout);
    return FILE_OK;
}

FileLog clear(const char* filename) {

    assert(filename != NULL);

    FILE* fo = fopen(filename, "w");

    if (fo == NULL)
        return CANNOT_FIND_FILE;

    fclose(fo);
    return FILE_OK;
}

FileLog get_file_names(char* input, char* output) {

    puts("Enter path to input file:");
    scanf("%s", input);

    FILE* fin = fopen(input, "r");
    if (fin == NULL)
        return CANNOT_READ_FILE;

    fclose(fin);

    puts("Enter path to output file:");
    scanf("%s", output);

    FILE* fout = fopen(output, "w");
    if (fout == NULL)
        return CANNOT_WRITE_FILE;

    fclose(fout);

    return FILE_OK;
}

void free_text_buf(string* text, char* buf) {

    free(text);
    free(buf);
}

FileLog file_preparation(char* buffer) {

    const char* ignore = " \t";

    char* l    = buffer;
    char* r    = buffer;

    r += strspn(r, ignore);
    l = r;

    while (*r != '\0') {

        while (!strspn(r, ignore) && *r != '\0') ++r;

        l = r - 1;
        r += strspn(r, ignore);

        if (*l == '\n' || *r == '\n') {

            for (; l < r; ++l)
                *l = '\n';
        }
    }

    r = buffer;

    while ( (r = strchr(r, '\t')) != NULL )
        *r = ' ';

    return FILE_OK;
}

FileLog preparation_write(const char *buffer, const char* output) {

    FILE* fout = fopen(output, "w");
    if (fout == NULL)
        return CANNOT_WRITE_FILE;

    while (*buffer != '\0') {

        if (*buffer == ' ') {

            putc(*buffer, fout);
            buffer += strspn(buffer, " \t");
        } else if (*buffer == '\n') {
        
            putc(*buffer, fout);
            buffer += strspn(buffer, "\n");
        } else {

            putc(*buffer, fout);
            ++buffer;
        }
    }

    fclose(fout);
    return FILE_OK;
}

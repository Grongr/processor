#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "assembler.h"
#include "commands.h"
#include "Textio/textio.h"

//! Maximum size of array <code>
#define MAXIMUM_CODE_SIZE 4096

#define CodeCheck(Func, OkCode)     \
{                                   \
    int Code = Func;                \
    if (Code != OkCode)             \
        return Code;                \
}

/* #define more_info */

int main(int argc, char** argv) {

    if (argc != 2) {

        puts("Wrong argument count.");
        return 1;
    }

    unsigned char code[MAXIMUM_CODE_SIZE];
    for (size_t i = 0; i < MAXIMUM_CODE_SIZE; ++i)
        code[i] = POIS;

    CodeCheck(code_from_text(code, argv[1]), ASS_OK);

#ifdef more_info
    int i = 0;
    while (code[i] != POIS) {

        printf("%d ", (int)code[i]);
        ++i;
    }
    puts("");
#endif // more_info

    return 0;
}

AssErr code_from_text(unsigned char* code, const char* filename) {

    if (strcmp(strchr(filename, '.'), ".sht") != 0)
        return ASS_EXTENTION_ERROR;

    char* buffer;
    if (input(&buffer, filename) != FILE_OK)
        return CANNOT_READ_ASSEMBL;

    size_t count = 0;
    string* text = parser(buffer, &count, '\n');

    /* char* outfile = outfile_name(filename); */
    const char* outfile = "out.asm";

    for (int i = 0; i < (int)count; ++i) {
        add_command(code, text[i].ptr);
    }

    size_t len = 0;
    while (code[len] != POIS) ++len;
    ++len;

    FILE* out = fopen(outfile, "wb");
    
    fwrite(code, sizeof(unsigned char), len, out);

    fclose(out);
    return ASS_OK;
}

char* outfile_name(const char* filename) {

    char* outfile1 = (char*)calloc(strlen(filename), sizeof(char));
    strncpy(outfile1, filename, strlen(filename) - 4);
    strcat(outfile1, ".asm");
    char* p = outfile1 + strlen(outfile1);
    
    while (*p != '/' && p != outfile1) --p;

    if (p != outfile1) ++p;

    char* outfile = (char*)calloc(strlen(p), sizeof(char));
    strcpy(outfile, p);
    free(outfile1);
    p = NULL;
    return outfile;
}

#ifdef more_info

#define d_bug \
    printf("Real code: %d %d\n", code[id - 1], code[id - 1] & Mask000);

#else // more_info

#define d_bug

#endif // more_info

#define param_calc                          \
    printf("Param:    %d\n", param);           \
    int* tmp = (int*)(code + id);           \
    *tmp = param;                           \
    ++tmp;                                  \
    id = (int)((unsigned char*)tmp - code);

#define reg_calc                            \
    printf("Register: %c\n", reg);          \
    char* tmp2 = (char*)(code + id);        \
    *tmp2 = reg - 'a';                      \
    ++tmp2;                                 \
    id = (int)((unsigned char*)tmp2 - code);

AssErr add_command(unsigned char* code, char* str) {

    static int id = 0;

    char cmd[20];
    int param = 0;
    char reg;
    
    if (sscanf(str, "%s [%d+r%cx]", cmd, &param, &reg) == 3 ||
        sscanf(str, "%s [r%cx+%d]", cmd, &reg, &param) == 3) {

        code[id++] = Mask111 | command_number(cmd);
        d_bug;
        param_calc;
        reg_calc;

    } else if ( sscanf(str, "%s [r%cx]", cmd, &reg) == 2 ) {

        code[id++] = Mask101 | command_number(cmd);
        d_bug;
        reg_calc;

    } else if ( sscanf(str, "%s [%d]", cmd, &param) == 2 ) {

        code[id++] = Mask110 | command_number(cmd);
        d_bug;
        param_calc;

    } else if ( sscanf(str, "%s r%cx", cmd, &reg) == 2 ) {

        code[id++] = Mask001 | command_number(cmd);
        d_bug;
        reg_calc;

    } else if ( sscanf(str, "%s %d", cmd, &param) == 2 ) {

        code[id++] = Mask010 | command_number(cmd);
        d_bug;
        param_calc;

    } else if ( sscanf(str, "%s ", cmd) == 1 ) {

        code[id++] = command_number(cmd);
        d_bug

    }

#ifdef more_info
    printf("Command code: %d\n", command_number(cmd));
    printf("Command name: %s\n\n", cmd);
#endif // more_info

    return ASS_OK;
}

ProcCommands command_number(char* str) {

    if (!strcmp(str, "push"))
        return Push;
    else if (!strcmp(str, "hajme"))
        return Hajme;
    else if (!strcmp(str, "in"))
        return In;
    else if (!strcmp(str, "out"))
        return Out;
    else if (!strcmp(str, "pop"))
        return Pop;
    else if (!strcmp(str, "sum"))
        return Sum;
    else if (!strcmp(str, "mul"))
        return Mul;
    else if (!strcmp(str, "div"))
        return Div;
    else if (!strcmp(str, "ippon"))
        return Ippon;
    else
        return ERROR;
}

#undef CodeCheck

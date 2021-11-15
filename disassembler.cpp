#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <assert.h>

#include "Textio/textio.h"
#include "assembler.h"
#include "disassembler.h"
#include "commands.h"

#define CodeCheck(Func, OkCode)     \
{                                   \
    int Code = Func;                \
    if (Code != OkCode)             \
        return Code;                \
}

int main(int argc, char** argv) {

    const char* input_file = (argc >= 2) ? argv[1] : "out.asm";
    unsigned char* code = NULL;
    int size = 0;

    CodeCheck(binary_code_read(&code, &size, input_file), FILE_OK);

    /* for (int i = 0; i < size; ++i) { */
    /*     printf("%d ", (int)code[i]); */
    /* } */
    /* puts(""); */

    CodeCheck(dis_assembl(code, size), ASS_OK);
    
    return 0;
}

FileLog binary_code_read(unsigned char** code, int* size,
                         const char* input_file) {

    assert(input_file != NULL);
    FILE* fin = fopen(input_file, "rb");
    
    if (fin == NULL)
        return CANNOT_FIND_FILE;
    
    struct stat info;
    stat(input_file, &info);

    *code = (unsigned char*) calloc((size_t)info.st_size,
                                                   sizeof(unsigned char));

    size_t readed_size = fread(*code, sizeof(unsigned char),
                               (size_t)info.st_size, fin);

    if (readed_size < 0)
        return CANNOT_READ_FILE;

    *size = (int)readed_size - 1;

    fclose(fin);

    return FILE_OK;
}

AssErr dis_assembl(unsigned char* code, int size) {

    int id = 0;
    FILE* fout = fopen("out.sht", "w");

    while (id < size) {

        int step = 0;

        switch (code[id] & Mask000) {

            case Hajme:
                fputs("hajme", fout);
                break;

            case In:
                fputs("in", fout);
                break;

            case Out:
                fputs("out", fout);
                break;

            case Push:
                fputs("push", fout);
                break;

            case Pop:
                fputs("pop", fout);
                break;

            case Sum:
                fputs("sum", fout);
                break;

            case Mul:
                fputs("mul", fout);
                break;

            case Div:
                fputs("div", fout);
                break;

            case Ippon:
                fputs("ippon", fout);
                break;

            default:
                assert("Wrong command code!");
                break;
        }

        if (code[id] & Mask010) {
            fprintf(fout, " %d", *(int*)(code + id + 1));
            step += 4;
        }
        if (code[id] & Mask001){
            fprintf(fout, " r%cx", 'a' + *(char*)(code + id + step + 1));
            step += 1;
        }
        id += step + 1;

        fputs("\n", fout);
    }
    
    fclose(fout);
    return ASS_OK;
}

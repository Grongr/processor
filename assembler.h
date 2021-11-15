#ifndef ASSEMBLER_H_INCLUDED
#define ASSEMBLER_H_INCLUDED

#include "Textio/textio.h"
#include "commands.h"

typedef enum {

    ASS_OK              = 0,
    ASS_EXTENTION_ERROR = 1,
    CANNOT_READ_ASSEMBL = 2

} AssErr;

/*!
 * @brief Gets code from <filenam>
 *
 * It tryes to understnad which command
 * from <commands.h> is used, then puts 
 * in <code> command number with arguments
 *
 * ARGUMENTS SHOULD BE ONLY INTEGER
 *
 * @param [out] <code>     Code array whuch lately will be written on disk
 * @param [in]  <filename> Name of file with an initial code
 *
 * @return error code
 */
AssErr code_from_text(unsigned char* code, const char* filename);

/*!
 * @brief Func to convert filename
 *
 * @param [in] <filename> name of file to transform
 *
 * @return pointer to the new file name
 */
char* outfile_name(const char* filename);

/*!
 * @brief Func to add command in code
 *
 * Adds one command from string <str> if it
 * possible.
 *
 * @param [out] <code> code array
 * @param [in]  <str>  string with command
 *
 * @return error code
 */
AssErr add_command(unsigned char* code, char* str);

/*!
 * @brief Func to know command number
 *
 * It counts number of commands including
 * firtt three bytes, which are needed to know
 * the params of command.
 *
 * @param [in] <str> string with command
 *
 * @return command number
 */
ProcCommands command_number(char* str);

#endif // ASSEMBLER_H_INCLUDED

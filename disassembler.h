#ifndef DISASSEMBLER_H_INCLUDED
#define DISASSEMBLER_H_INCLUDED

#include "Textio/textio.h"
#include "commands.h"
#include "assembler.h"

/*!
 * @brief This func does all the work
 *
 * It puts code into <out.sht> file after
 * disassemlying.
 * 
 * @param [in] <code> array with code in binary format
 * @param [in] <size> code array size
 *
 * @return error code
 */
AssErr dis_assembl(unsigned char* code, int size);

/*!
 * @brief Simply reads binary file
 *
 * It reads code from <input_file>
 *
 * @param [out] <code>       array with code
 * @param [out] <size>       size of code array
 * @param [in]  <input_file> name of file to read
 */
FileLog binary_code_read(unsigned char** code, int* size, const char* input_file);

#endif // DISASSEMBLER_H_INCLUDED

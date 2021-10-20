#ifndef TEXTIO_INClUDED
#define TEXTIO_INClUDED

#include <stddef.h>

/*!
 * @brief Funcs returns the code from this enum
 *
 * @version 0.1
 */
enum FileLog {
    FILE_OK           = 0, //< Means that all is ok
    CANNOT_FIND_FILE  = 1, //< Means that file is not in current directory
    CANNOT_READ_FILE  = 2, //< Means that file isn't avalible for reading 
    CANNOT_WRITE_FILE = 3, //< Means that file isn't avalible for writing
    NO_MEMORY         = 4  //< Means that there is not enough memory
};

typedef enum FileLog FileLog;

/*!
 * @brief Struct of string...
 *
 * Nothing to say about it...
 *
 * @version 0.1
 */
struct string {
    char*  ptr;    //< Pointer to the string
    size_t length; //< Length of this string
};

typedef struct string string;

/*!
 * @brief Func which is needed to bufferise file.
 *
 * It reads from input file all strings and
 * optinally safes them to memory.
 *
 * @param [out] <buffer> array of pointers
 *                       to the strings
 * 
 * @return code of error or 0 if all was ok
 *         (see FileLog enum for more details)
 * 
 * @version 0.1
 */
FileLog input(char** buffer, const char* input_file);

/*!
 * @brief Makes an array of strings
 *
 * From big cstring <buffer> creates an array
 * of strings
 *
 * @param [in]  <buffer> pointer to the beginning of buffer
 * @param [out] <count>  count of strings in buffer
 * @param [in]  <ch>     delimeter of strings in <buffer>
 *
 * @return parsed buffer as text
 *
 * @version 0.1
 */
string* parser(char* buffer, size_t* count, char ch);

/*!
 * @brief This func clears the <filename> file
 *
 * You need to clear output file before
 * you add something to it (if you wanna
 * to get useful output)
 *
 * @param [in] <filename> the name of file to clear
 *
 * @version 0.1
 */
FileLog clear(const char* filename);

/*!
 * @brief Use it to change filenames
 *
 * Changes names of <input> and <output> files
 *
 * @return code of error or 0 if all was ok
 *         (see FileLog enum for more details)
 *
 * @version 0.1
 */
FileLog get_file_names(char* input, char* output);

/*!
 * @brief Writes in file <output>
 *
 * Use it to write text from string arra <text>
 * in the file <output>
 *
 * @param [in]  <text>    pointer to the array of strings
 * @param [in]  <output>  name of ouput file
 * @param [in]  <count>   count of strings in text
 *
 * @return code of error or 0 if all was ok
 *         (see FileLog enum for more details)
 *
 * @version 0.1
 */
FileLog write_result(string* text, int count, const char* output);

/*!
 * @brief Destructor of <buffer> and <text>
 *
 * Frees <buffer> valuable and <text> valuable
 *
 * @param [in] <text>    array of strings to free
 * @param [in] <buffer>  cstring buffer to free
 *
 * @version 0.1
 */
void free_text_buf(string* text, char* buf);

/*!
 * @brief Func to prepare file to processing it
 *
 * It deletes all useless spaces, tabs and '\n'
 * symbols
 *
 * @param [in]  <buffer> what should it work with
 *
 * @return FileLog enum - code of error or FILE_OK
 */
FileLog file_preparation(char* buffer);

/*!
 * @brief Writes buffer in the outout file
 *
 * Ignores double spaces and double '\n'
 * when writes buffer in output file
 *
 * @param [in] <buffer> string to write in
 * @param [in] <output> path to output file
 */
FileLog preparation_write(const char* buffet, const char* output);

#endif // TEXTIO_INClUDED

cmake_minimum_required(VERSION 3.10)
project(processor VERSION 1.0 LANGUAGES CXX)

# set (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DNDEBUG")
set (CMAKE_C_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Werror -Wfloat-equal -Wsign-conversion -warray-bounds -wdiv-by-zero -wdouble-promotion -g3 -o0")

add_subdirectory(Stack)
add_subdirectory(Textio)

add_executable(ass assembler.cpp)
add_executable(dis disassembler.cpp)
add_executable(cml compiler.cpp)

# add_library(stack STATIC Stack/stack.cpp Stack/mem_copy.cpp
#                          Stack/user_funcs.cpp Stack/hash.cpp)
# add_library(textio STATIC Textio/textio.cpp)

# target_include_directories(stack Stack/)
# target_include_directories(textio Textio/)

target_link_libraries(ass stack textio)
target_link_libraries(dis stack textio)
target_link_libraries(cml stack textio)

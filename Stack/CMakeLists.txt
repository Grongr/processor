cmake_minimum_required(VERSION 3.10)

add_library(stack STATIC stack.cpp mem_copy.cpp
                         user_funcs.cpp hash.cpp)

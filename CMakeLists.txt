cmake_minimum_required(VERSION 3.26)
project(class4j C)

set(CMAKE_C_STANDARD 11)

add_executable(class4j Class4j.c
        Class.h
        Class.c
        Common.c
        Common.h
        Class4j.h
        ConstantItem.h
        ConstantItem.c
        FieldItem.h
        AttrWrapper.h
        FieldItem.c)

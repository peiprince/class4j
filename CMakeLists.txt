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
        FieldItem.c
        AttrWrapper.c
        AttrConstantValue.c
        AttrConstantValue.h
        AttrDeprecated.h
        AttrDeprecated.c
        AttrRtVisAnnotations.h
        AttrRtVisAnnotations.c
        AttrRtVisTypeAnnotations.h
        AttrRtVisTypeAnnotations.c
        AttrAnnotation.h
        AttrAnnotation.c
        AttrCode.h
        AttrCode.c
        AttrLineNumberTable.h
        AttrLineNumberTable.c
        AttrLocalVariableTable.h
        AttrLocalVariableTable.c
        AttrRtVisParamAnnotation.h
        AttrRtVisParamAnnotation.c
        AttrMethodParams.h
        AttrMethodParams.c
        AttrExceptions.h
        AttrExceptions.c
        AttrSourceFile.h
        AttrSourceFile.c
        AttrInnerClass.h
        AttrInnerClass.h
        AttrInnerClass.c)

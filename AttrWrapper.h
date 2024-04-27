//
// Created by Administrator on 2024/4/26 0026.
//
#pragma once
#ifndef CLASS4J_ATTRWRAPPER_H
#define CLASS4J_ATTRWRAPPER_H

typedef struct AttrWrapper {

    char *type;         // 标记当前属性的类型

    void *p_attr;       // 存储属性信息

} AttrWrapper;

#endif //CLASS4J_ATTRWRAPPER_H

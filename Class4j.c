#include "Class.h"

Class class = { 0 };

int main(int argv, char* argc[]) {
    if (argv != 2) {
        printf("Invalid option!");
        return -1;
    }
    FILE* fp = fopen(argc[1], "rb");
    if (fp == NULL)
    {
        perror("Failed to open file");
        return -1;
    }
    check_class_version(&class, fp);
    read_constant_pool(&class, fp);
    read_access_flags(&class, fp, ClassType);
    print_class_info(&class, argc[1]);
    return 0;
}

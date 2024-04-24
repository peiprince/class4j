#include "Class.h"

extern char const_type[11][20];
extern unsigned int g_index;
extern unsigned int power;

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
    check_class_version(fp, &class);
    print_class_info(&class);
    return 0;
}

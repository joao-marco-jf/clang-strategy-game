#include "include.h"

int main() {
    FILE *file = fopen("entrada.txt", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    read_all_file(file);

    return 0;
}
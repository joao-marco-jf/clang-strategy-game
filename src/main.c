#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
    FILE *file = fopen("entrada.txt", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    int rows, columns;
    if (fscanf(file, "%i %i", &rows, &columns) != 2) {
        printf("Failed to read the dimensions of the board.\n");
        return 1;
    }

    int num_factions;
    if (fscanf(file, "%i", &num_factions) != 1) {
        printf("Failed to read the number of phases.\n");
        return 1;
    }

    char part[10];
    char action[10];

    while (!feof(file)) {
        if(fscanf(file, "%s %s ", part, action) != 2) break;
        if(strcmp(part, "FIM") == 0) break;

        printf("%s %s ", part, action);

        if(strcmp(action, "alianca") == 0){
            char param[10];
            fscanf(file, "%s", param);
            printf("%s", param);
        } else if (strcmp(action, "ataca") == 0) {
            char param[10];
            fscanf(file, "%s", param);
            printf("%s ", param);

            int params[6];
            int index = 0;
            while (fscanf(file, "%i ", &params[index]) == 1) {
            printf("%i ", params[index]);
            }
        }
        else if (
            strcmp(action, "combate") == 0 ||
            strcmp(action, "ganha") == 0 ||
            strcmp(action, "perde") == 0 ||
            strcmp(action, "vence") == 0
        ) {
            char enemy_name[10];
            int self_value;
            int enemy_value;
            fscanf(file, "%i %s %i", &self_value, enemy_name, &enemy_value);
            printf("%i %s %i", self_value, enemy_name, enemy_value);
        } else {
            int params[6];
            int index = 0;
            while (fscanf(file, "%i ", &params[index]) == 1) {
                printf("%i ", params[index]);
            }
        }
        
        printf("\n");
        // Process the unit, action, and parameters
        // ...
    }

    fclose(file);
    return 0;
}
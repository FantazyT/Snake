#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

void get_dims(char *world, int *width, int *height) {
    bool stop_count_width = false;
    for (int i = 0; world[i] != '\0'; ++i){
        if(world[i] == '\n'){
            (*height)++;
            stop_count_width = true;
        }
        if(!stop_count_width){
            (*width)++;
        }
    }
}


int main(int argc, char **argv) {
    char *fileName = NULL;
    if (argc > 1) {
        fileName = argv[1];
    } else {
        printf("entrez au moins un paramètre\n");
        return -1;
    }

    FILE *file = fopen(fileName, "r");
    if(file == NULL) {
        return -1;
    }

    fseek(file, 0, SEEK_END); 
    int size = ftell(file); 
    fclose(file); 

    char *world = malloc(size);

    file = fopen(fileName, "r");
    size_t read_bytes = fread(world, sizeof(char), size, file);

    printf("%s\n", world);

    bool stop_count = false;
    int height = 0;
    int width = 0;

    for(int i = 0; i < read_bytes; i++) {
        if(world[i] == "\n") {
            height ++;
            stop_count = true;
        }
        if(!stop_count) {
            width ++;
        }
    }

    bool stop = false;
    while(!stop) {
        int user_input = getchar();
        //testing esc
        if(user_input == 27) {
            stop = true;
        }
    }

    free(world);

    fclose(file);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int i;

    // Check if at least one file is provided
    if (argc < 2) {
        fprintf(stderr, "wcat: file1 [file2 ...]\n");
        return 1;
    }

    // Loop through each file provided as an argument
    for (i = 1; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        char buffer[4096];

        // Check if the file was opened successfully
        if (file == NULL) {
            fprintf(stderr, "wcat: cannot open file\n");
            return 1;
        }

        // Read the file line by line and print
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            printf("%s", buffer);
        }

        fclose(file);
    }

    return 0;
}
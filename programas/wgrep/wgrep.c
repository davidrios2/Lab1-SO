#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void search_in_stream(FILE *stream, const char *search_term) {
    char *line = NULL;
    size_t line_capacity = 0;
    ssize_t line_length;

    // -1 is returned on EOF or error, but we don't distinguish between them here
    while ((line_length = getline(&line, &line_capacity, stream)) != -1) {
        
        if (strstr(line, search_term) != NULL) {
            printf("%s", line);
        }
    }

    free(line);
}

int main(int argc, char *argv[]) {
    int i;
    const char *search_term;

    if (argc < 2) {
        fprintf(stderr, "wgrep: searchterm [file ...]\n");
        return 1;
    }

    search_term = argv[1];

    // If no files are provided, search in standard input
    //why? Because this allows the user to use wgrep in a pipeline, for example: `wcat file.txt | wgrep searchterm`
    if (argc == 2) {
        search_in_stream(stdin, search_term);
        return 0;
    }


    // Loop through each file provided as an argument
    for (i = 2; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");

        if (file == NULL) {
            fprintf(stderr, "wgrep: cannot open file\n");
            return 1;
        }

        search_in_stream(file, search_term);
        fclose(file);
    }

    return 0;
}

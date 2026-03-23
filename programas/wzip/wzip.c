#include <stdio.h>
#include <stdlib.h>

static void write_run(int count, int byte_value) {
    fwrite(&count, sizeof(int), 1, stdout);
    fputc(byte_value, stdout);
}

int main(int argc, char *argv[]) {
    int i;
    int previous_byte;
    int current_byte;
    int count;
    int has_data = 0;

    if (argc < 2) {
        fprintf(stderr, "wzip: file1 [file2 ...]\n");
        return 1;
    }

    previous_byte = 0;
    count = 0;

    for (i = 1; i < argc; i++) {
        FILE *file = fopen(argv[i], "rb");

        if (file == NULL) {
            fprintf(stderr, "wzip: cannot open file\n");
            return 1;
        }

        while ((current_byte = fgetc(file)) != EOF) {
            if (!has_data) {
                previous_byte = current_byte;
                count = 1;
                has_data = 1;
            } else if (current_byte == previous_byte) {
                count++;
            } else {
                // When the byte changes, the current run is "closed" and written.
                write_run(count, previous_byte);
                previous_byte = current_byte;
                count = 1;
            }
        }

        fclose(file);
    }

    if (has_data) {
        //This is necessary because the loop only writes when it finds a byte change, 
        //but at the end of the file there is no change to trigger it.
        // If this is not done, the last run would not be written and information would be lost.
        write_run(count, previous_byte);
    }

    return 0;
}

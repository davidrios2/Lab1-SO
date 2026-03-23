#include <stdio.h>
#include <stdlib.h>

static int expand_stream(FILE *file) {
    int count;
    unsigned char byte;

    // It reads pairs of (count, byte) until the end of the file. For each pair, it writes the byte to stdout count times.
    while (fread(&count, sizeof(int), 1, file) == 1) {
        if (fread(&byte, sizeof(unsigned char), 1, file) != 1) {
            return 1;
        }

        while (count > 0) {
            // It writes the byte to stdout count times.
            // Same as in wzip, '>' is handled by the shell.
            fputc(byte, stdout);
            count--;
        }
    }

    return 0;
}

int main(int argc, char *argv[]) {
    int i;

    if (argc < 2) {
        fprintf(stderr, "wunzip: file1 [file2 ...]\n");
        return 1;
    }

    for (i = 1; i < argc; i++) {
        FILE *file = fopen(argv[i], "rb");

        if (file == NULL) {
            fprintf(stderr, "wunzip: cannot open file\n");
            return 1;
        }

        if (expand_stream(file) != 0) {
            fclose(file);
            fprintf(stderr, "wunzip: invalid compressed file\n");
            return 1;
        }

        fclose(file);
    }

    return 0;
}

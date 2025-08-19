#include <stdio.h>
#include <stdlib.h>
void compressFile(const char *inputFile, const char *outputFile) {
    FILE *in = fopen(inputFile, "r");
    FILE *out = fopen(outputFile, "w");
    if (!in || !out) {
        printf("Error opening files!\n");
        exit(1);
    }
    int ch, prev, count;
    prev = fgetc(in);
    if (prev == EOF) {
        fclose(in);
        fclose(out);
        return;
    }
    count = 1;
    while ((ch = fgetc(in)) != EOF) {
        if (ch == prev) {
            count++;
        } else {
            fprintf(out, "%d%c", count, prev);
            prev = ch;
            count = 1;
        }
    }
    fprintf(out, "%d%c", count, prev);  
    fclose(in);
    fclose(out);
    printf("File compressed successfully -> %s\n", outputFile);
}

void decompressFile(const char *inputFile, const char *outputFile) {
    FILE *in = fopen(inputFile, "r");
    FILE *out = fopen(outputFile, "w");
    if (!in || !out) {
        printf("Error opening files!\n");
        exit(1);
    }
    int count;
    char ch;
    while (fscanf(in, "%d%c", &count, &ch) == 2) {
        for (int i = 0; i < count; i++) {
            fputc(ch, out);
        }
    }

    fclose(in);
    fclose(out);
    printf("File decompressed successfully -> %s\n", outputFile);
}
int main() {
    int choice;
    char inputFile[100], outputFile[100];

    while (1) {
        printf("\n--- Run-Length Encoding (RLE) Tool ---\n");
        printf("1. Compress File\n");
        printf("2. Decompress File\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter input file name: ");
                scanf("%s", inputFile);
                printf("Enter output file name: ");
                scanf("%s", outputFile);
                compressFile(inputFile, outputFile);
                break;
            case 2:
                printf("Enter input file name: ");
                scanf("%s", inputFile);
                printf("Enter output file name: ");
                scanf("%s", outputFile);
                decompressFile(inputFile, outputFile);
                break;
            case 3:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}

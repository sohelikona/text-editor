#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void addSpaceAfterWord(char *str) {
    int i = 0, j = 0;
    while (str[i]) {
        if (isspace((unsigned char)str[i])) {

            while (isspace((unsigned char)str[i])) {
                i++;
            }
            if (str[i] != '\0') {
                str[j++] = ' '; 
            }
        }
        if (str[i] != '\0') {
            str[j++] = str[i++];
        }
    }
    str[j] = '\0';
}

int main() {
    char filename[50];
    char text[1000];
    char ch;
    int wordCount = 0;
    int charCount = 0;
    int lineCount = 0;
    char password[20];
    char enteredPassword[20] = "password"; 

    printf("Enter the password: ");
    scanf("%s", password);

    if (strcmp(password, enteredPassword) != 0) {
        printf("Incorrect password. Access denied.\n");
        return 1;
    }

    printf("Enter the filename: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    printf("File contents:\n");
    while ((ch = fgetc(file)) != EOF) {
        printf("%c", ch);

        if (isspace(ch)) {
            wordCount++;
        }

        if (ch == '\n') {
            lineCount++;
        }
        charCount++;
    }
    fclose(file);


    file = fopen(filename, "r");
    FILE *tempFile = fopen("temp.txt", "w");

    while (fgets(text, sizeof(text), file)) {
        addSpaceAfterWord(text);
        fputs(text, tempFile);
    }

    fclose(file);
    fclose(tempFile);

    remove(filename);
    rename("temp.txt", filename);

    file = fopen(filename, "a");

    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    printf("\n\nWord count is %d\n", wordCount + 1);
    printf("Total character is %d\n", charCount);
    printf("Line count is %d\n", lineCount);
    printf("Enter text (type 'exit' to quit):\n");

    while (1) {
        fgets(text, sizeof(text), stdin);

        if (strcmp(text, "exit\n") == 0) {
            break;
        }

        addSpaceAfterWord(text);

        fputs(text, file);
    }

    fclose(file);

    printf("Text saved to %s\n", filename);

    return 0;
}

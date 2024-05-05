#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "handler.h"

void clear_input_buffer() {
    if (VERBOSE) {
        printf("Clearing input buffer\n");
    }
    
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
    fflush(stdin);
}

int encrypt() {
    char plaintext[1000];
    
    if (getInputType() == 1) {
        printf("Enter the plaintext: ");
        fgets(plaintext, sizeof(plaintext), stdin);
        plaintext[strcspn(plaintext, "\n")] = '\0';
    } else {
        char filename[100];
        printf("Enter the filename: ");
        fgets(filename, sizeof(filename), stdin);

        int l;
        for (l = 0; filename[l] != '\0'; ++l) {
            filename[l] = (char)tolower(filename[l]);
        }

        filename[strcspn(filename, "\n")] = '\0';
        FILE *file = fopen(filename, "r");
        if (file == NULL) {
            printf("Error opening file!\n");
            return 1;
        }
        fgets(plaintext, sizeof(plaintext), file);
        fclose(file);
    }

    int shift;
    printf("Enter the shift value: ");
    scanf(" %d", &shift);
    
    printf("Encrypting...\n");
    if(VERBOSE) {
        printf("Calling encryption...\n");
    }

    decrypt_caesar(plaintext, -shift);
    printf("-----------------------------\n");
    printf("Ciphertext: %s\n", plaintext);
    clear_input_buffer();
    return 0;
}

int decrypt() {
    char ciphertext[1000];
    if (getInputType() == 1) {
        printf("Enter the ciphertext: ");
        fgets(ciphertext, sizeof(ciphertext), stdin);
        ciphertext[strcspn(ciphertext, "\n")] = '\0';
    } else {
        char filename[100];
        printf("Enter the filename: ");
        fgets(filename, sizeof(filename), stdin);
        
        int l;
        for (l = 0; filename[l] != '\0'; ++l) {
            filename[l] = (char)tolower(filename[l]);
        }

        filename[strcspn(filename, "\n")] = '\0';
        FILE *file = fopen(filename, "r");
        if (file == NULL) {
            printf("Error opening file!\n");
            return 1;
        }
        fgets(ciphertext, sizeof(ciphertext), file);
        fclose(file);
    }

    int shift;
    printf("Enter the shift value: ");
    scanf(" %d", &shift);

    printf("Decrypting...\n");
    if(VERBOSE) {
        printf("Calling decryption...\n");
    }

    decrypt_caesar(ciphertext, shift);
    printf("-----------------------------\n");
    printf("Plaintext: %s\n", ciphertext);
    clear_input_buffer();
    return 0;
}

int getInputType() {
    if (VERBOSE) {
        printf("Getting input type\n");
    }
    
    int choice;
    printf("Input type\n");
    printf("1. Text\n");
    printf("2. File\n");
    printf("Enter your choice\n->");
    scanf(" %d", &choice);
    if (choice == 1 || choice == 2) {
        printf("-----------------------------\n");
        clear_input_buffer();
        return choice;
    } else {
        printf("Invalid choice!\n");
        return getInputType();
    }
}

int main() {
    int choice;
    int repeat = 1;

    do {
        printf("\n-----------------------------\n");
        printf("\nCaesar Cipher Menu\n");
        printf("1. Encrypt\n");
        printf("2. Decrypt\n");
        printf("3. Crack\n");
        printf("0. Exit\n");
        printf("Enter your choice\n->");
        scanf("%d", &choice);
        printf("\n-----------------------------\n");
        switch (choice) {
            case 0:
                printf("Exiting...\n");
                repeat = 0;
                break;
            case 1:
                if(VERBOSE) {
                    printf("Attempting to encrypt...\n");
                }
                encrypt();
                break;
            case 2:
                if(VERBOSE) {
                    printf("Attempting to decrypt...\n");
                }
                decrypt();
                break;
            case 3:
                if(VERBOSE) {
                    printf("Attempting to crack...\n");
                }
                crack();
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }

    } while (repeat);

    return 0;
}

/*
Code Cat creates compilable code.
    /\__/\
   /__OwO_\
    /    \
    \u__u/
*/
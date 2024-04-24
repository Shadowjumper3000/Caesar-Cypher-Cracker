#include <stdio.h>
#include <string.h>

#include "handler.h"

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int encrypt() {
    char plaintext[100];
    printf("Enter the Plain Text: ");
    clear_input_buffer();
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';

    int shift;
    printf("Enter the shift value: ");
    scanf(" %d", &shift);
    
    printf("Encrypting...\n");
    if(VERBOSE) {
        printf("Calling encryption...\n");
    }

    decrypt_caesar(plaintext, -shift);
    printf("Ciphertext: %s\n", plaintext);
    clear_input_buffer();
    return 0;
}

int decrypt() {
    char ciphertext[100];
    printf("Enter the ciphertext: ");
    clear_input_buffer();
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0';

    int shift;
    printf("Enter the shift value: ");
    scanf(" %d", &shift);

    printf("Decrypting...\n");
    if(VERBOSE) {
        printf("Calling decryption...\n");
    }

    decrypt_caesar(ciphertext, shift);
    printf("Plaintext: %s\n", ciphertext);
    clear_input_buffer();
    return 0;
}

int main() {
    int choice;
    int repeat = 1;

    do {
        printf("Caesar Cipher Menu\n");
        printf("1. Encrypt\n");
        printf("2. Decrypt\n");
        printf("3. Crack\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

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
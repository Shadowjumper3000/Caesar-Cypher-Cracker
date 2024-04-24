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
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';
    int shift;
    printf("Enter the shift value: ");
    scanf("%d", &shift);
    while ((getchar()) != '\n'); // clear input buffer
    printf("Encrypting...\n");
    decrypt_caesar(plaintext, -shift);
    printf("Ciphertext: %s\n", plaintext);
    return 0;
}

int decrypt() {
    char ciphertext[100];
    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0';
    int shift;
    printf("Enter the shift value: ");
    scanf("%d", &shift);
    while ((getchar()) != '\n'); // clear input buffer
    printf("Decrypting...\n");
    decrypt_caesar(ciphertext, shift);
    printf("Plaintext: %s\n", ciphertext);
    return 0;
}

int main() {
    int choice;
    char repeat;

    do {
        printf("Caesar Cipher Menu\n");
        printf("1. Encrypt\n");
        printf("2. Decrypt\n");
        printf("3. Crack\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                encrypt();
                break;
            case 2:
                decrypt();
                break;
            case 3:
                crack();
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }
        printf("Do you want to continue? (Y/N): ");
        scanf(" %c", &repeat);
    } while (repeat == 'Y' || repeat == 'y');

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
#define MAX_COMMON_WORDS 500
#define INT_MAX 2147483647
#define FILENAME "englishLibrary.txt"

// English letter frequency distribution
float english_letter_frequency[ALPHABET_SIZE];

// Common English words
char *common_words[MAX_COMMON_WORDS];

// Function to decrypt Caesar cipher
void decrypt_caesar(char *ciphertext, int shift) {
    int i;
    for (i = 0; ciphertext[i] != '\0'; ++i) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            ciphertext[i] = (char)((((ciphertext[i] - base - shift) % ALPHABET_SIZE) + ALPHABET_SIZE) % ALPHABET_SIZE + base);
        }
    }
}

// Function to calculate letter frequencies
void calculate_letter_frequencies(char *text, float *freq) {
    int i;
    int total_letters = 0;
    for (i = 0; text[i] != '\0'; ++i) {
        if (isalpha(text[i])) {
            ++total_letters;
            ++freq[toupper(text[i]) - 'A'];
        }
    }
    for (i = 0; i < ALPHABET_SIZE; ++i) {
        freq[i] /= (float)total_letters;
    }
}

// Function to calculate score for a shift
int calculate_score(char *text, float *freq) {
    int score = 0;
    float encrypted_frequencies[ALPHABET_SIZE] = {0};
    calculate_letter_frequencies(text, encrypted_frequencies);

    // Score based on letter frequency difference
    int i;
    for (i = 0; i < ALPHABET_SIZE; ++i) {
        score += (abs((int)freq[i] - (int)encrypted_frequencies[i]));
    }

    // Score based on common word occurrence
    for (i = 0; i < MAX_COMMON_WORDS && common_words[i] != NULL; ++i) {
        if (strstr(text, common_words[i]) != NULL) {
            score -= 10; // Decrease score for each occurrence of a common word
        }
    }

    return score;
}

// Function to crack Caesar cipher
int crack_caesar(char *ciphertext, float *freq) {
    int best_shift = 0;
    int best_score = INT_MAX; // Initialize with a large value

    // Try each shift from 1 to 25
    int shift;
    for (shift = 1; shift <= 25; ++shift) {
        char shifted_text[strlen(ciphertext) + 1];
        strcpy(shifted_text, ciphertext);
        decrypt_caesar(shifted_text, shift);
        int score = calculate_score(shifted_text, freq);
        if (score < best_score) {
            best_score = score;
            best_shift = shift;
        }
    }

    return best_shift;
}

// Function to read frequency distribution from a file
void read_frequency_distribution() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", FILENAME);
        return;
    }

    char line[100];
    int i = 0;
    while (fgets(line, sizeof(line), file) != NULL && i < ALPHABET_SIZE) {
        english_letter_frequency[i] = (float)atof(line);
        i++;
    }

    // Read common English words
    char word[100];
    i = 0;
    while (fgets(word, sizeof(word), file) != NULL && i < MAX_COMMON_WORDS) {
        word[strcspn(word, "\n")] = '\0';
        common_words[i] = malloc(strlen(word) + 1);
        strcpy(common_words[i], word);
        i++;
    }

    fclose(file);
}

int main() {
    char choice;
    do {
        char ciphertext[100];
        printf("Enter the ciphertext: ");
        fgets(ciphertext, sizeof(ciphertext), stdin);
        ciphertext[strcspn(ciphertext, "\n")] = '\0';

        // Read frequency distribution and common English words
        read_frequency_distribution();

        // Crack Caesar cipher
        int best_shift = crack_caesar(ciphertext, english_letter_frequency);

        // Decrypt ciphertext with the best shift
        decrypt_caesar(ciphertext, best_shift);
        printf("Best shift: %d\n", best_shift);
        printf("Decrypted message: %s\n", ciphertext);

        // Free memory allocated for common words
        int i;
        for (i = 0; i < MAX_COMMON_WORDS && common_words[i] != NULL; i++) {
            free(common_words[i]);
        }

        printf("Do you want to continue? (Y/N): ");
        scanf(" %c", &choice);
        while ((getchar()) != '\n');

    } while (choice == 'Y' || choice == 'y');

    return 0;
}

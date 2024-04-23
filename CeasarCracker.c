#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
#define MAX_COMMON_WORDS 500
#define INT_MAX 2147483647
#define FILENAME "englishLibrary.txt"

// English letter frequency distribution
float english_letter_frequency[ALPHABET_SIZE] = {
    (float)0.08167, (float)0.01492, (float)0.02782, (float)0.04253, (float)0.12702, (float)0.02228, (float)0.02015, (float)0.06094,
    (float)0.06966, (float)0.00153, (float)0.00772, (float)0.04025, (float)0.02406, (float)0.06749, (float)0.07507, (float)0.01929,
    (float)0.00095, (float)0.05987, (float)0.06327, (float)0.09056, (float)0.02758, (float)0.00978, (float)0.02360, (float)0.00150,
    (float)0.01974, (float)0.00074
};

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
int calculate_score(char *text) {
    int score = 0;
    float encrypted_frequencies[ALPHABET_SIZE] = {0};
    calculate_letter_frequencies(text, encrypted_frequencies);

    // Score based on letter frequency difference
    int i;
    for (i = 0; i < ALPHABET_SIZE; ++i) {
        score += (abs((int)english_letter_frequency[i] - (int)encrypted_frequencies[i]));
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
int crack_caesar(char *ciphertext) {
    int best_shift = 0;
    int best_score = INT_MAX; // Initialize with a large value

    // Try each shift from 1 to 25
    int shift;
    for (shift = 1; shift <= 25; ++shift) {
        char shifted_text[strlen(ciphertext) + 1];
        strcpy(shifted_text, ciphertext);
        decrypt_caesar(shifted_text, shift);
        int score = calculate_score(shifted_text);
        if (score < best_score) {
            best_score = score;
            best_shift = shift;
        }
    }

    return best_shift;
}

// Function to read common English words from a file
void read_common_english_words() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", FILENAME);
        return;
    }

    char word[100];
    int i = 0;
    while (fgets(word, sizeof(word), file) != NULL && i < MAX_COMMON_WORDS) {
        word[strcspn(word, "\n")] = '\0';
        common_words[i] = malloc(strlen(word) + 1);
        strcpy(common_words[i], word);
        i++;
    }

    fclose(file);
}

int main() {
    char ciphertext[100];
    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0';

    // Read common English words
    read_common_english_words();

    // Crack Caesar cipher
    int best_shift = crack_caesar(ciphertext);

    // Decrypt ciphertext with the best shift
    decrypt_caesar(ciphertext, best_shift);
    printf("Decrypted message: %s\n", ciphertext);

    // Free memory allocated for common words
    int i;
    for (i = 0; i < MAX_COMMON_WORDS && common_words[i] != NULL; i++) {
        free(common_words[i]);
    }

    return 0;
}

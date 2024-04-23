#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define ALPHABET_SIZE 26
#define MAX_COMMON_WORDS 500
#define INT_MAX 2147483647

#define VERBOSE 0

// English letter frequency distribution
float letter_frequency[ALPHABET_SIZE];

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
        score += (int)(100 * fabs(freq[i] - encrypted_frequencies[i]));
    }

    // Score based on common word occurrence
    char *lowercase_text = strdup(text);
    for (i = 0; lowercase_text[i]; ++i) {
        lowercase_text[i] = (char)tolower((unsigned char)lowercase_text[i]);
    }

    for (i = 0; i < MAX_COMMON_WORDS && common_words[i] != NULL; ++i) {
        if (strstr(lowercase_text, common_words[i]) != NULL) {
            score += 50; // Decrease score for each occurrence of a common word
        }
    }

    free(lowercase_text);

    return score;
}

// Function to crack Caesar cipher
void crack_caesar(char *ciphertext, float *freq, int *shift_scores) {
    if(VERBOSE) {
        printf("Cracking Caesar cipher...\n");
        printf("frequencies: ");
        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            printf("%.2f ", freq[i]);
        }
        printf("\n");
    }
    // Try each shift from 1 to 25
    int shift;
    for (shift = 0; shift < 25; ++shift) {
        char shifted_text[strlen(ciphertext) + 1];
        strcpy(shifted_text, ciphertext);
        decrypt_caesar(shifted_text, shift + 1);
        int score = calculate_score(shifted_text, freq);
        shift_scores[shift] = score;

        if (VERBOSE) {
            printf("Shift %d: Score %d\n", shift + 1, score);
        }
    }
}

// Function to read frequency distribution from a file
void read_frequency_distribution(char *language) {

    char filename[100];
    sprintf(filename, "libraries/%sLibrary.txt", language);
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return;
    } else {
        printf("%s Language supported\n\n", language);
    }

    char line[100];
    int i = 0;
    while (fgets(line, sizeof(line), file) != NULL && i < ALPHABET_SIZE) {
        letter_frequency[i] = (float)atof(line);
        i++;
    }

    // Read common words
    char word[100];
    i = 0;
    while (fgets(word, sizeof(word), file) != NULL && i < MAX_COMMON_WORDS) {
        word[strcspn(word, "\n")] = '\0';
        common_words[i] = malloc(strlen(word) + 1);
        strcpy(common_words[i], word);
        if(VERBOSE) {
            printf("Read word: %s\n", word);
        }
        i++;
    }

    fclose(file);
}

int main() {
    char choice;
    do {
        char language[100];
        printf("Enter the suspected language of the message\nEnglish, German, Spanish supported: ");
        fgets(language, sizeof(language), stdin);
        language[strcspn(language, "\n")] = '\0';

        // Read frequency distribution and common words
        read_frequency_distribution(language);

        char ciphertext[100];
        printf("Enter the ciphertext: ");
        fgets(ciphertext, sizeof(ciphertext), stdin);
        ciphertext[strcspn(ciphertext, "\n")] = '\0';

        int shift_scores[26]; // Declare the shift_scores array with a size of 26

        // Make a copy of the original ciphertext
        char original_ciphertext[strlen(ciphertext) + 1];
        strcpy(original_ciphertext, ciphertext);

        // Crack Caesar cipher
        crack_caesar(ciphertext, letter_frequency, shift_scores);

        // Find the best shift score
        int best_shift = 0;
        int i;
        for (i = 0; i < 25; ++i) {
            if (shift_scores[i] > shift_scores[best_shift]) {
                best_shift = i;
            }
        }

        // Create an array to keep track of tried shifts
        int tried_shifts[25] = {0};

        // Try to decrypt the ciphertext with the best shift
        int current_shift = best_shift;
        do {
            char decrypted_text[strlen(ciphertext) + 1];
            strcpy(decrypted_text, original_ciphertext);
            decrypt_caesar(decrypted_text, current_shift + 1);
            printf("\nShift %d: %s\n\n", current_shift + 1, decrypted_text);

            // Ask if decryption seems correct
            printf("Does the decryption seem correct? (Y/N): ");
            scanf(" %c", &choice);
            while ((getchar()) != '\n');

            // If decryption is incorrect, find the next best shift
            if (choice == 'N' || choice == 'n') {
                tried_shifts[current_shift] = 1;
                int max_score = -1;
                for (i = 0; i < 25; ++i) {
                    if (!tried_shifts[i] && shift_scores[i] > max_score) {
                        max_score = shift_scores[i];
                        current_shift = i;
                    }
                }
            }
        } while (choice == 'N' || choice == 'n');

        // Free memory allocated for common words
        int j;
        for (j = 0; j < MAX_COMMON_WORDS && common_words[j] != NULL; j++) {
            free(common_words[j]);
        }

        printf("Do you want to continue? (Y/N): ");
        scanf(" %c", &choice);
        while ((getchar()) != '\n');

    } while (choice == 'Y' || choice == 'y');

    return 0;
}

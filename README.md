# Caesar Cipher Cracker

This is a simple Caesar cipher cracker implemented in C. It uses a combination of word detection and common letter weighting to crack passwords encrypted with a Caesar cipher.

## How it Works

The Caesar cipher is a substitution cipher where each letter in the plaintext is shifted a certain number of positions down the alphabet. This cracker attempts to find the correct shift value by analyzing the frequency of letters in the encrypted text and comparing it to the frequency of letters in the English language.

The cracker works as follows:

1. The encrypted text is provided as input.
2. It goes through every possible shift.
3. The cracker analyzes the frequency of letters in the encrypted text.
4. It compares the frequency of letters to the frequency of letters in the English language.
5. It weighs common words of the english language.
6. The cracker calculates the shift value based on the difference in frequencies.
7. It applies the calculated shift value to decrypt the text.
8. The decrypted text is displayed as output.

## Usage

To use the Caesar cipher cracker, follow these steps:

1. Compile the C program using a C compiler.
2. Run the compiled program.
3. Enter the encrypted text when prompted.
4. The cracker will attempt to decrypt the text and display the result.

## Limitations

Please note that this is a simple Caesar cipher cracker and may not be able to crack complex or heavily encrypted passwords. It relies on word detection and common letter weighting, which may not always yield accurate results.

## Contributing

Contributions to this project are welcome. If you have any suggestions or improvements, please feel free to submit a pull request.

## License

This project is licensed under the [MIT License](LICENSE).

# Caesar Cipher Cracker

This is a Caesar Cipher program implemented in C. It provides encryption, decryption, and cracking capabilities. The program works by using common words of the language as well as letter weighting to score possible shifts and return the correct encryption.

## How it Works

1. **Encryption**: The program takes a plaintext or file with plaintext and a shift value as input and provides the encrypted text as output.
2. **Decryption**: The program takes an encrypted text or a file with encrypted text and a shift value as input and provides the decrypted text as output.
3. **Cracking**: The program takes an encrypted text or a file with encrypted text as input. It then goes through every possible shift, calculates a score for each shift based on the frequency of letters and occurrence of common words, and provides the decrypted text with the highest score as output.

## Usage

To use the Caesar Cipher program, follow these steps:

1. Download the source code.
2. Compile the C program using a C compiler.
3. Run the compiled program.
4. Choose the operation you want to perform (encryption, decryption, or cracking) when prompted.
5. Enter the required inputs when prompted.
6. The program will perform the operation and display the result.

## Contributing

Contributions to this project are welcome. If you have any suggestions or improvements, please feel free to submit a pull request.

## License

This project is licensed under the [MIT License](LICENSE).
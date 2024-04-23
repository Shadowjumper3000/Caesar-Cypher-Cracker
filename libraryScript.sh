#!/bin/bash

# Check if a filename is provided as an argument
if [ $# -eq 0 ]; then
    echo "Usage: $0 <input_file>"
    exit 1
fi

# Input and output filenames
input_file="$1"
output_file="${input_file%.txt}_modified.txt"

# Check if the input file exists
if [ ! -f "$input_file" ]; then
    echo "Error: Input file '$input_file' not found!"
    exit 1
fi

# Process the input file
echo "Processing file '$input_file'..."
# Read each line from the input file
while IFS= read -r line; do
    # Remove empty lines
    if [[ -n "$line" ]]; then
        # Replace spaces and tabs with newline characters
        words=$(echo "$line" | tr '[:space:]' '\n')
        # Remove whitespace at the beginning and end of each word
        words=$(echo "$words" | sed 's/^[[:space:]]*//;s/[[:space:]]*$//')
        # Append the modified line to the output file
        echo "$words" >> "$output_file"
    fi
done < "$input_file"

echo "Modified file saved as '$output_file'"

# Huffman File Compressor

A command-line utility built in C++ that performs lossless data compression on any file using the Huffman coding algorithm.

This program reads a source file, builds a Huffman tree based on the frequency of characters, generates prefix-free binary codes, and writes a new, smaller binary file containing the compressed data.

---

## Features

- **Real Compression:** Implements true bitwise I/O to pack data, achieving significant file size reduction for uncompressed files.
- Will Work Well On Uncompressed file types like .txt .csv .json and source code files will be good for storing and transmission

## How to Build and Run

### Prerequisites

- A C++ compiler that supports C++11 or newer (e.g., g++, Clang, MSVC).

### Steps

1.  **Create a Sample File:** Create a text file to compress (e.g., `input.txt`).

2.  **Compile:** Open a terminal in the project directory and compile the source code:

    ```bash
    g++ compressor.cpp -o compress
    ```

3.  **Run:** Execute the program from your terminal, providing the input and output filenames as arguments:

    ```bash
    ./compress input.txt output.huff
    ```

4.  **Check the Result:** The program will print the original and compressed file sizes, and a new `output.huff` file will be created.

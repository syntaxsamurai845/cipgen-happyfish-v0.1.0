# CipGen HappyFish v0.1.0

CipGen HappyFish is a lightweight C++ hobby project designed to experiment with basic encryption concepts. It provides both text-based and byte-level encryption through a simple command-line interface.

---

## Overview

CipGen HappyFish supports:

* **Text encryption and decryption** using a layered system:

  1. Caesar Cipher
  2. Numeric Mapping
  3. String Reversal
  
* **Binary file encryption and decryption** using a reversible byte-shift algorithm.

This project is meant for learning and experimentation, not for production-grade security. It demonstrates how basic encryption, file I/O, and user input can be combined into a clean C++ implementation.

---

## Features

* Text and file encryption/decryption modes
* Fully offline, no external dependencies
* Simple CLI-based user interaction
* Works on any file type (binary and text)
* Modular functions for easy expansion

---

## Build Instructions

1. Clone the repository:

   ```bash
   git clone https://github.com/<your-username>/CipGen-HappyFish.git
   ```
2. Compile the source:

   ```bash
   g++ main.cpp -o cipgen
   ```
3. Run the program:

   ```bash
   ./cipgen
   ```

---

## Example Usage

**Encrypt directly in the terminal**

```
1 -> e -> test -> 3
```

**Decrypt directly in the terminal**

```
1 -> d -> 40114011 -> 3
```

**Encrypt a text file:**

```
2 -> t -> filepath → e
```

**Decrypt a binary file:**

```
2 -> b → filepath -> d
```

---

## Disclaimer

This project is for educational and hobby purposes only. It should **not** be used for real security applications. The encryption algorithms are intentionally simple to help understand core principles.

---

## Author

Created by SyntaxSamurai as a personal learning project exploring encryption, file manipulation, and C++ design.

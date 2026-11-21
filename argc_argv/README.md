# 0x0A. Argc and Argv

## Description

This project introduces command-line arguments in C. It covers how to use `argc` and `argv` to access arguments passed to a program.

## Learning Objectives

- Understand how to use arguments passed to a program.
- Know the two common prototypes of `main`.
- Understand the meaning of `argc` and `argv`.
- Learn how to handle unused variables and parameters using `(void)` and `__attribute__((unused))`.

## Requirements

- Ubuntu 20.04 LTS
- GCC compiler
- Betty coding style
- Compilation flags: `-Wall -Werror -Wextra -pedantic -std=gnu89`
- All files end with a new line.
- No global variables.
- Maximum of 5 functions per file.

## Tasks

### 0. It ain't what they call you, it's what you answer to

Write a program that prints its own name, followed by a new line. The program name is obtained dynamically using `argv[0]`, so renaming the executable does not require recompiling the program.

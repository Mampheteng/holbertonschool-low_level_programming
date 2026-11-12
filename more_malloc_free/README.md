# 0x0B. malloc, free

## Description

This project introduces dynamic memory allocation in C using malloc and free.

## Requirements

- Ubuntu 20.04 LTS
- GCC
- Betty coding style
- All files compiled using:
  `gcc -Wall -Werror -Wextra -pedantic -std=gnu89`

## Tasks

### 0. Trust no one

Write a function called `malloc_checked` that allocates memory using malloc.

- Returns a pointer to the allocated memory.
- If malloc fails, the function terminates the process with exit status 98.

## Files

- `main.h` - Header file containing function prototypes.
- `0-malloc_checked.c` - Implementation of malloc_checked.


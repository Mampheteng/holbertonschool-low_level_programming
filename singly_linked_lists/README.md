# Singly Linked Lists

This project covers the implementation and use of singly linked lists in C.

## Description

A singly linked list is a data structure made up of nodes. Each node contains data and a pointer to the next node in the list.

## Data Structure

The project uses the following structure:

```c
typedef struct list_s
{
	char *str;
	unsigned int len;
	struct list_s *next;
} list_t;
```

## Files

| File | Description |
|---|---|
| `lists.h` | Header file containing the list structure and function prototypes |
| `0-print_list.c` | Function that prints all elements of a `list_t` list |

## Compilation

Compile the source file using:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 0-main.c 0-print_list.c -o a
```

## Requirements

- Ubuntu 20.04
- GCC
- Betty coding style

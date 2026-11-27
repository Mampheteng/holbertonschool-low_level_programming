# Valgrind Analysis — AI Memory Visualizer + Valgrind Tracer

## 1. Introduction

The purpose of this analysis is to connect Valgrind Memcheck reports to actual memory behavior in the four C programs.

I used the following command to run each program:

```bash
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./program_name
```

This helped identify invalid memory accesses, memory leaks, and memory that remained reachable at program termination.

## 2. Stack Example

### Program: `stack_example`

**Valgrind result:**

- Total heap usage: 1 allocation and 1 free.
- Memory in use at exit: 0 bytes.
- No memory leaks.
- Error summary: 0 errors from 0 contexts.

### Memory reasoning

The program uses recursive function calls to demonstrate stack frames and local-variable lifetimes.

Each active call to `walk_stack()` has its own local `marker` variable. The recursive calls reach depths 0, 1, 2, and 3, then return in reverse order.

The `dump_frame()` function also declares local variables:

- `local_int`
- `local_buf`
- `p_local`

The pointer `p_local` refers to `local_int`. It does not allocate additional heap memory.

### Valgrind interpretation

Valgrind reported no invalid reads, invalid writes, or memory leaks.

The single allocation and free shown in the heap summary are associated with runtime output buffering, not an allocation made by the program's own memory-management code.

**Conclusion:** The program completed without detected memory errors. Its local variables have lifetimes associated with their function calls, and the program does not explicitly allocate heap memory.

## 3. Heap Example

### Program: `heap_example`

**Valgrind result:**

- Total heap usage: 5 allocations and 4 frees.
- Memory in use at exit: 6 bytes in 1 block.
- Definitely lost: 6 bytes in 1 block.
- Error summary: 1 error from 1 context.

### Identifying the memory object

The `person_new()` function allocates two separate objects for each person:

1. A `Person` structure.
2. A character array for the person's name.

For Alice, the name allocation is 6 bytes: five characters plus the terminating null character.

The `person_new()` function allocates the `Person` structure and its name string. The returned `Person` pointer gives the caller responsibility for managing the allocated objects. Before releasing a `Person` structure, its separately allocated `name` must also be freed. In this example, Bob's name and structure are both released, but Alice's name is not. Freeing Alice's structure loses the only remaining reference to her allocated name.

### Exact source of the error

The name is allocated at:

`heap_example.c:21`

The allocation is reached when Alice is created at:

`heap_example.c:51`

The problem is in `person_free_partial()`:

```c
static void person_free_partial(Person *p)
{
    if (!p)
        return;

    free(p);
}
```

This function frees the structure but does not free the separately allocated name.

When `person_free_partial(alice)` executes, the `Person` structure is released. However, the allocated memory containing `"Alice"` remains allocated, and its pointer is lost when the structure is freed.

### Error classification

**Definitely lost memory leak due to lost ownership.**

The leaked object is Alice's dynamically allocated name string.

### Valgrind interpretation

Valgrind reported:

```text
6 bytes in 1 blocks are definitely lost
```

The report identifies the allocation in `person_new()` at line 21 and traces it to Alice's creation in `main()` at line 51.

Bob's name and structure are both freed correctly. Alice's structure is freed, but her name is not.

**Conclusion:** The program contains one definite memory leak because the name allocation is not released before its owning structure is freed.

## 4. Aliasing Example

### Program: `aliasing_example`

**Valgrind result:**

- Total heap usage: 2 allocations and 2 frees.
- Memory in use at exit: 0 bytes.
- Error summary: 3 errors from 3 contexts.
- No memory leaks.

### Identifying the memory object

The function `make_numbers()` allocates memory for five integers using `malloc()`.

The allocation is 20 bytes on this system.

In `main()`, the following assignment occurs:

```c
b = a;
```

This copies the pointer address, not the allocated data.

Both pointers refer to the same heap allocation.

### Exact source of the errors

The program executes:

```c
free(a);
```

This releases the allocated block.

However, `b` still contains the old address. It becomes a dangling pointer.

The following operations then access the released memory:

1. `aliasing_example.c:42` — reading `b[2]`.
2. `aliasing_example.c:44` — writing to `b[3]`.
3. `aliasing_example.c:45` — reading `b[3]`.

### Error classification

- Line 42: Invalid read of size 4.
- Line 44: Invalid write of size 4.
- Line 45: Invalid read of size 4.

All three are use-after-free errors.

The four-byte access corresponds to the size of an integer on this system.

### Valgrind interpretation

Valgrind traced the invalid accesses to the memory block that had been allocated by `make_numbers()` at line 12 and freed by `free(a)` at line 38.

The fact that the heap summary reports zero bytes in use does not mean the program is free from memory errors.

The allocation was released, but the program continued accessing it through the dangling pointer `b`.

**Conclusion:** The program demonstrates pointer aliasing and use-after-free. Both pointers refer to one allocation, and freeing the allocation through one pointer makes access through the other pointer invalid.

## 5. Crash Example

### Program: `crash_example`

**Valgrind result:**

- Invalid write of size 4.
- Process terminated with signal 11 (`SIGSEGV`).
- Error summary: 1 error from 1 context.
- Definitely lost: 0 bytes.
- Still reachable: 1,024 bytes in 1 block.

### Identifying the memory object

In `main()`, the program initializes:

```c
int *nums = NULL;
int n = 0;
```

It then calls:

```c
nums = allocate_numbers(n);
```

Inside `allocate_numbers()`, the condition:

```c
if (n <= 0)
    return NULL;
```

is true because `n` is zero.

The function returns `NULL` before calling `malloc()`.

### Exact source of the error

The program then executes:

```c
nums[0] = 42;
```

This attempts to write an integer through a NULL pointer.

Valgrind identifies the invalid write at:

`crash_example.c:32`

### Error classification

**NULL pointer dereference resulting in an invalid write.**

Valgrind reports an access at address `0x0`, which is not a valid allocated memory location.

The invalid write causes a segmentation fault (`SIGSEGV`).

### Understanding the remaining 1,024 bytes

Valgrind also reports:

```text
still reachable: 1,024 bytes in 1 blocks
definitely lost: 0 bytes
```

The allocation originates from the C library's standard output buffering, through `_IO_file_doallocate`.

It is not an allocation made by `allocate_numbers()`.

It is classified as still reachable, not definitely lost.

**Conclusion:** The program crashes because it writes through a NULL pointer. The report does not identify a definite memory leak from the program's own allocation function.

## 6. Uninitialized Memory Checks

I used `--track-origins=yes` during the Memcheck runs to help identify the origins of uninitialized values if they were reported.

No uninitialized-value errors were reported in the captured runs.

## 7. Critical Review of AI Explanations

AI explanations were useful as a starting point, but I verified them against the source code and Valgrind output.

### Example 1: Heap allocation count

An initial AI explanation described four heap allocations for the two `Person` objects and their two names.

That description covered the four allocations made by the program's own `person_new()` calls, but it was incomplete as an explanation of the full Valgrind heap summary.

Valgrind reported five allocations and four frees because the C runtime also allocated memory for standard output buffering.

This distinction matters because not every allocation reported by Valgrind necessarily comes directly from the program's own `malloc()` calls.

### Example 2: Pointer aliasing

An AI explanation could incorrectly suggest that:

```c
b = a;
```

creates a second copy of the allocated array.

This is incorrect. The assignment copies the pointer value, not the contents of the allocated memory.

I verified this using the program output, which showed that `a` and `b` contained the same address.

Valgrind then confirmed that accessing the allocation through `b` after freeing it through `a` caused invalid reads and writes.

### Independent verification

I checked the explanations against:

- The actual C source code.
- The memory maps created in Task 0.
- The runtime output of each program.
- The source-code line references and memory summaries reported by Valgrind.

This helped distinguish actual memory errors from allocations made by the runtime environment.

## 8. Final Summary

| Program | Finding | Result |
|---|---|---|
| `stack_example` | No detected memory errors | 0 errors |
| `heap_example` | Definitely lost allocation | 6-byte leak |
| `aliasing_example` | Use-after-free | 3 invalid accesses |
| `crash_example` | NULL pointer dereference | 1 invalid write |

The Valgrind results demonstrate that different memory problems can occur independently.

A program can have no memory leaks but still contain invalid memory accesses, as demonstrated by `aliasing_example`.

Likewise, a program can terminate with a segmentation fault because of an invalid write through a NULL pointer, as demonstrated by `crash_example`.

The main lesson is that every Valgrind report should be connected to the actual memory object, its allocation and deallocation history, and the operation that violated its lifetime or valid usage.

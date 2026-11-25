
# Memory Maps: Stack and Aliasing Examples

## 1. Stack Example

### Program execution

The program starts in `main()`, which calls `walk_stack(0, 3)`.

The `walk_stack()` function calls itself recursively until the depth reaches 3.

The calls happen in this order:

1. `walk_stack(0, 3)`
2. `walk_stack(1, 3)`
3. `walk_stack(2, 3)`
4. `walk_stack(3, 3)`

After reaching depth 3, the function calls return in reverse order: 3, 2, 1, 0. This is the Last In, First Out (LIFO) behavior of the call stack.

### Conceptual stack frames

Each active call to `walk_stack()` has its own local `marker` variable.

| Depth | marker value |
|---|---:|
| 0 | 0 |
| 1 | 10 |
| 2 | 20 |
| 3 | 30 |

The local variables remain alive while their function calls are active. For example, the `marker` belonging to depth 0 remains alive while the deeper recursive calls execute.

### Local variables in `dump_frame()`

The function `dump_frame()` declares:

- `local_int`: an integer local variable.
- `local_buf`: a local character array of 16 bytes.
- `p_local`: a pointer that stores the address of `local_int`.

The statement `int *p_local = &local_int;` does not allocate heap memory. It makes the pointer refer to the local integer.

The buffer stores a character based on the recursion depth:
- Depth 0: A
- Depth 1: B
- Depth 2: C
- Depth 3: D

Each call to `dump_frame()` creates its own local variables. These variables cease to exist when that function call returns.

### Observed memory addresses

In my program output, the addresses of local variables differed between recursive calls. The addresses appeared lower as recursion depth increased.

This is what happened on my system during this run. However, C does not guarantee that stack addresses must increase or decrease in a particular direction.

The `dump_frame()` function is called twice at each depth: once when entering and once when exiting. Matching addresses between those two calls do not mean the same local objects remained alive. The earlier call had already returned, so the compiler could reuse the same stack storage.

### Stack and heap distinction

The program uses local variables and recursive function calls to demonstrate stack behavior.

There are no explicit calls to `malloc()`, `calloc()`, or `realloc()` in `stack_example.c`, so the program does not explicitly allocate heap memory.

### Important correction to a possible AI explanation

An AI explanation might claim that every local variable is guaranteed by the C language to be physically stored on the stack.

That is too absolute. The stack is a useful way to understand function calls and local-variable lifetimes, but the C language does not require a particular physical memory layout. A compiler may optimize how variables are stored.

For this exercise, the stack-frame diagrams are conceptual models supported by the observed program output.


## 2. Aliasing Example

### Heap allocation

The `make_numbers(5)` function allocates memory for five integers using `malloc()`.

The allocation requires 20 bytes on this system because each integer occupies 4 bytes.

The allocated values are:

| Index | Value |
|---|---:|
| 0 | 0 |
| 1 | 11 |
| 2 | 22 |
| 3 | 33 |
| 4 | 44 |

### Pointer aliasing

In `main()`, the program executes:

```c
a = make_numbers(n);
b = a;
```

Both pointers store the same memory address. They are aliases because they refer to the same allocated memory.

Conceptual memory map:

```text
a ─────┐
       ├────> Heap allocation (5 integers)
b ─────┘       [0] [11] [22] [33] [44]
```

The pointers are separate variables, but they refer to the same allocated block.

### Use-after-free

The statement `free(a)` releases the allocated heap memory.

However, freeing memory through `a` does not automatically update `b`. Both pointers still contain the old address, but neither should be used to access the released allocation.

The program then performs three invalid operations:

1. Reads `b[2]` after the memory has been freed.
2. Writes `1234` to `b[3]` after the memory has been freed.
3. Reads `b[3]` after the memory has been freed.

These are use-after-free errors.

### Valgrind results

I ran the program using:

```bash
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./aliasing_example
```

Valgrind reported:

- Invalid read at line 42.
- Invalid write at line 44.
- Invalid read at line 45.
- Three errors from three contexts.
- Zero bytes in use at exit.
- No memory leaks.

The report confirms that the program accesses memory after it has been freed, even though all allocated blocks were eventually released.

### Important correction to a possible AI explanation

An AI explanation might suggest that `b = a` creates a second allocation. This is incorrect.

The assignment copies the pointer address, not the allocated data. Both pointers refer to the same allocation.

Freeing the allocation through one pointer makes the allocation unavailable through every alias.

Setting `a = NULL` after freeing it would not automatically make `b` safe. The program must not access the released memory through any pointer.


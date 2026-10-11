# ft_printf — Custom Formatted Output Printf Engine

Engineered and developed by [Ayham Shalabi](https://github.com/ayhamshalabi)  
[https://github.com/ayhamshalabi](https://github.com/ayhamshalabi)

![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c)
![Build](https://img.shields.io/badge/Build-Passing-brightgreen?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

> A lightweight, modular static C library (`libftprintf.a`) re-implementing the standard C `printf()` formatting engine with zero heap allocation overhead, supporting character, string, numeric, hexadecimal, and pointer memory address conversions.

---

## Table of Contents

- [Overview](#overview)
- [About the Author](#about-the-author)
- [Supported Conversion Specifiers](#supported-conversion-specifiers)
- [Library Architecture & Description](#library-architecture--description)
  - [Variadic Argument Processing](#variadic-argument-processing)
  - [Zero Heap Allocation Philosophy](#zero-heap-allocation-philosophy)
  - [Modular Translation Units](#modular-translation-units)
- [Quick Navigation Index](#quick-navigation-index)
- [Instructions](#instructions)
  - [Prerequisites](#prerequisites)
  - [Compilation & Makefile Targets](#compilation--makefile-targets)
  - [Linking ft_printf in Your Project](#linking-ft_printf-in-your-project)
  - [Running the Built-in Test Suite](#running-the-built-in-test-suite)
- [Detailed Function Breakdown](#detailed-function-breakdown)
  - [Core Parsing & Dispatching Engine](#core-parsing--dispatching-engine)
  - [Character & String Formatters](#character--string-formatters)
  - [Signed & Unsigned Decimal Formatters](#signed--unsigned-decimal-formatters)
  - [Hexadecimal & Pointer Address Formatters](#hexadecimal--pointer-address-formatters)
- [Resources & References](#resources--references)
- [License](#license)

---

## Overview

In C systems programming, formatted output conversion through `printf()` is one of the most widely used I/O interfaces. This project re-engineers the standard `printf()` routine from the ground up, utilizing low-level POSIX system calls (`write`) and ANSI C variadic argument abstractions (`<stdarg.h>`).

The resulting archive—`libftprintf.a`—serves as an independent, embeddable formatted printing engine that evaluates format strings, extracts arguments with proper promotion rules, writes formatted byte streams directly to file descriptor 1 (stdout), and returns the exact number of characters transmitted.

### Key Technical Attributes
- **Zero Heap Footprint ($O(1)$ Memory):** Operates entirely on stack memory without dynamic heap allocations (`malloc`/`free`), eliminating potential memory leaks.
- **Recursive Base Conversion:** Formats decimal, unsigned, hexadecimal, and pointer addresses using mathematical recursion, avoiding auxiliary string buffer overflows.
- **Defensive Edge Case Handling:** Robust support for negative integer boundaries (`INT_MIN`), unsigned limits (`UINT_MAX`), `NULL` string pointers (`(null)`), and `NULL` memory addresses (`(nil)`).
- **Clean Namespace Isolation:** Internal helper subroutines are statically scoped (`static`) within their translation units to prevent symbol collisions when linking with external codebases.

---

## About the Author

Engineered and developed by **Ayham Shalabi**.

- **GitHub Profile:** [https://github.com/ayhamshalabi](https://github.com/ayhamshalabi)
- **Project Repository:** [https://github.com/ayhamshalabi/ft_printf](https://github.com/ayhamshalabi/ft_printf)

---

## Supported Conversion Specifiers

| Specifier | Argument Type | Formatted Output Description | Example Input | Output |
| :--- | :--- | :--- | :--- | :--- |
| `%c` | `int` | Prints a single character (respects NUL bytes) | `'A'` | `A` |
| `%s` | `char *` | Prints a string; outputs `(null)` if pointer is `NULL` | `"Hello"` | `Hello` |
| `%p` | `void *` | Prints a pointer memory address in lowercase hex prefixed with `0x` (outputs `(nil)` on `NULL`) | `&variable` | `0x7ffee1b5c4` |
| `%d` | `int` | Prints a signed decimal integer (base 10) | `-1024` | `-1024` |
| `%i` | `int` | Prints a signed integer in base 10 | `123` | `123` |
| `%u` | `unsigned int` | Prints an unsigned decimal integer (base 10) | `4000000000U` | `4000000000` |
| `%x` | `unsigned int` | Prints an unsigned number in lowercase hexadecimal (base 16) | `255` | `ff` |
| `%X` | `unsigned int` | Prints an unsigned number in uppercase hexadecimal (base 16) | `255` | `FF` |
| `%%` | None | Prints a literal percent symbol | None | `%` |

---

## Library Architecture & Description

The project is structured into focused translation units, compiling into the static archive `libftprintf.a`:

```
ft_printf/
├── ft_printf.h          # Header file defining public API and module prototypes
├── Makefile             # Build automation script
├── ft_printf.c          # Top-level formatting loop & dispatcher
├── ft_printf_char.c     # Character and string conversion routines
├── ft_printf_nbr.c      # Signed and unsigned decimal arithmetic converters
├── ft_printf_hex.c      # Hexadecimal and pointer address converters
├── main.c               # Comprehensive unit test harness comparing against libc
├── .gitignore           # Build artifact exclusions
├── LICENSE              # MIT License
└── README.md            # Technical documentation
```

### Variadic Argument Processing
C variadic functions utilize macros defined in `<stdarg.h>`:
1. `va_start(args, format)` initializes the argument list pointer immediately after the named parameter `format`.
2. `va_arg(args, type)` retrieves the next argument from the stack or CPU registers. Standard C integer promotion rules apply: types smaller than `int` (e.g., `char`, `short`) are promoted to `int` when passed through variadic ellipses.
3. `va_end(args)` performs cleanup on the argument list pointer prior to function return.

### Zero Heap Allocation Philosophy
Many string formatting engines allocate temporary heap buffers with `malloc()`, risking allocation failures and memory leaks. In contrast, `ft_printf` uses **direct recursive writing**:
- Output characters are written directly to stdout via `write(1, ...)`.
- Number formatting uses the runtime call stack to reverse digits on-the-fly, requiring $O(\log_{base} N)$ stack frames and exactly zero bytes of heap memory.

---

## Quick Navigation Index

| Function | Prototype | Category | Summary |
| :--- | :--- | :--- | :--- |
| [`ft_printf`](#ft_printf) | `int ft_printf(const char *format, ...);` | Public API | Entry-point parsing format string and dispatching specifiers |
| [`ft_format`](#ft_format) | `static int ft_format(char specifier, va_list args);` | Dispatcher | Routes specifier character to specific converter |
| [`ft_putchar`](#ft_putchar) | `static int ft_putchar(char c);` | Character | Writes single character to stdout and returns 1 |
| [`ft_putstr`](#ft_putstr) | `static int ft_putstr(char *s);` | String | Writes null-terminated string or `(null)` |
| [`ft_printf_char`](#ft_printf_char) | `int ft_printf_char(char specifier, va_list args);` | Module Handler | Manages `%c`, `%s`, and `%%` conversions |
| [`ft_putnbr`](#ft_putnbr) | `static int ft_putnbr(int n);` | Numeric | Recursively prints signed 32-bit integer |
| [`ft_putunsigned`](#ft_putunsigned) | `static int ft_putunsigned(unsigned int n);` | Numeric | Recursively prints unsigned 32-bit integer |
| [`ft_printf_nbr`](#ft_printf_nbr) | `int ft_printf_nbr(char specifier, va_list args);` | Module Handler | Manages `%d`, `%i`, and `%u` conversions |
| [`ft_puthex`](#ft_puthex) | `static int ft_puthex(char specifier, unsigned long n);` | Hexadecimal | Recursively prints base-16 number in upper/lower case |
| [`ft_putptr`](#ft_putptr) | `static int ft_putptr(void *ptr);` | Pointer | Prints `0x` prefix followed by hex address, or `(nil)` |
| [`ft_printf_hex`](#ft_printf_hex) | `int ft_printf_hex(char specifier, va_list args);` | Module Handler | Manages `%x`, `%X`, and `%p` conversions |

---

## Instructions

### Prerequisites
- Compiler: `cc`, `gcc`, or `clang`
- Build System: GNU `make`
- Archiver: `ar`
- Environment: Linux, macOS, or Windows (WSL2 / MinGW)

### Compilation & Makefile Targets

Clone the repository and build the archive:
```bash
git clone https://github.com/ayhamshalabi/ft_printf.git
cd ft_printf
```

Manage the build lifecycle using the provided `Makefile`:
```bash
# Compile all translation units and create libftprintf.a
make

# Remove intermediate object files (*.o)
make clean

# Remove object files and the static library archive (libftprintf.a)
make fclean

# Rebuild the library from scratch
make re
```

### Linking ft_printf in Your Project

To use `libftprintf.a` in your C application:

1. Include the header file:
   ```c
   #include "ft_printf.h"
   ```

2. Compile and link against the static archive:
   ```bash
   # Method A: Direct archive path
   cc main.c libftprintf.a -o my_app

   # Method B: Linker flags
   cc main.c -L. -lftprintf -o my_app
   ```

### Running the Built-in Test Suite

A comprehensive test suite is provided in [`main.c`](main.c) that exercises all specifiers, combos, boundary values, and compares character output counts directly against libc's standard `printf()`:

```bash
# 1. Compile the static library
make

# 2. Compile the test executable with libftprintf.a
cc main.c libftprintf.a -o test_runner

# 3. Execute the tests
./test_runner
```

---

## Detailed Function Breakdown

---

### Core Parsing & Dispatching Engine

#### `ft_printf`
```c
int ft_printf(const char *format, ...);
```
- **File:** [`ft_printf.c`](ft_printf.c)
- **Parameters:** `format` — Format control string; `...` — Variable arguments matching conversion specifiers.
- **Return Value:** Total count of characters written to stdout, or `-1` if `format` is `NULL`.
- **Approach:**
  1. Validates that `format` is not `NULL`.
  2. Initializes variadic tracking via `va_start(args, format)`.
  3. Sequentially scans through `format`:
     - If encountering `%` followed by a specifier (`format[i + 1]`), invokes `ft_format(format[++i], args)` and accumulates the returned character count.
     - Otherwise, writes the literal character via `write(1, &format[i], 1)` and increments `len`.
  4. Finalizes variadic state with `va_end(args)` and returns `len`.
- **Optimization Tricks:** In-line index increment `format[++i]` seamlessly advances the scanner past both the `%` and specifier character in a single step.

#### `ft_format`
```c
static int ft_format(char specifier, va_list args);
```
- **File:** [`ft_printf.c`](ft_printf.c)
- **Parameters:** `specifier` — Conversion character (e.g. `'s'`, `'d'`, `'x'`); `args` — Active `va_list` reference.
- **Return Value:** Number of characters printed by the delegated handler.
- **Approach:** Evaluates `specifier` using concise branch clusters:
  - Dispatches `'c'`, `'s'`, and `'%'` to `ft_printf_char`.
  - Dispatches `'d'`, `'i'`, and `'u'` to `ft_printf_nbr`.
  - Dispatches `'x'`, `'X'`, and `'p'` to `ft_printf_hex`.
  - For unrecognized specifiers, prints literal `%` and the character (`write(1, "%", 1); write(1, &specifier, 1); return (2);`).

---

### Character & String Formatters

#### `ft_printf_char`
```c
int ft_printf_char(char specifier, va_list args);
```
- **File:** [`ft_printf_char.c`](ft_printf_char.c)
- **Parameters:** `specifier` — Conversion specifier; `args` — Variadic argument list.
- **Return Value:** Printed character count.
- **Approach:**
  - `'c'`: Extracts character with `va_arg(args, int)` (due to default promotion) and invokes `ft_putchar`.
  - `'s'`: Extracts pointer with `va_arg(args, char *)` and invokes `ft_putstr`.
  - `'%'`: Directly writes literal `'%'` via `ft_putchar('%')`.

#### `ft_putchar`
```c
static int ft_putchar(char c);
```
- **File:** [`ft_printf_char.c`](ft_printf_char.c)
- **Parameters:** `c` — Character byte to write.
- **Return Value:** Number of bytes written (1).
- **Approach:** Directly invokes `write(1, &c, 1)`.

#### `ft_putstr`
```c
static int ft_putstr(char *s);
```
- **File:** [`ft_printf_char.c`](ft_printf_char.c)
- **Parameters:** `s` — Null-terminated string pointer.
- **Return Value:** Number of characters written.
- **Approach:** If `s` is `NULL`, outputs `(null)` and returns `6`. Otherwise, iterates through `s`, writing character-by-character to stdout and tracking total output count.

---

### Signed & Unsigned Decimal Formatters

#### `ft_printf_nbr`
```c
int ft_printf_nbr(char specifier, va_list args);
```
- **File:** [`ft_printf_nbr.c`](ft_printf_nbr.c)
- **Parameters:** `specifier` — Conversion specifier (`'d'`, `'i'`, or `'u'`); `args` — Variadic list.
- **Return Value:** Total digits and signs printed.
- **Approach:**
  - `'d'` / `'i'`: Retrieves signed `int` via `va_arg(args, int)` and delegates to `ft_putnbr`.
  - `'u'`: Retrieves unsigned value via `va_arg(args, unsigned int)` and delegates to `ft_putunsigned`.

#### `ft_putnbr`
```c
static int ft_putnbr(int n);
```
- **File:** [`ft_printf_nbr.c`](ft_printf_nbr.c)
- **Parameters:** `n` — Signed 32-bit integer.
- **Return Value:** Number of characters printed.
- **Approach:**
  1. Casts `n` to `long nb` to prevent integer overflow when taking `-nb` on `INT_MIN` (`-2147483648`).
  2. If negative, writes `'-'`, increments `len`, and negates `nb`.
  3. If `nb >= 10`, recursively invokes `ft_putnbr(nb / 10)` and accumulates `len`.
  4. Writes current least-significant digit `(nb % 10) + '0'` and increments `len`.
- **Optimization Tricks:** Using a `long` accumulator guarantees full compliance across all 32-bit integer values without special-case branches for `INT_MIN`.

#### `ft_putunsigned`
```c
static int ft_putunsigned(unsigned int n);
```
- **File:** [`ft_printf_nbr.c`](ft_printf_nbr.c)
- **Parameters:** `n` — Unsigned 32-bit integer.
- **Return Value:** Number of digits printed.
- **Approach:** Recursively divides `n / 10` while `n >= 10`, printing digits in forward order using stack unwind.

---

### Hexadecimal & Pointer Address Formatters

#### `ft_printf_hex`
```c
int ft_printf_hex(char specifier, va_list args);
```
- **File:** [`ft_printf_hex.c`](ft_printf_hex.c)
- **Parameters:** `specifier` — Conversion specifier (`'x'`, `'X'`, or `'p'`); `args` — Variadic list.
- **Return Value:** Characters printed.
- **Approach:**
  - `'x'` / `'X'`: Retrieves `unsigned int` via `va_arg(args, unsigned int)` and delegates to `ft_puthex`.
  - `'p'`: Retrieves generic pointer via `va_arg(args, void *)` and delegates to `ft_putptr`.

#### `ft_puthex`
```c
static int ft_puthex(char specifier, unsigned long n);
```
- **File:** [`ft_printf_hex.c`](ft_printf_hex.c)
- **Parameters:** `specifier` — `'x'` for lowercase or `'X'` for uppercase; `n` — Unsigned 64-bit value.
- **Return Value:** Number of hexadecimal digits printed.
- **Approach:**
  - Selects base character lookup table: `"0123456789abcdef"` for `'x'` or `"0123456789ABCDEF"` for `'X'`.
  - If `n >= 16`, recursively divides `n / 16`.
  - Writes current hex digit `base[n % 16]` and accumulates total length.
- **Optimization Tricks:** Taking `unsigned long` allows the exact same function to format both 32-bit integer hex conversions (`%x`/`%X`) and 64-bit pointer addresses (`%p`).

#### `ft_putptr`
```c
static int ft_putptr(void *ptr);
```
- **File:** [`ft_printf_hex.c`](ft_printf_hex.c)
- **Parameters:** `ptr` — Generic memory pointer address.
- **Return Value:** Characters written.
- **Approach:**
  - If `ptr` is `NULL`, outputs `(nil)` and returns `5` (matching Linux glibc behavior).
  - Otherwise, writes the `"0x"` prefix (2 bytes), casts pointer to `unsigned long addr`, and delegates conversion to `ft_puthex('x', addr)`.

---

## Resources & References

### Official System Documentation & Standards
- [FreeBSD printf(3) Manual](https://man.freebsd.org/cgi/man.cgi?query=printf&sektion=3) — Definitive specification for formatted output conversion and specifiers.
- [FreeBSD stdarg(3) Manual](https://man.freebsd.org/cgi/man.cgi?query=stdarg&sektion=3) — Variadic argument list macros (`va_start`, `va_arg`, `va_end`).
- [FreeBSD write(2) System Call](https://man.freebsd.org/cgi/man.cgi?query=write&sektion=2) — Direct unbuffered kernel write operations.
- [FreeBSD Libc Source: vfprintf.c](https://github.com/freebsd/freebsd-src/blob/main/lib/libc/stdio/vfprintf.c) — Official BSD reference implementation for formatted printing.
- [ISO/IEC C Reference: fprintf family (cppreference.com)](https://en.cppreference.com/w/c/io/fprintf) — Standardized C documentation for formatted I/O operations and conversion specifiers.

### Seminal Literature
- [Brian W. Kernighan & Dennis M. Ritchie: The C Programming Language (2nd Edition)](https://en.wikipedia.org/wiki/The_C_Programming_Language) — Chapter 7: Input and Output (Formatted Output — `printf` and Variable-length Argument Lists).

---

## License

This project is open-source and available under the [MIT License](LICENSE).
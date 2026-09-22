*This activity has been created as part of the 42 curriculum by ayhshala.*

# Description

The **ft_printf** project is a fundamental milestone in the 42 curriculum. The goal of this project is to recode libc's well-known `printf()` function, learning about variadic functions in C and creating a modular, extensible static library named `libftprintf.a`.

This implementation mimics standard `printf()` behavior (without buffer management) by parsing a format string, extracting variable arguments, writing formatted output to file descriptor 1 (standard output), and returning the total count of printed characters.

### Supported Conversion Specifiers

| Specifier | Description |
| :--- | :--- |
| `%c` | Prints a single character. |
| `%s` | Prints a string (handles `NULL` pointers by outputting `(null)`). |
| `%p` | Prints a `void *` pointer memory address in lowercase hex prefixed with `0x` (outputs `(nil)` on `NULL` pointers). |
| `%d` | Prints a signed decimal (base 10) number. |
| `%i` | Prints a signed integer in base 10. |
| `%u` | Prints an unsigned decimal (base 10) number. |
| `%x` | Prints an unsigned number in lowercase hexadecimal format (base 16). |
| `%X` | Prints an unsigned number in uppercase hexadecimal format (base 16). |
| `%%` | Prints a literal percent sign. |

---

# Instructions

### Compilation

The library is built using the provided `Makefile`, which adheres strictly to 42 standards (compiles with `cc`, flags `-Wall -Wextra -Werror`, and packages the object files using `ar rcs`):

```bash
# Build the static library libftprintf.a
make

# Clean object files (.o)
make clean

# Clean object files and libftprintf.a
make fclean

# Re-compile the entire project
make re
```

### Usage

To link and use `libftprintf.a` in your C projects:

1. Include the header in your C source file:
   ```c
   #include "ft_printf.h"

   int main(void)
   {
       ft_printf("Hello, %s! Total count: %d\n", "42", 42);
       return (0);
   }
   ```

2. Compile your program by linking against `libftprintf.a`:
   ```bash
   cc -Wall -Wextra -Werror main.c -L. -lftprintf -o my_program
   ./my_program
   ```

---

# Algorithm & Data Structures

### Algorithm
The implementation uses a **single-pass sequential parsing algorithm**:
1. **Format Traversal**: A `while` loop traverses the `format` string character by character.
2. **Literal Printing**: Characters that are not `%` are written directly to stdout via `write(1, &format[i], 1)` and increment the output counter.
3. **Specifier Dispatching**: When encountering a `%` character:
   - The index is advanced to inspect the conversion specifier (`format[++i]`).
   - The character is dispatched to a specialized category handler (`ft_printf_char`, `ft_printf_nbr`, or `ft_printf_hex`).
   - The argument is fetched from the variadic list (`va_list`) using the corresponding type in `va_arg`.
   - The helper returns the exact number of bytes printed, which is accumulated into `len`.
4. **Recursive Numerical & Hex Conversion**:
   - For numbers (`%d`, `%i`, `%u`, `%x`, `%X`, `%p`), recursive division is used instead of dynamic memory allocation or large buffers.
   - For base 10 (`%d`, `%i`), values are cast to `long` to prevent integer overflow when taking the absolute value of `INT_MIN` (`-2147483648`).
   - For `%x`, `%X`, and `%p`, a single recursive base-16 function taking `unsigned long` formats both 32-bit unsigned integers and 64-bit pointer addresses cleanly.
5. **Final Return**: The function calls `va_end(args)` and returns the total character count (or `-1` if `format` is `NULL`).

### Data Structures & Encapsulation
* **Variadic Argument Management**: Handled via standard `<stdarg.h>` structures (`va_list`, `va_start`, `va_arg`, `va_end`), enabling portable access to variable arguments across system calling conventions.
* **No Dynamic Memory Allocation**: The entire project operates with $O(1)$ heap overhead; all conversions are executed using stack-allocated primitives and direct writes, ensuring zero memory leaks.
* **Static Encapsulation**: All internal helper functions (`ft_putchar`, `ft_putstr`, `ft_putnbr`, `ft_putunsigned`, `ft_puthex`, `ft_putptr`) are declared `static` within their respective translation units. This hides implementation details, prevents global namespace pollution, and guarantees zero symbol collisions when linking with external projects or libraries.

---

# Resources

### Classic References
* **Linux Programmer's Manual (man pages)**:
  * `man 3 printf` — Standard formatted output conversion documentation.
  * `man 3 stdarg` — Variable argument lists (`va_start`, `va_arg`, `va_end`).
  * `man 2 write` — Direct system call output specifications.
* **42 Norminette Documentation**: Guidelines on coding standards, function line constraints, and modular structure.

### AI Usage Description
In accordance with the 42 AI directives (Chapter 3 & Chapter 5):
* **Tasks Assisted**:
  * Architectural guidance and module separation (organizing specifiers by category into `ft_printf_char.c`, `ft_printf_nbr.c`, and `ft_printf_hex.c`).
  * Concept clarification on C variadic arguments, default argument promotions (`char` promoting to `int`), and pointer address sizing on 64-bit architectures (`unsigned long`).
  * Edge case verification (`INT_MIN`, `UINT_MAX`, `NULL` strings returning `(null)`, and `NULL` pointer addresses displaying `(nil)`).
  * Structure and formatting of the project documentation to fulfill Chapter 5 specifications.
* **Student Verification**: All code logic, prototypes, recursive bases, and Makefile rules were reviewed, tested, and validated by the student to guarantee complete mastery during peer evaluation.
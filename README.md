# C-Compiler

> A C language compiler for practice.
> WIP!

## Usage

After built, run the program with one argument like the example below:

```shell
C-Compiler "10 + (4 - 3) * 7 + -1;"
```

The available operators include addition, subtraction, multiplication, division,
unary plus, unary minus, relational operators, and equality operators.

The last statement of the given semicolon-split sequence is the return of the main function.

You can use variables whose name consists of a single character like `a = 10; a + 1;`.

The program will output LLVM IR into stdout.

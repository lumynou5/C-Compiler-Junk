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

You can use variables like `abc = 10; abc + 1;`.
Trying to access a variable that hasn't assigned before is undefined behavior.

The program will output LLVM IR into stdout.

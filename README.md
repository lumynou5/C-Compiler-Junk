# C-Compiler

> A C language compiler for practice.
> WIP!

## Usage

After built, run the program with one argument like the example below:

```shell
./C_Compiler "10 + (4 - 3) * 7 + -1;"
```

The available operators include addition, subtraction, multiplication, division, remainder,
unary plus, unary minus, relational operators, equality operators, and assignment operators.

The last statement of the given semicolon-split sequence is the return of the main function.

You can use variables like `foo = 10; foo + 1;`.
Trying to access a variable that hasn't assigned before causes compilation error.

The program will output LLVM IR into stdout.
You may redirect the output into a file and run it with `lli`.

### Command Template

Optimize the IR and output:

```shell
./C_Compiler $SOURCE > test.ll && opt --O3 test.ll -o test.ll && llvm-dis test.ll -o test.ll && cat test.ll && rm test.ll
```

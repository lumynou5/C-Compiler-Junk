# C-Compiler

> A C language compiler for practice.
> WIP!

## Usage

After built, run the program with one argument like the example below:

```shell
./C_Compiler "return 10 + 3 * 4 - (-1 == 2);"
```

The available operators include addition, subtraction, multiplication, division, remainder,
unary plus, unary minus, relational operators, equality operators, and assignment operators.

A `return` statement is necessary.
Unreachable code after the return statement won't be parsed.

You can use variables like `foo = 10; return foo + 1;`.
Trying to access a variable that hasn't assigned before causes compilation error.

The program will output LLVM IR into stdout.
You may redirect the output into a file and run it with `lli`.

### Command Template

#### Optimize the IR and output

```shell
./C_Compiler $SOURCE | opt --O3 | llvm-dis | cat
```

#### Run the IR

```shell
./C_Compiler $SOURCE | lli
```

For some shells, you may have to use `$pipestatus[2]` or something else to get the exit status.

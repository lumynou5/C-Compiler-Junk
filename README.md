# C-Compiler

> WIP! It cannot compile C source code now.

This is just a practice project to learn how to make a compiler.

## Building

Dependencies:
- [CMake](https://cmake.org)
- [fmt](https://github.com/fmtlib/fmt)
- [LLVM](https://llvm.org)

Use the commands below or an IDE such as CLion to build.

```shell
# In the repository root directory.
mkdir build
cd build
cmake ..
make
```

## Usage

After built, the program can be run with one argument like the example below:

```shell
./C_Compiler "main() { x = 10; x += 3 * 2 - 8; x = x == 5; return x; }"
```

The available operators include addition, subtraction, multiplication, division, remainder,
unary plus, unary minus, relational operators, equality operators, assignment operators, and brackets.

The result of a comparison will be converted into `i32`, where `false` is `0` and `true` is `1`.

You can use variables like `foo = 10; return foo + 1;` without types.
Trying to access a variable that hasn't defined before causes a compilation error.

The program will output LLVM IR into stdout.
You may redirect the output into a file and run it with `lli`.

### Command Templates

Replace `$SOURCE` with your code like `(cat source.c)` or `$(cat source.c)`, depends on the shell.

#### Optimize the IR and output

```shell
./C_Compiler $SOURCE | opt --O3 | llvm-dis
```

#### Run the IR

```shell
./C_Compiler $SOURCE | lli
```

For some shells, you may have to use `$pipestatus[2]` or something else to get the exit status.

## License

The source code is distributed under the MIT license.
See [LICENSE.md](LICENSE.md) for further information.

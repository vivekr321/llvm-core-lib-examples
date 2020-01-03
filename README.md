# llvm-core-lib-examples
Examples described in Getting started with LLVM core libraries book.
Build using Visual studio 2017 (v15). Assumes LLVM to be installed at 'C:\LLVM\'

 - ### llvm-func-pass
    Consists of source code for a tool that would list all function names present in bit code file being passed as an argument.
    ```
    >> llvm-func-pass.exe hello.bc
    ?fib@@YAHH@Z has 5 basic block(s) and accepts 1 arguments
    ```

- ### clang-read-diagnostics
    Consists of source code for a tool that would  list out all clang diagnostic messages for a source file being passed as an argument
    ```
    >> clang-read-diagnostics.exe hello_with_errors.c
    Severity: 3 File: ..\hello_with_error.c
    Line: 7 Col: 12 Category: "Parse Issue" Message: expected ';' at end of declaration
    ```

- ### llvm-clang-lexer
    Consists of source code for a tool that would use clang lexer to emit tokens from given c/cpp source file passed as an argument
    ```
    Source file: min.c
    int min(int a, int b)
    {
        if (a < b)
            return a;
        return b;
    }
    ```

    ```
    >> llvm-clang-lexer.exe min.c
    Number of token: 20
    KEYWORD(int) IDENTIFIER(min) PUNCTUATION(() KEYWORD(int) IDENTIFIER(a) PUNCTUATION(,) KEYWORD(int) IDENTIFIER(b) PUNCTUATION())
    PUNCTUATION({) KEYWORD(if) PUNCTUATION(() IDENTIFIER(a) PUNCTUATION(<) IDENTIFIER(b)PUNCTUATION()) KEYWORD(return) IDENTIFIER(a)
    PUNCTUATION(;) KEYWORD(return)
    ``

- ### llvm-clang-traverse-ast
    Tool to parse provided source code and print function names using its declaraion. Function name is obtained by tranversing the AST (abstract syntax tree)
    provided by clang

    ```
    >> llvm-clang-traverse-ast.exe min.c
    min.c:1:5 declares min
    ```

- ### llvm-clang-ast-stats
    Tool to print out abstract syntax tree statisitics. This tool attempst to perform actions performed by clang driver in a simplified manner (not handling all use cases).

    ```
    //Input Source: fib.cpp
    #define MAX_INPUT 1000

    int fib(int n)
    {
        if (n > MAX_INPUT)
        {
            return 0;
        }

        if (n == 0 || n == 1)
        {
            return 1;
        }
        else
        {
            return fib(n - 1) + fib(n - 2);
        }
    }
    ```


    ```
    >>llvm-clang-ast-stats.exe fib.cpp
    int fib(int n) {
        if (n > 1000) {
            return 0;
        }
        if (n == 0 || n == 1) {
            return 1;
        } else {
            return fib(n - 1) + fib(n - 2);
        }
    }

    *** AST Context Stats:
      69 types total.
        58 Builtin types, 24 each (1392 bytes)
        4 Complex types, 40 each (160 bytes)
        1 FunctionProto types, 40 each (40 bytes)
        5 Pointer types, 40 each (200 bytes)
        1 Record types, 32 each (32 bytes)
    Total bytes = 1824
    0/0 implicit default constructors created
    0/0 implicit copy constructors created
    0/0 implicit copy assignment operators created
    0/0 implicit destructors created

    Number of memory regions: 2
    Bytes used: 4636
    Bytes allocated: 8192
    Bytes wasted: 3556 (includes alignment, etc)
    ```
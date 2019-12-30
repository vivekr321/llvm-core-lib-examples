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

# llvm-essentials-examples
Examples described in LLVM essentials book.
Build using Visual studio 17. Assumes LLVM to be installed at 'C:\LLVM\'

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
    Severity: 3 File: C:\Users\vr\Desktop\Repo\Compilers\llvm-example\intro-examples\hello_with_error.c
    Line: 7 Col: 12 Category: "Parse Issue" Message: expected ';' at end of declaration
    ```

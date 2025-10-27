# C Compiler for RISC-V (32-bit)

This project implements a custom **C compiler** that translates pre-processed C90 code into **RISC-V (RV32IM)** assembly.  
It was developed to explore compiler architecture, code generation, and low-level programming concepts within a reproducible Docker-based Ubuntu environment.

---

## Overview

The compiler parses a `.c` source file, generates an **Abstract Syntax Tree (AST)**, and outputs **RISC-V assembly**.  
It is designed for **Ubuntu 22.04** and tested using **VS Code Dev Containers** and the RISC-V GCC toolchain.  
Most of the **basic** and **intermediate** compiler features have been implemented successfully.

---

## Implemented Features

### Basic Features
- Single function files with no arguments  
- Local variables  
- `int` variable type  
- Arithmetic and logical expressions  
- `if-then-else` statements  
- `while` loops  

### Intermediate Features
- Multiple functions with inter-function calls  
- Functions with up to eight parameters  
- `for` loops  
- Global and local arrays  
- Array initialization and indexing (constants, variables, expressions)  
- Recursive function calls  
- `enum` keyword  
- `switch` statements  
- `break` and `continue` statements  
- Ternary operator (`x ? y : z`)

### Advanced Features (Planned)
- Additional data types: `float`, `double`, `char`, `unsigned`, `struct`, and pointers  
- Externally defined functions (cross-file linking)  
- Functions with more than eight parameters  
- Mutually recursive functions  
- Locally scoped declarations inside control structures  
- `typedef` keyword  
- `sizeof(...)` operator  
- Address-of (`&`) and dereference (`*`) operators  
- Pointer arithmetic  
- Character literals and strings (including escape sequences such as `\n`)  
- Struct declaration and use  

---

## Environment Setup

The compiler is designed to build and run inside a **Docker container** running Ubuntu 22.04.  
This ensures a consistent and isolated environment for testing and evaluation.


# C Compiler for RISC-V (32-bit)

This project is a **custom C compiler** that translates pre-processed C90 code into **RISC-V (RV32IM)** assembly.  
It was built from scratch as part of a broader effort to understand compiler design — from parsing to code generation — while working within a Docker-based Ubuntu environment.

---

## 🌱 Overview

The compiler takes a `.c` source file, generates an **Abstract Syntax Tree (AST)**, and emits **RISC-V assembly code**.  
It is designed to work on **Ubuntu 22.04** and tested within a **VS Code Dev Container** using the provided toolchain.

Majority of **basic** and **intermediate** features have been implemented successfully.

---

## ⚙️ Supported Features

### ✅ Basic Features
- Single function files with no arguments  
- Local variables  
- `int` variable type  
- Arithmetic and logical expressions  
- `if-then-else` statements  
- `while` loops  

### 🚀 Intermediate Features
- Multiple functions with inter-function calls  
- Functions with up to 8 parameters  
- `for` loops  
- Global and local arrays  
- Array initialization and indexing (constants, variables, expressions)  
- Recursive function calls  
- `enum` keyword  
- `switch` statements  
- `break` and `continue` keywords  
- Ternary operator (`x ? y : z`)

### 💡 Planned / Advanced Features
- Additional types: `float`, `double`, `char`, `unsigned`, `struct`, pointers  
- Externally-defined functions (cross-file linking)  
- More than 8 function parameters  
- Mutually recursive function calls  
- Locally scoped declarations inside control structures  
- `typedef` keyword  
- `sizeof(...)` operator  
- Address-of (`&`) and dereference (`*`) operators  
- Pointer arithmetic  
- Character literals and strings (`\n`, `\t`, etc.)  
- Struct declarations and usage

---

## 🧰 Environment Setup

The project is designed to be built and tested inside a **Docker container** with Ubuntu 22.04.  
This ensures a consistent toolchain for RISC-V compilation and simulation.

### 🐳 Using VS Code + Docker

1. **Install Docker Desktop**  
   (On Apple M1/M2, choose the *Apple Silicon* version.)

2. **Install the Dev Containers extension** in VS Code.

3. **Open the repository** in VS Code.

4. Open the Command Palette (`Ctrl+Shift+P` on Windows / `Cmd+Shift+P` on Mac)  
   and run:

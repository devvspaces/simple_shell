# Simple Shell

A simple UNIX command interpreter using C programming.


## Introduction

This project creates a simple shell, which is a computer program that exposes an operating system's services to a human user or other programs. The simple shell is written in C language and provides a command-line interface for interacting with the operating system.


## Installation

To use the Simple Shell script, follow these steps:

1. Clone the repository to your local machine.
2. Compile the shell script using a C compiler, such as GCC. Using the options `-Wall -Werror -Wextra -pedantic -std=gnu89`
3. Run the compiled binary to start the shell.


# Tasks

### 0. Betty would be proud

    Write a beautiful code that passes the Betty checks


### 1. Simple shell 0.1

    Write a UNIX command line interprete


### 2. Simple shell 0.2

    Handle command lines with arguments


### 3. Simple shell 0.3

    Handle the`PATH`


### 4. Simple shell 0.4

Simple shell 0.3 +

    Implement the`exit` built-in, that exits the shell


### 5. Simple shell 1.0

Simple shell 0.4 +

* Implement the `env`  **built-in** , that prints the current environment


### 6. Simple shell 0.1.1

Simple shell 0.1 +

* Write your own `getline` function
* Use a buffer to read many chars at once and call the least possible the `read` system call
* You will need to use `static` variables


### 7. Simple shell 0.2.1

    Simple shell 0.2 +

* You are not allowed to use `strtok`



### 8. Simple shell 0.4.1

Simple shell 0.4 +

* handle arguments for the built-in `exit`
* Usage: `exit status`, where `status` is an integer used to exit the shell


### 9. setenv, unsetenv

Simple shell 1.0 +

Implement the `setenv` and `unsetenv` builtin commands


### 10. cd

Simple shell 1.0 +

Implement the builtin command `cd`


### 11.;

Simple shell 1.0 +

* Handle the commands separator `;`


### 12.&& and ||

Simple shell 1.0 +

* Handle the `&&` and `||` shell logical operators


### 13. alias

Simple shell 1.0 +

* Implement the `alias` builtin command
* Usage: `alias [name[='value'] ...]`


### 14. Variables

Simple shell 1.0 +

* Handle variables replacement
* Handle the `$?` variable
* Handle the `$$` variable


### 15. Comments

Simple shell 1.0 +

* Handle comments (`#`)


### 16. File as input

Simple shell 1.0 +

* Usage: `simple_shell [filename]`
* Your shell can take a file as a command line argument
* The file contains all the commands that your shell should run before exiting
* The file should contain one command per line
* In this mode, the shell should not print a prompt and should not read from `stdin`

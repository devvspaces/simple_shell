#!/bin/sh

# betty check
betty *.c *.h;

# complile and run
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c *.h -o shell;

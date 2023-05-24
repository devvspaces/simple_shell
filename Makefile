# Makefile

CC=gcc -Wall -Werror -Wextra -pedantic -std=gnu89
TARGET=shell
CFILES=*.c
HFILES=*.h

build:
	betty $(CFILES) $(HFILES)
	$(CC) $(CFILES) -o $(TARGET)

clean:
	rm -f $(TARGET)

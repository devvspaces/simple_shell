# Makefile

CC=gcc -Wall -Werror -Wextra -pedantic -std=gnu89
TARGET=shell
CFILES=*.c
HFILES=*.h

build:
	$(CC) $(CFILES) -o $(TARGET)

test:
	betty $(CFILES) $(HFILES)
	$(CC) -g $(CFILES) -o $(TARGET)

clean:
	rm -f $(TARGET)

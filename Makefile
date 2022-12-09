# Makefile for the project

CC = g++
CFLAGS = -g -Wall
SOURCES = src/main.cpp
OBJECTS = $(SOURCES:.c=.o)
TARGET = proj3

.PHONY: clean

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)
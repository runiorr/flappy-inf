SRCDIR = src
SRCFILES = $(wildcard $(SRCDIR)/*.c)

MAIN = main.c
SOURCES = $(filter-out $(SRCDIR)/$(MAIN), $(SRCFILES)) # Remove the main file from the list of source files

CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic-errors

INCLUDE_PATHS = -I"/usr/local/include" -I"./include"
LINKER_PATHS = -L"/usr/local/lib" -L"./lib"
LINKER_FLAGS = -lraylib -lm

BUILDDIR = build
TARGET = game

###############################################################################
# Check running platform

ifeq ($(OS),Windows_NT)
    # Windows settings
    RM = del /Q
    TARGET_EXTENSION = .exe
else
    # Linux settings
    RM = rm -f
    TARGET_EXTENSION =
endif

###############################################################################

all:
	make clean & make compile && make run

compile: $(SRCDIR)/*.c
	$(CC) $(CFLAGS) $(INCLUDE_PATHS) $(LINKER_PATHS) $(LINKER_FLAGS) $(SRCFILES) -o $(BUILDDIR)/$(TARGET)$(TARGET_EXTENSION)

run: $(BUILDDIR)/$(TARGET)$(TARGET_EXTENSION)
	./$(BUILDDIR)/$(TARGET)$(TARGET_EXTENSION)

clean:
	$(RM) $(BUILDDIR)/$(TARGET)$(TARGET_EXTENSION)

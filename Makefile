SRCDIR = src
MAIN = main.c
BUILDDIR = build
TARGET = game

###############################################################################
# Check running platform

ifeq ($(OS),Windows_NT)
	# Windows settings
	SRCFILES = $(SRCDIR)/*.c

	CC = gcc
	CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic-errors -Wno-missing-braces

	INCLUDE_PATHS = -I"./include"

	LINKER_PATHS = -L"./lib"
	LINKER_FLAGS = -lraylib -lopengl32 -lgdi32 -lwinmm

	RM = del /Q
	TARGET_EXTENSION = .exe
else
	# Linux settings
	SRCFILES = $(wildcard $(SRCDIR)/*.c)

	CC = gcc
	CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic-errors

	INCLUDE_PATHS = -I"/usr/local/include" -I"./include"

	LINKER_PATHS = -L"/usr/local/lib"
	LINKER_FLAGS = -lraylib -lm

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

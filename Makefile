# OBJS specifies which files to compile as part of the project
OBJS = src/*.c

# CXX specifies the compiler that we want to use
CXX = gcc

# COMPILER_FLAGS specifies the additional compilation options that we are using
# -w: Inhibit all warning messages.
# -Wall: Enables all compiler's warning messages
# -Wextra: This enables some extra warning flags that are not enabled by -Wall.
# -Werror: Make all warnings into errors.
COMPILER_FLAGS = -Wall -Wextra -Werror -std=c99

# INCLUDE_PATHS
INCLUDE_PATHS = -I"/usr/local/include"

# LINKER_PATHS
LINKER_PATHS = -L"/usr/local/lib"

# LINKER_FLAGS
LINKER_FLAGS = -lraylib -lm

# OBJ_NAME specifies the name of our executable
# OUT_FOLDER specifies the folder of our executable
OBJ_NAME = game
OUT_FOLDER = build

###############################################################################

# This is the target that compiles our executable
compile: $(OBJS)
	$(CXX) $(COMPILER_FLAGS) $(INCLUDE_PATHS) $(LINKER_PATHS) $(LINKER_FLAGS) $(OBJS) -o $(OUT_FOLDER)/$(OBJ_NAME)

# This command run the executable
run: $(OUT_FOLDER)/$(OBJ_NAME)
	./$(OUT_FOLDER)/$(OBJ_NAME)

# This command removes the previously created executable
clean: $(OUT_FOLDER)/$(OBJ_NAME)
	rm ./$(OUT_FOLDER)/$(OBJ_NAME)
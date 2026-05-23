# 1. Define Directory Variables
SRC_DIR   := src
BUILD_DIR := build
OBJ_DIR   := $(BUILD_DIR)/obj
BIN_DIR   := bin

# 2. Project & Compiler Settings
EXE      := $(BIN_DIR)/bfck
SRC      := $(wildcard $(SRC_DIR)/*.c)
HEADER   := $(wildcard $(SRC_DIR)/*.h)
# Convert src/file.c to obj/file.o
OBJ      := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC       := gcc
CPPFLAGS := -Iinclude  # Include headers if they are in an 'include' folder
CFLAGS   := -Wall
LDFLAGS  := -Llib
LDLIBS   := -lm

# 3. Primary Targets
.PHONY: all static-anlysis format-check format clean

all: $(EXE)

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

# 4. Pattern Rule for Objects
# This rule tells Make how to create an .o file in obj/ from a .c file in src/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# 5. Directory Creation (Order-only prerequisites)
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

static-analysis:
	cppcheck $(SRC_DIR)

format-check:
	@FAILED=0; \
	for file in $(SRC) $(HEADER); do \
		if ! [ clang-format --dry-run --Werror "$$file" 2>/dev/null ]; then \
			echo "Needs formatting: $$file"; \
			FAILED=1; \
		fi; \
	done; \
	if [ $$FAILED -eq 1 ]; then \
		echo ""; \
		echo "Some files need formatting. Run: make format"; \
		exit 1; \
	fi; \
	echo "All files are properly formatted!"

format:
	clang-format -i $(SRC) $(HEADER)

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

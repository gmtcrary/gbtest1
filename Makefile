CC := /mnt/c/gbdk/bin/lcc.exe
INCLUDES := $(shell find $(SRC_DIR) -type f -name '*.h' -exec dirname {} \; | sort -u | sed 's/^/-I/')
CFLAGS := -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG $(INCLUDES)
BUILD_DIR := build
OUT := $(BUILD_DIR)/main.gb
SRC_DIR := src
# Find all .c files recursively under src/
SRC := $(shell find $(SRC_DIR) -name '*.c')
# Replace src/ with build/ and .c with .o
OBJ := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))

# Default target
all: $(OUT)

# Link to final ROM
$(OUT): $(OBJ) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Pattern rule for compiling .c to .o (preserving subdirs)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

# Ensure build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean: ## Clean build artifacts
	rm -rf $(BUILD_DIR)

run: $(OUT) ## Run the build/main.gb rom
	./tools/bgb.exe build/main.gb

help:
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.* ?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

.PHONY: all $(MAKECMDGOALS)

.DEFAULT_GOAL := help

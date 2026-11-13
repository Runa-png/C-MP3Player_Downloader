BUILD_DIR = build
TARGET = $(BUILD_DIR)/app
JOBS = $(shell nproc)

.PHONY: all build clean run

all: build

build:
	rm -rf ./$(BUILD_DIR)
	cmake -S . -B $(BUILD_DIR)
	cmake --build $(BUILD_DIR) -j$(JOBS)

clean:
	rm -rf ./$(BUILD_DIR)

run: build
	./$(TARGET)
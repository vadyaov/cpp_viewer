CURR_DIR := .
BUILD_DIR := ./build

all: install run

install:
	cmake $(CURR_DIR) -S $(CURR_DIR) -B $(BUILD_DIR)
	@cd $(BUILD_DIR) ; make ; cd ./..

run:
	./build/viewer.app

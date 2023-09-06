BUILD_DIR = build
COVER_DIR = cover

all: test

test:
	mkdir -p $(BUILD_DIR)
	cmake ./ -B $(BUILD_DIR)
	$(MAKE) -C $(BUILD_DIR) tests
	./build/tests

gcov:
	mkdir -p $(COVER_DIR)
	cmake ./ -B $(COVER_DIR) -DCMAKE_BUILD_TYPE=Debug
	$(MAKE) -C ./$(COVER_DIR) viewer_coverage
	open ./cover/viewer_coverage/index.html

clang:
	clang-format -n *.cc *.h

valgrind:
	valgrind --leak-check=full ./build/tests

clean:
	@rm -rf $(BUILD_DIR)
	@rm -rf $(COVER_DIR)

.PHONY: all test clang valgrind clean

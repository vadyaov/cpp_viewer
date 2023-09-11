FLAGS = -ggdb -std=c++17 -Wall -Werror -Wextra -lstdc++
TEST_FLAGS= -lgtest -lgmock -pthread
SOURCES=model/Aphine.cc model/Reader.cc model/Model.cc
OBJECTS=model.o
CXX=g++

EXECUTABLE = test

OPEN_REPORT :=
LEAKS :=

TEST_DIR = tests/
TESTS_SRC = $(wildcard $(TEST_DIR)*.cc)
TESTS_OBJ = $(patsubst %.cc,%.o,$(notdir $(TESTS_SRC)))
TEST_FILES = tests/tests.cc

ifeq ($(shell uname -s), Linux)
	TEST_FLAGS= -lgtest -lpthread -pthread
	OPEN_REPORT += xdg-open
	LEAKS += valgrind --leak-check=full -s -q --track-origins=yes
endif

ifeq ($(shell uname -s), Darwin)
	OPEN_REPORT += open
	LEAKS += leaks -atExit --
endif

all: install run

tests: clean create_objects
	$(CXX) $(FLAGS) $(SOURCES) $(TEST_FILES) $(TEST_FLAGS) -o test
	./test

gcov_report: clean add_coverage tests
	./test
	lcov --exclude='/usr/include/*' -t "test" -o test.info -c -d .
	genhtml -o report test.info
	$(OPEN_REPORT) report/index.html
	rm -f *.gcda *.gcno
ifeq (${OS}, Linux)
	cd report && firefox coverage_report.html
else
	cd report && open coverage_report.html
endif

add_coverage:
	$(eval FLAGS += -fprofile-arcs -ftest-coverage --coverage)

CURR_DIR := .
BUILD_DIR := $(CURR_DIR)/build
LOGIC_DIR := $(CURR_DIR)/core

RM := rm -f
MK := mkdir -p

EXEC := vimer.app
ARCHIVE := $(CURR_DIR)/vimer

create_objects:
	cp models/Alien_Animal.txt models/Alien_Animal.obj
	cp models/cube.txt models/cube.obj
	cp models/dragon.txt models/dragon.obj
	cp models/magnolia.txt models/magnolia.obj

install: create_objects
	@$(MK) $(BUILD_DIR)
	cmake $(CURR_DIR) -S $(CURR_DIR) -B $(BUILD_DIR)
	@cd $(BUILD_DIR) ; make ; cd ./..

uninstall:
	@$(RM) -r $(BUILD_DIR)

run:
	$(BUILD_DIR)/$(EXEC)

dist:	
	tar -cvzf viewer.tar.gz model/* view/* controller/* shaders/* imgui/*

dvi:
	doxygen Doxyfile
	open ./html/index.html

clean: uninstall
	@$(RM) -r doc/
	@$(RM) imgui.ini
	@$(RM) ScreenShot.jpeg
	@$(RM) ScreenShot.bmp
	@$(RM) -r imgui/CMakeFiles/
	@$(RM) imgui/cmake_install.cmake
	@$(RM) imgui/Makefile
	@$(RM) imgui/libimgui.a
	@$(RM) -r html/* latex/*
	@$(RM) -r report/
	@$(RM) test.info test
	@$(RM) models/cube.obj models/dragon.obj models/magnolia.obj models/Alien_Animal.obj

.PHONY: all clean tests gcov_report run

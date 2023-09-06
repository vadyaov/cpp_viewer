cmake_minimum_required(VERSION 3.14)
project(viewer_test VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_MODULE_PATH ./CMakeModules)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

add_compile_options(-Wall -Werror -Wextra -Wpedantic)
# add_compile_options(-fsanitize=address)
# add_link_options(-fsanitize=address)

find_package(GTest REQUIRED)
include(GoogleTest)
enable_testing()

file(GLOB SOURCES ./tests/*.cc model.cc file_reader.cc)
add_executable(tests ${SOURCES})

target_link_libraries(tests GTest::gtest_main)

gtest_discover_tests(tests)

# if(CMAKE_COMPILER_IS_GNUCXX)
  include(CodeCoverage)
  append_coverage_compiler_flags()
  setup_target_for_coverage_lcov(
         NAME viewer_coverage
         EXECUTABLE tests -j ${PROCESSOR_COUNT}
         BASE_DIRECTORY "../"
         EXCLUDE "/usr/include/*" "./model/tests/*" "./gtest/*" "./gtest/internal/*")
# endif()

cmake_minimum_required(VERSION 3.14)
project(
  p
  VERSION 0.0.1
  LANGUAGES C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_EXTENSIONS OFF)

# good default for executables:
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

add_executable(usb main.c usb_drive.c)
set(flags
    -pedantic
    -Wall
    -Wextra
    # -Werror
    -Wshadow
    -Wdouble-promotion
    -Wformat=2
    -Wformat-truncation
    -Wundef
    -fno-common
    # -fstack-usage
    -Wstack-usage=512
    -Wconversion
    -Wunused-parameter)

target_compile_options(
  usb PRIVATE # clang/gcc warnings:
              "$<$<OR:$<C_COMPILER_ID:Clang>,$<C_COMPILER_ID:GNU>>:${flags}>")

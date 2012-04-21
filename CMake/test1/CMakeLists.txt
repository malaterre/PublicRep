project(test1 C)

add_library(lib1 SHARED foo.c)
add_library(lib2 MODULE foo.c)

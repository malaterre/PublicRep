cmake_minimum_required(VERSION 3.24)
project(P)
add_executable(p p.cxx)

target_compile_features(p PRIVATE cxx_std_17)

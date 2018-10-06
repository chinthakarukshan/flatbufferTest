cmake_minimum_required(VERSION 3.12)
project(FlatBuffers)

set(CMAKE_CXX_STANDARD 14)

include_directories("/home/chinthaka/research/flatbuffers/include")

add_executable(FlatBuffers main.cpp monster_generated.h sample-binary.cpp edgestore_generated.h)
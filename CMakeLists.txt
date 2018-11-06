cmake_minimum_required(VERSION 3.12)
project(FlatBuffers)

set(CMAKE_CXX_STANDARD 14)

include_directories("/home/chinthaka/research/flatbuffers/include")

set(SOURCE_FILES )

add_executable(FlatBuffers main.cpp monster_generated.h sample-binary.cpp edgestore_generated.h LocalGraphDatabase.cpp util.cpp util.h LocalGraphDatabase.h AbstractLocalGraph.cpp AbstractLocalGraph.h MetisPartition.cpp MetisPartition.h)
cmake_minimum_required(VERSION 3.12)
project(FlatBuffers)

set(CMAKE_CXX_STANDARD 14)

include_directories("/home/chinthaka/software/flatbuffers/include")
#include_directories("/home/chinthaka/research/libs/metis-5.1.0/include")

#[[link_directories(/usr/local/lib)
link_libraries('libmetis')]]


set(SOURCE_FILES )

add_executable(FlatBufferTest main.cpp monster_generated.h sample-binary.cpp edgestore_generated.h LocalGraphDatabase.cpp util.cpp util.h LocalGraphDatabase.h AbstractLocalGraph.cpp AbstractLocalGraph.h MetisPartition.cpp MetisPartition.h)

target_link_libraries(FlatBufferTest /usr/local/lib/libmetis.so)
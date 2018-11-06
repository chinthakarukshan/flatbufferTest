//
// Created by chinthaka on 10/31/18.
//

#ifndef FLATBUFFERS_METISPARTITION_H
#define FLATBUFFERS_METISPARTITION_H

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <unordered_set>

using std::string;


class MetisPartition {
public:
    void loadDataSet(string filePath);

private:
    bool zeroVertexFlag;
    int nThreads;
    std::vector<std::map<int,std::unordered_set<int>>> graphStorage;
    int edgeCount;
    int largestVertex;
    string outputFilePath;
    int vertexCount;

    void constructMetisFormat(int adjustEdgeCount);
};


#endif //FLATBUFFERS_METISPARTITION_H

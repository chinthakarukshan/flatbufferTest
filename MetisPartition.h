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
#include <set>
#include "metis.h"
#include <cstddef>

using std::string;


class MetisPartition {
public:
    void loadDataSet(string filePath);
    void loadDataSetNew(string filePath);
    void partitionGraph();

private:
    bool zeroVertexFlag;
    int nThreads;
    std::vector<std::map<int,std::unordered_set<int>>> graphStorage;
    idx_t edgeCount;
    idx_t largestVertex;
    string outputFilePath;
    idx_t vertexCount;
    idx_t nWeights = 1;
    idx_t nParts = 2;
    idx_t objVal;


    std::map<int,std::set<int>> graphStorageMap;
    std::vector<int> xadj;
    std::vector<int> adjncy;

    void constructMetisFormat(int adjustEdgeCount);
    void constructMetisFormatNew();
};


#endif //FLATBUFFERS_METISPARTITION_H

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
    void loadDataSetNew(string filePath);
    void partitionGraph();

private:
    idx_t edgeCount;
    idx_t largestVertex;
    idx_t vertexCount;
    idx_t nWeights = 1;
    idx_t nParts = 3;
    idx_t objVal;


    std::map<int,std::set<int>> graphStorageMap;
    std::map<int,std::set<int>> graphEdgeMap;
    std::map<int,std::set<int>> partVertexMap;
    std::map<int,std::map<int,std::set<int>>> partitionedLocalGraphStorageMap;
    std::map<int,std::map<int,std::set<int>>> masterGraphStorageMap;
    std::vector<int> xadj;
    std::vector<int> adjncy;

    void constructMetisFormatNew();
    void createPartitionFiles(idx_t part[]);
};


#endif //FLATBUFFERS_METISPARTITION_H

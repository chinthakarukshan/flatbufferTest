#include <iostream>
#include "LocalGraphDatabase.h"
#include "MetisPartition.h"

int main() {
    /*LocalGraphDatabase* database = new LocalGraphDatabase(1);
    database->addVertex();*/


    MetisPartition* partition = new MetisPartition();
    partition->loadDataSetNew("/home/chinthaka/Downloads/simple_graph.dl");
    partition->partitionGraph();

    /*std::map<int,std::set<int>> graphStorageMap;
    std::set<int> test;
    std::set<int> testTwo;

    test.insert(2);
    test.insert(4);
    test.insert(6);

    testTwo.insert(3);
    testTwo.insert(6);
    testTwo.insert(9);

    graphStorageMap.insert(std::make_pair(5,test));
    graphStorageMap.insert(std::make_pair(8,testTwo));

    testTwo.insert(6);*/


    return 0;
}

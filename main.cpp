#include <iostream>
#include "LocalGraphDatabase.h"
#include "MetisPartition.h"

int main() {
    /*LocalGraphDatabase* database = new LocalGraphDatabase(1);
    database->addVertex();*/


    MetisPartition* partition = new MetisPartition();
    partition->loadDataSet("/home/chinthaka/Downloads/simple_graph.dl");



    return 0;
}

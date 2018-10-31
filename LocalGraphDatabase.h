//
// Created by chinthaka on 10/18/18.
//

#ifndef FLATBUFFERS_LOCALGRAPHDATABASE_H
#define FLATBUFFERS_LOCALGRAPHDATABASE_H

#include "AbstractLocalGraph.h"


class LocalGraphDatabase:public AbstractLocalGraph {
private:
    void getMaps();

public:
    LocalGraphDatabase(int test);
    bool addVertex();

};


#endif //FLATBUFFERS_LOCALGRAPHDATABASE_H

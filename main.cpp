#include <iostream>
#include "LocalGraphDatabase.h"

int main() {
    LocalGraphDatabase* database = new LocalGraphDatabase(1);
    database->addVertex();
    return 0;
}

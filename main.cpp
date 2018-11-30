#include <iostream>
#include <string>
#include <map>
#include <set>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

using std::string;

int main() {

    string line;
    int count=0;
    std::ifstream dbFile;
    dbFile.open("/home/chinthaka/research/dataset/Hyves-dataset/data/edges.csv",std::ios::binary | std::ios::in);

    int firstVertex = -1;
    int secondVertex = -1;

    std::unordered_map<int,std::set<int>> graphStorageMap;
    //std::unordered_map<int,std::set<int>> graphEdgeMap;
    std::unordered_set<string> edgeSet;


    std::set<int> vertexSet;


    std::getline(dbFile, line);

    while(!line.empty()) {
        string vertexOne;
        string vertexTwo;
        std::getline(dbFile, line);
        count++;

        std::istringstream stream(line);
        std::getline(stream, vertexOne, ',');
        stream >> vertexTwo;

        firstVertex = atoi(vertexOne.c_str());
        secondVertex = atoi(vertexTwo.c_str());



        std::set<int> firstEdgeSet = graphStorageMap[firstVertex];

        firstEdgeSet.insert(secondVertex);

    }

    std::cout << "Load Completed "  << count<< std::endl;

    std::unordered_map<int,std::set<int>>::iterator it;
    int tempCount = 0;

    for (it=graphStorageMap.begin();it != graphStorageMap.end();it++) {
        std::set<int> tempSet = it->second;
        tempCount = tempCount+tempSet.size();
    }

    std::cout << "Total Count "  << tempCount<< std::endl;

    return 0;
}

void executeLoadingSerially() {
    string line;
    int count=0;
    std::ifstream dbFile;
    dbFile.open("/home/chinthaka/research/dataset/Hyves-dataset/data/edges.csv",std::ios::binary | std::ios::in);

    int firstVertex = -1;
    int secondVertex = -1;

    std::unordered_map<int,std::set<int>> graphStorageMap;
    //std::unordered_map<int,std::set<int>> graphEdgeMap;
    std::unordered_set<string> edgeSet;


    std::set<int> vertexSet;


    std::getline(dbFile, line);

    while(!line.empty()) {
        string vertexOne;
        string vertexTwo;
        std::getline(dbFile, line);
        count++;

        std::istringstream stream(line);
        std::getline(stream, vertexOne, ',');
        stream >> vertexTwo;

        firstVertex = atoi(vertexOne.c_str());
        secondVertex = atoi(vertexTwo.c_str());



        std::set<int> firstEdgeSet = graphStorageMap[firstVertex];

        firstEdgeSet.insert(secondVertex);

        graphStorageMap[firstVertex] = firstEdgeSet;

    }

   // std::cout << "Load Completed "  << count<< std::endl;






}

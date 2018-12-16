#include <iostream>
#include <string>
#include <map>
#include <set>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>


using std::string;

int main() {

    string line;
    int count=0;
    std::ifstream dbFile;
    dbFile.open("/home/chinthaka/research/dataset/simpledataset/simple_graph.dl",std::ios::binary | std::ios::in);

    int firstVertex = -1;
    int secondVertex = -1;
    char splitter;

    std::unordered_map<int,std::vector<int>> graphStorageMap;
    std::unordered_map<int,std::vector<int>> graphEdgeMap;

    std::getline(dbFile, line);

    if (!line.empty()) {
        if (line.find(" ") != std::string::npos) {
            splitter = ' ';
        } else if (line.find('\t') != std::string::npos) {
            splitter = '\t';
        } else if (line.find(",") != std::string::npos) {
            splitter = ',';
        }
    }

    while (!line.empty()) {
        string vertexOne;
        string vertexTwo;

        std::istringstream stream(line);
        std::getline(stream, vertexOne, splitter);
        stream >> vertexTwo;

        firstVertex = atoi(vertexOne.c_str());
        secondVertex = atoi(vertexTwo.c_str());

        std::vector<int> firstEdgeSet = graphStorageMap[firstVertex];
        std::vector<int> secondEdgeSet = graphStorageMap[secondVertex];

        std::vector<int> vertexEdgeSet = graphEdgeMap[firstVertex];

        if (firstEdgeSet.empty()) {
            firstEdgeSet.push_back(secondVertex);
            vertexEdgeSet.push_back(secondVertex);

        } else {
            if (std::find(firstEdgeSet.begin(), firstEdgeSet.end(),secondVertex) == firstEdgeSet.end()) {
                firstEdgeSet.push_back(secondVertex);
                vertexEdgeSet.push_back(secondVertex);
            }
        }

        if (secondEdgeSet.empty()){
            secondEdgeSet.push_back(firstVertex);

        } else {
            if (std::find(secondEdgeSet.begin(), secondEdgeSet.end(),firstVertex) == secondEdgeSet.end()) {
                secondEdgeSet.push_back(firstVertex);
            }
        }

        graphStorageMap[firstVertex] = firstEdgeSet;
        graphStorageMap[secondVertex] = secondEdgeSet;
        graphEdgeMap[firstVertex] = vertexEdgeSet;



        std::getline(dbFile, line);
        while(!line.empty() && line.find_first_not_of(splitter) == std::string::npos) {
            std::getline(dbFile, line);
        }
    }

    std::unordered_map<int,std::vector<int>>::iterator it;
    int tempCount = 0;

    for (it=graphEdgeMap.begin();it != graphEdgeMap.end();it++) {
        std::vector<int> tempSet = it->second;
        std::sort(tempSet.begin(),tempSet.end());
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

void vectorImplementation() {
    string line;
    int count=0;
    std::ifstream dbFile;
    dbFile.open("/home/chinthaka/research/dataset/Hyves-dataset/data/edges.csv",std::ios::binary | std::ios::in);

    int firstVertex = -1;
    int secondVertex = -1;

    std::unordered_map<int,std::vector<int>> graphStorageMap;
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



        std::vector<int> firstEdgeSet = graphStorageMap[firstVertex];

        firstEdgeSet.push_back(secondVertex);

        graphStorageMap[firstVertex]=firstEdgeSet;

    }

    std::cout << "Load Completed "  << count<< std::endl;

    std::unordered_map<int,std::vector<int>>::iterator it;
    int tempCount = 0;

    for (it=graphStorageMap.begin();it != graphStorageMap.end();it++) {
        std::vector<int> tempSet = it->second;
        tempCount = tempCount+tempSet.size();
    }

    std::cout << "Total Count "  << tempCount<< std::endl;

}

//
// Created by chinthaka on 10/31/18.
//

#include <vector>
#include "MetisPartition.h"


void MetisPartition::loadDataSet(string filePath) {
    std::ifstream dbFile;
    dbFile.open(filePath,std::ios::binary | std::ios::in);

    int firstVertex = -1;
    int secondVertex = -1;
    string line;
    char splitter;

    //while(std::getline(dbFile, line)) {
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


       // std::cout << line << std::endl;
    //}

    while (!line.empty()) {
        std::cout << line << std::endl;
        string token1;
        string token2;
        std::istringstream stream(line);
        std::getline(stream, token1, splitter);
        stream >> token2;
        /*do {
            stream >> token;
            std::cout << token << std::endl;
        } while(stream);

        std::cout << token1 << std::endl;
        std::cout << token2 << std::endl;*/

        firstVertex = atoi(token1.c_str());
        secondVertex = atoi(token2.c_str());

        if (firstVertex == 0 || secondVertex == 0) {
            zeroVertexFlag = true;
            break;
        }

        std::getline(dbFile, line);

        while(!line.empty() && line.find_first_not_of(splitter) != std::string::npos) {
            std::getline(dbFile, line);
        }
    }

    dbFile.close();


    dbFile.open(filePath,std::ios::binary | std::ios::in);
    std::getline(dbFile, line);
    while (!line.empty()) {
        string token1;
        string token2;
        std::istringstream stream(line);
        std::getline(stream, token1, splitter);
        stream >> token2;
        firstVertex = atoi(token1.c_str());
        secondVertex = atoi(token2.c_str());
        if (firstVertex == secondVertex) {
            std::getline(dbFile, line);
            while(!line.empty() && line.find_first_not_of(splitter) != std::string::npos) {
                std::getline(dbFile, line);
            }
            continue;
        }

        if (zeroVertexFlag) {
            firstVertex = firstVertex + 1;
            secondVertex = secondVertex + 1;
        }

        int firstVertexIdx = firstVertex % nThreads;
        std::map<int,std::unordered_set<int>> vertexMap = graphStorage[firstVertexIdx];
        std::unordered_set<int> vertexSet = vertexMap[firstVertex];


        if (vertexSet.find(secondVertex) == vertexSet.end()) {
            vertexSet.insert(secondVertex);
            edgeCount++;
        }


        int secondVertexIdx = secondVertex%nThreads;
        vertexMap = graphStorage[secondVertexIdx];
        vertexSet = vertexMap[secondVertex];


        if (vertexSet.find(firstVertex) == vertexSet.end()) {
            vertexSet.insert(firstVertex);
            edgeCount++;
        }

        if (firstVertex > largestVertex) {
            largestVertex = firstVertex;
        }
        if (secondVertex > largestVertex) {
            largestVertex = secondVertex;
        }

        std::getline(dbFile, line);
        while(!line.empty() && line.find_first_not_of(splitter) != std::string::npos) {
            std::getline(dbFile, line);
        }

    }


}


void MetisPartition::constructMetisFormat(int adjustEdgeCount) {
    string outputFile = outputFilePath+"/grf";

    std::ofstream file(outputFile);

    if(file.is_open()) {
        vertexCount = largestVertex;

        if (adjustEdgeCount == -1) {
            file<<largestVertex+" " + edgeCount + '\r\n';
        } else {
            file<<largestVertex+" " + adjustEdgeCount + '\r\n';
        }

        int index = 1;

        for (;index <= largestVertex; index++) {
            std::map<int,std::unordered_set<int>> vertexMap = graphStorage[index % nThreads];
            std::unordered_set<int> itemSet = vertexMap[index];

            if (itemSet.empty()) {
                if (index == 0) {
                    file<<"1 \r\n";
                } else {
                    file<< "\r\n";
                }

            } else {
                for (std::unordered_set<int>::iterator itr = itemSet.begin(); itr != itemSet.end(); ++itr) {
                    file<<(*itr);
                    if (++itr == itemSet.end()) {
                        file<< "\r\n";
                    } else {
                        file<<" ";
                    }
                }
            }

        }
    }
    file.close();
}
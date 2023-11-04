//
// Created by Victor Lelis
// Matheus Vieira
// Victor Ramires
// on 11/1/23.
//
#include "utils.h"

#include<string>
#include<fstream>
#include<sstream>

using namespace std;

string ReadProgramSource(const string filePath){
    fstream file(filePath);
    stringstream ss;
    string line;

    while (getline(file, line)){
        ss << line << "\n";
    }
    file.close();

    return ss.str();
}

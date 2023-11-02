//
// Created by lelis on 11/1/23.
//

#include "Utils.h"

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

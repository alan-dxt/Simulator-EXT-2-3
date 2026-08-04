#include <iostream>
#include <fstream>
#include "./Utilities.h"

using namespace std;

string Utilities::Trim(const string& str){
    size_t first = str.find_first_not_of(" \t\n\r");
    size_t last = str.find_last_not_of(" \n\n\t");
    if(first == string::npos) return "";
    return str.substr(first, (last - first + 1));
}

bool Utilities::diskExist(const string& path){
    ifstream file(path, ios::binary);
    return file.good();
}
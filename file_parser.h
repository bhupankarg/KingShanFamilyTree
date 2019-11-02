#pragma once
#include "family_operations.cpp"

class FileParser
{
public:
    int parseDataFromFile(Family*, ifstream*, bool);
private:
    int parseInputCommand(Family*, string);
    int parseInitCommand(Family*, string);
    vector<string> splitCommand(string, char);
};


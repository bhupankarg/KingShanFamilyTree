#include "main.h"

int main(int arg_count, char* argv[])
{
    int initiateStatus;
    Family kingFamily;
    for(int fileNumber = 1; fileNumber <= 2; fileNumber++)
    {
        if(fileNumber == 1)
            initiateStatus = initiateFile(&kingFamily, init_data_file, false);
        else
            initiateStatus = initiateFile(&kingFamily, argv[1], true);
        if(initiateStatus == FAILURE) return FAILURE;
    }
    return SUCCESS;
}

int initiateFile(Family* kingFamily, string fileName, bool inputFile)
{
    ifstream inFile;
    inFile.open(fileName, ios::in);
    if(!inFile.is_open())
    {
        cerr << "Error: File " << fileName << " not found" << endl;
        return FAILURE;
    }
    FileParser parser;
    int parseStatus = parser.parseDataFromFile(kingFamily, &inFile, inputFile);
    inFile.close();
    return parseStatus;
}

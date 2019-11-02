#include "file_parser.h"

int FileParser :: parseDataFromFile(Family* kingFamily, ifstream* file, bool inputFile)
{
    int parseStatus;
    string command;
    while(!file->eof())
    {
        getline(*file, command);
        if(inputFile)
            parseStatus = parseInputCommand(kingFamily, command);
        else
            parseStatus = parseInitCommand(kingFamily, command);
        if(parseStatus == FAILURE) return FAILURE;
    }
    return SUCCESS;
}

int FileParser :: parseInputCommand(Family* kingFamily, string command)
{
    string commandResult;
    vector<string> commandParam;
    commandParam = splitCommand(command, ' ');
    if(commandParam[0] == ADD_CHILD && (commandParam[3] == MALE || commandParam[3] == FEMALE) && commandParam.size() == 4 )
    {
        commandResult = kingFamily->addchild(commandParam[1], commandParam[2], commandParam[3]);
    }
    else if(commandParam[0] == GET_RELATIONSHIP && commandParam.size() == 3)
    {
        commandResult = kingFamily->getRelationship(commandParam[1], commandParam[2]);
    }
    else
    {
        commandResult = INVALID_COMMAND;
    }
    cout << commandResult << endl;
    return SUCCESS;
}

int FileParser :: parseInitCommand(Family* kingFamily, string command)
{
    vector<string> commandParam;
    commandParam = splitCommand(command, ';');
    if(commandParam[0] == ADD_FAMILY_HEAD && (commandParam[2] == MALE || commandParam[2] == FEMALE) && commandParam.size() == 3)
    {
        kingFamily->addFamilyHead(commandParam[1], commandParam[2]);
    }
    else if(commandParam[0] == ADD_CHILD && (commandParam[3] == MALE || commandParam[3] == FEMALE) && commandParam.size() == 4)
    {
        kingFamily->addchild(commandParam[1], commandParam[2], commandParam[3]);
    }
    else if(commandParam[0] == ADD_SPOUSE && (commandParam[3] == MALE || commandParam[3] == FEMALE) && commandParam.size() == 4)
    {
        kingFamily->addSpouse(commandParam[1], commandParam[2], commandParam[3]);
    }
    else
    {
        cerr << "INVALID INIT COMMAND!" << endl;
        return FAILURE;
    }
    return SUCCESS;
}

vector<string> FileParser :: splitCommand(string command, char delimiter)
{
    string param = BLANK;
    vector<string> commandParam;
    for(int i = 0; i < command.size(); i++)
    {
        if(command[i] == delimiter && param != "King" && param != "Queen")
        {
            commandParam.push_back(param);
            param = BLANK;
        }
        else
        {
            param += command[i];
        }
    }
    commandParam.push_back(param);
    return commandParam;
}

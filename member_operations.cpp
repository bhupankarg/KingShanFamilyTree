#include "member_operations.h"

Member :: Member(string name, string gender, Member* father, Member* mother)
{
    this->name = name;
    this->gender = gender;
    this->mother = mother;
    this->father = father;
    this->spouse = nullptr;
}

void Member :: addChild(Member* child)
{
    this->children.push_back(child);
}

void Member :: addSpouse(Member* spouse)
{
    this->spouse = spouse;
}

string Member :: searchChildren(string gender)
{
    string childrenList = BLANK;
    vector<Member*>::iterator itr;
    for(itr = this->children.begin(); itr != this->children.end(); itr++)
    {
        if((*itr)->gender == gender)
        {
            childrenList += (*itr)->name;
            childrenList += " ";
        }
    }
    return childrenList;
}

string Member :: searchChildren(string gender, string personName)
{
    string childrenList = BLANK;
    vector<Member*>::iterator itr;
    for(itr = this->children.begin(); itr != this->children.end(); itr++)
    {
        if(personName != (*itr)->name && (*itr)->gender == gender)
        {
            childrenList += (*itr)->name;
            childrenList += " ";
        }
    }
    return childrenList;
}

string Member :: searchSiblings()
{
    string siblingList = BLANK;
    if(this->mother != nullptr)
    {
        vector<Member*>::iterator itr;
        for(itr = this->mother->children.begin(); itr != this->mother->children.end(); itr++)
        {
            if(this->name != (*itr)->name)
            {
                siblingList += (*itr)->name;
                siblingList += " ";
            }
        }
    }
    return siblingList;
}

string Member :: searchUncleOrAunt(string gender)
{
    string uncleOrAuntList = BLANK;
    vector<Member*>::iterator itr;
    if(this->mother != nullptr)
    {
        for(itr = this->mother->children.begin(); itr != this->mother->children.end(); itr++)
        {
            if(this->name != (*itr)->name && (*itr)->gender == gender)
            {
                uncleOrAuntList += (*itr)->name;
                uncleOrAuntList += " ";
            }
	}
    }
    return uncleOrAuntList;
}

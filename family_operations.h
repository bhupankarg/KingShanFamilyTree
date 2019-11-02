#pragma once
#include "member_operations.cpp"

class Family
{
public:
    void addFamilyHead(string, string);
    void addSpouse(string, string, string);
    string addchild(string, string, string);
    string getRelationship(string, string);
private:
    Member* familyHead;
    string getRelationship(Member*, string);
    string searchInLaws(Member*, string);
    Member* searchMember(Member*, string);
};

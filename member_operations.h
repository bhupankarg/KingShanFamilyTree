#pragma once

using namespace std;

class Member
{
public:
    string name;
    string gender;
    Member* mother;
    Member* father;
    Member* spouse;
    vector<Member*> children;

    Member(string, string, Member*, Member*);
    void addChild(Member*);
    void addSpouse(Member*);
    string searchChildren(string);
    string searchChildren(string, string);
    string searchSiblings();
    string searchUncleOrAunt(string);
};

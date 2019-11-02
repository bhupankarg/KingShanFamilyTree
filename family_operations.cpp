#include "family_operations.h"

void Family :: addFamilyHead(string name, string gender)
{
    familyHead = new Member(name, gender, nullptr, nullptr);
}

void Family :: addSpouse(string memberName, string spouseName, string gender)
{
    Member* member = searchMember(familyHead, memberName);
    if(member != nullptr && member->spouse == nullptr)
    {
        Member* spouse = new Member(spouseName, gender, nullptr, nullptr);
        spouse->addSpouse(member);
        member->addSpouse(spouse);
    }
}

string Family :: addchild(string motherName, string childName, string gender)
{
    string result;
    Member* member = searchMember(familyHead, motherName);
    if(member == nullptr)
    {
        result = PERSON_NOT_FOUND;
    }
    else if(childName == BLANK || gender == BLANK)
    {
        result = CHILD_ADDITION_FAILED;
    }
    else if(member->gender == FEMALE)
    {
        Member* child = new Member(childName, gender, member->spouse, member);
        member->addChild(child);
        member->spouse->addChild(child);
        result = CHILD_ADDITION_SUCCEEDED;
    }
    else
    {
        result = CHILD_ADDITION_FAILED;
    }
    return result;
}

string Family :: getRelationship(string person, string relationship)
{
    string relations;
    Member* member = searchMember(familyHead, person);
    if (member == nullptr)
    {
        relations = PERSON_NOT_FOUND;
    }
    else if (relationship == BLANK)
    {
        relations = PROVIDE_VALID_RELATION;
    }
    else
    {
        relations = getRelationship(member, relationship);
    }
    return relations;
}

string Family :: getRelationship(Member* member, string relationship)
{
    string relations = BLANK;
    if(relationship == DAUGHTER)
    {
        relations = member->searchChildren(FEMALE);
    }
    else if(relationship == SON)
    {
        relations = member->searchChildren(MALE);
    }
    else if(relationship == SIBLINGS)
    {
        relations = member->searchSiblings();
    }
    else if(relationship == SISTER_IN_LAW)
    {
        relations = searchInLaws(member, FEMALE);
    }
    else if(relationship == BROTHER_IN_LAW)
    {
        relations = searchInLaws(member, MALE);
    }
    else if(relationship == MATERNAL_AUNT)
    {
        if (member->mother != nullptr)
            relations = member->mother->searchUncleOrAunt(FEMALE);
    }
    else if(relationship == PATERNAL_AUNT)
    {
        if (member->father != nullptr)
            relations = member->father->searchUncleOrAunt(FEMALE);
    }
    else if(relationship == MATERNAL_UNCLE)
    {
        if (member->mother != nullptr)
            relations = member->mother->searchUncleOrAunt(MALE);
    }
    else if(relationship == PATERNAL_UNCLE)
    {
        if (member->father != nullptr)
            relations = member->father->searchUncleOrAunt(MALE);
    }
    else
    {
        relations = NOT_YET_IMPLEMENTED;
    }
    return (relations == BLANK) ? NONE : relations;
}

string Family :: searchInLaws(Member* member, string gender)
{
    string personName = member->name;
    string result = BLANK;
    if(member->mother != nullptr)
    {
        vector<Member*>::iterator itr;
        for(itr = member->mother->children.begin(); itr != member->mother->children.end(); itr++)
        {
            if(personName != (*itr)->name && (*itr)->gender != gender)
            {
                if((*itr)->spouse != nullptr)
                {
                    result += (*itr)->spouse->name;
                    result += " ";
                }
            }
        }
    }
    else if(member->spouse != nullptr && member->spouse->mother != nullptr)
    {
        result += member->spouse->mother->searchChildren(gender, member->spouse->name);
    }
    return result;
}

Member* Family :: searchMember(Member* head, string memberName)
{
    if(memberName == BLANK || head == nullptr)
    {
        return nullptr;
    }
    Member* member = nullptr;
    if(head->name == memberName)
    {
        return head;
    }
    else if(head->spouse != nullptr && head->spouse->name == memberName)
    {
        return head->spouse;
    }
    vector<Member*> childlist;
    if(head->gender == FEMALE)
        childlist = head->children;
    else if(head->spouse != nullptr)
        childlist = head->spouse->children;
    vector<Member*>::iterator it;
    for(it = childlist.begin(); it != childlist.end(); it++)
    {
        member = searchMember(*it, memberName);
        if(member != nullptr) break;
    }
    return member;
}

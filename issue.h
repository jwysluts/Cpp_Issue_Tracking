#ifndef ISSUE_H
#define ISSUE_H

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

using namespace rapidjson;

class Issue
{
private:
        std::ifstream issueIn,
        issueListIn; //JSON File Storing List of Issues by status
        std::ofstream issueOut,
        issueListOut; //JSON File Storing List of Issues by status

        //Necessary Functions for Issue Class
        int getNextNumber(); //Gets the next sequential Issue Number
public:
        //User Functions
        void checkStatus(int); //Check the Status of a user given Issue Number
        void findIssue(int); //Find the Issue Number given by the user and print the data
        void createIssue(); // Create a new issue
        void changeStatus(int, std::string); //Change the status of an issue
        void getExistingIssues(std::string); //List existing issues that are in user provided status
        void updateIssue(int); //Update issue named by the user;
        void help();

};

void Issue::checkStatus(int issueNum)
{
    return;
}

void Issue::changeStatus(int issueNum, std::string status)
{
    return;
}

void Issue::createIssue()
{
    return;
}

void Issue::findIssue(int issueNum)
{
    return;
}

void Issue::help()
{
    return;
}

void Issue::getExistingIssues(std::string status)
{
    return;
}

void Issue::updateIssue(int issueNum)
{
    return;
}


#endif // ISSUE_H

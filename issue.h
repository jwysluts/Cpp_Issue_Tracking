#ifndef ISSUE_H
#define ISSUE_H

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"

#include <iostream>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <string>

using namespace rapidjson;

class Issue
{
private:
        std::string documentIn;
        std::ifstream issueIn,
        issueListIn; //JSON File Storing List of Issues by status
        std::ofstream issueOut,
        issueListOut; //JSON File Storing List of Issues by status

        //Necessary Functions for Issue Class
        int getNextNumber(Document &document) //Gets the next sequential Issue Number
        {
            int num;
            Value& nxtIssueNum = document["Next Number"];
            num = nxtIssueNum.GetInt();

            nxtIssueNum = nxtIssueNum.GetInt() + 1;

        }
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
    Document inDocument, newIssue;

    std::ifstream issueIn;
    std::string fileName="issues.json";

    issueIn.open(fileName.c_str(),std::ios::binary);

    std::streampos begin, end;

    begin=issueIn.tellg();
    issueIn.seekg(0,std::ios::end);
    end=issueIn.tellg();

    std::streampos size = end-begin;
    issueIn.seekg(0,std::ios::beg);

    char * fileData = new char[size];
    issueIn.read(fileData, size);
    fileData[size]='\0';
    issueIn.close();

    inDocument.Parse(fileData);

    Value& nxtIssueNum = inDocument["Next Number"];

    std::cout<< "Number before function: "<<nxtIssueNum.GetInt()<<std::endl;

    int nxtNum = getNextNumber(inDocument);

    std::cout<< "Number after function: "<<nxtIssueNum.GetInt()<<std::endl;

    fileName="newIssue.json";
    issueIn.open(fileName.c_str(),std::ios::binary);

    begin=issueIn.tellg();
    issueIn.seekg(0,std::ios::end);
    end=issueIn.tellg();

    size = end-begin;
    issueIn.seekg(0,std::ios::beg);

    char * issueFileData = new char[size];
    issueIn.read(issueFileData, size);
    issueFileData[size]='\0';
    issueIn.close();

    newIssue.Parse(issueFileData);

    Value& issueNum = newIssue["Number"];

    issueNum.SetInt(nxtNum);

    auto t = time(nullptr);
    auto tm = *std::localtime(&t);

    int month = tm.tm_mon + 1;
    int year = tm.tm_year + 1900;
    int day = tm.tm_mday;

    std::string date = std::to_string(month)+"-"+std::to_string(day)+"-"+std::to_string(year);
    std::cout<<"Today's Date: "<<date<<std::endl;

    Value& issueDate = newIssue["Date"];
    issueDate.SetString(date.c_str(), date.length());

    std::string status = "Open";

    Value& issueStatus = newIssue["Status"];
    issueStatus.SetString(status.c_str(), status.length());

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

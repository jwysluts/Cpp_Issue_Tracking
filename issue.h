#ifndef ISSUE_H
#define ISSUE_H

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include <iostream>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <string>

using namespace rapidjson;

class Issue
{
private:
        std::string inFileName, outFileName;

        //Necessary Functions for Issue Class
        int getNextNumber(Document &document) //Gets the next sequential Issue Number
        {
            int num;
            Value& nxtIssueNum = document["Next Number"];
            num = nxtIssueNum.GetInt();

            nxtIssueNum = nxtIssueNum.GetInt() + 1;

            return num;

        }
	Document genDoc(std::string fileName)
        {
             Document newDoc;
             std::ifstream issueIn;
             issueIn.open(fileName.c_str(),std::ios::binary);
             std::streampos begin, end;
             begin = issueIn.tellg();
             issueIn.seekg(0,std::ios::end);
             end = issueIn.tellg();
             std::streampos size = end - begin;
             issueIn.seekg(0,std::ios::beg);

             char * fileData = new char[size];
             issueIn.read(fileData, size);
             fileData[size]='\0';
             newDoc.Parse(fileData);
             issueIn.close();

             return newDoc;
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
    Document inDocument;

    std::ifstream issueIn;

    std::string numStr = std::to_string(issueNum);

    inDocument = genDoc("issues.json");

    bool issueExists = false;

    Value& issues = inDocument["Issues"];

    while(!issueExists)
        {
            for(auto& m : issues.GetObject())
            {
                if(issueNumStr==m.name.GetString()) issueExists = true;
            }

            if(!issueExists)
            {
                std::cout<<"No issue found with number " <<issueNum<<"\nPlease try again: ";
                std::cin>>issueNum;
            }

        }

    Value& checkIssue = issues[numStr.c_str()];

    Value& status = checkIssue["Status"];

    std::cout<<"Issue #"<<issueNum<<" has status "<<status.GetString()<<std::endl;

    return;
}

void Issue::changeStatus(int issueNum, std::string newStatus)
{
    Document inDocument;

    inDocument = genDoc("issues.json");

    std::string issueNumStr=std::to_string(issueNum), oldStatus;
    bool issueExists = false;

    Value& issues = inDocument["Issues"];

    while(!issueExists)
        {
            for(auto& m : issues.GetObject())
            {
                if(issueNumStr==m.name.GetString()) issueExists = true;
            }

            if(!issueExists)
            {
                std::cout<<"No issue found with number " <<issueNum<<"\nPlease try again: ";
                std::cin>>issueNum;
            }

        }

    while(newStatus!="Open" && newStatus!="Pending Solution" && newStatus!="Moved" && newStatus!="Closed")
    {
        if(newStatus!="Open" && newStatus!="Pending Solution" && newStatus!="Moved" && newStatus!="Closed")
        {
            std::cout<<"\nInvalid status: "<<newStatus<<"\nValid Statuses: Open, Pending Solution, Moved, Closed"<<std::endl
                     <<"\nPlease enter a valid status: ";

            std::getline(std::cin,newStatus);
        }
    }

    Value& issues = inDocument["Issues"];
    Value& issObj = issues[issueNumStr.c_str()];
    Value& StatObj = issObj["Status"];


    StatObj.SetString(newStatus.c_str(),newStatus.length());

    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    inDocument.Accept(writer);

    std::string fileName = "issues.json";
    const char* output = buffer.GetString();
    std::ofstream issueOut;
    issueOut.open(fileName.c_str(), std::ios::binary);
    issueOut<<output;
    issueOut.close();

    return;
}

void Issue::createIssue()
{
    std::ofstream issueOut;
    Document inDocument;
    Document newIssue(&inDocument.GetAllocator());
    Value issObj(kObjectType);

    inDocument = genDoc("issues.json");

    Value& issues = inDocument["Issues"];

    int nxtNum=getNextNumber(inDocument);
    std::string nxtNumStr = std::to_string(nxtNum);
    Value nxtNumStrObj;
    nxtNumStrObj.SetString(StringRef(nxtNumStr.c_str(),nxtNumStr.length()));

    newIssue = genDoc("newIssue.json");

    Value& issueNum = newIssue["Number"];

    issueNum.SetInt(nxtNum);

    auto t = time(nullptr);
    auto tm = *std::localtime(&t);

    int month = tm.tm_mon + 1;
    int year = tm.tm_year + 1900;
    int day = tm.tm_mday;

    std::string date = std::to_string(month)+"/"+std::to_string(day)+"/"+std::to_string(year);

    Value& issueDate = newIssue["Date"];
    issueDate.SetString(date.c_str(), date.length());

    std::string status = "Open";

    Value& issueStatus = newIssue["Status"];
    issueStatus.SetString(status.c_str(), status.length());

    Value& description = newIssue["Description"];
    std::string desc;

    std::cout<<"Please enter a description of your issue: ";
    std::getline(std::cin,desc);

    description.SetString(desc.c_str(),desc.length());

    issues.AddMember(nxtNumStrObj,newIssue,inDocument.GetAllocator());

    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    inDocument.Accept(writer);

    std::string fileName = "issues.json";
    const char* output = buffer.GetString();
    issueOut.open(fileName.c_str(),std::ios::binary);
    issueOut<<output;
    issueOut.close();

    return;
}

void Issue::findIssue(int issueNum)
{
    Document inDocument = genDoc("issues.json");

    std::string issueNumStr = std::to_string(issueNum);

    Value& issues = inDocument["Issues"];

    for(auto& m : issues.GetObject())
    {
        if(issueNumStr==m.name.GetString())
        {
            Value& tempIss = issues[m.name.GetString()];
            std::cout<<std::endl<<"------------------------- Issue #"<<issueNum<<" -------------------------"<<std::endl;
            std::cout<<"Status: "<<tempIss["Status"].GetString()<<"\t\tDate: "<<tempIss["Date"].GetString()<<std::endl<<std::endl;
            std::cout<<"Description: "<<tempIss["Description"].GetString()<<std::endl<<std::endl;
            std::cout<<"Update(s): "<<tempIss["Update(s)"].GetString()<<std::endl<<std::endl;
            return;
        }
    }
    std::cout<<"No issue found with number " <<issueNum<<"\nPlease try again."<<std::endl;
    return;
}

void Issue::help()
{
    std::cout<<"--------------- Help ---------------"<<std::endl;
    std::cout<<"n  -  New Issue"<<std::endl;
    std::cout<<"s  -  Get Status"<<std::endl;
    std::cout<<"f  -  Find Issue"<<std::endl;
    std::cout<<"c  -  Change Status" << std::endl;
    std::cout<<"e  -  Get Existing Issues" << std::endl;
    std::cout<<"u  -  Update Issue"<<std::endl;
    return;
}

void Issue::getExistingIssues(std::string status)
{
    Document inDocument = genDoc("issues.json");

    while(status!="Open" && status!="Pending Solution" && status!="Moved" && status!="Closed" && status!= "All")
    {
        if(status!="Open" && status!="Pending Solution" && status!="Moved" && status!="Closed" && status!="All")
        {
            std::cout<<"\nInvalid status: "<<status<<"\nValid Statuses: Open, Pending Solution, Moved, Closed"<<std::endl
                     <<"\nPlease enter a valid status: ";

            std::getline(std::cin,status);
        }
    }

    Value& issues = inDocument["Issues"];

    std::cout<<"--- "<<status;
    if(status!="Pending Solution")std::cout<<" Issues ---"<<std::endl;
    else std::cout<<" ---"<<std::endl;

    if(status=="All")
    {
        for(auto& m : issues.GetObject())
        {
            std::cout<<m.name.GetString()<<std::endl;
        }
    }
    else
    {
        for(auto& m : issues.GetObject())
        {
            Value& tempIss = issues[m.name.GetString()];
            Value& tempStat = tempIss["Status"];

            if(status==tempStat.GetString()) std::cout<<m.name.GetString()<<std::endl;
        }
    }
    return;
}

void Issue::updateIssue(int issueNum)
{
    std::string update, issueNumStr=std::to_string(issueNum);
    std::ofstream issueOut;
    Document inDocument = genDoc("issues.json");

    bool issueExists = false;

    Value& issues = inDocument["Issues"];

    while(!issueExists)
        {
            for(auto& m : issues.GetObject())
            {
                if(issueNumStr==m.name.GetString()) issueExists = true;
            }

            if(!issueExists)
            {
                std::cout<<"No issue found with number " <<issueNum<<"\nPlease try again: ";
                std::cin>>issueNum;
            }

        }


    Value& issObj = issues[issueNumStr.c_str()];
    Value& dateObj = issObj["Date"];

    auto t = time(nullptr);
    auto tm = *std::localtime(&t);

    int month = tm.tm_mon + 1;
    int year = tm.tm_year + 1900;
    int day = tm.tm_mday;

    std::string date = std::to_string(month)+"/"+std::to_string(day)+"/"+std::to_string(year);

    dateObj.SetString(date.c_str(),date.length());

    std::cout<<"Please enter an update for the issue: ";
    std::cin.ignore();
    std::getline(std::cin,update);

    update = date + " - " + update;

    Value& updtObj = issObj["Update(s)"];

    std::string oldUpdate = updtObj.GetString();

    if(oldUpdate!="")
    {
        update =update + "\n\n" +oldUpdate;
    }

    updtObj.SetString(update.c_str(), update.length());

    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    inDocument.Accept(writer);

    std::string fileName = "issues.json";
    const char* output = buffer.GetString();
    issueOut.open(fileName.c_str(),std::ios::binary);
    issueOut<<output;
    issueOut.close();

    return;
}


#endif // ISSUE_H

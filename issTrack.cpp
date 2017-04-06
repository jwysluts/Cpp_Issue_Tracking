#include <iostream>
#include <string>


#include "issue.h"

int main(int argc, char*argv[])
{
    Issue myIssue;
    int issueNum;
    std::string description, status;

    //std::cout<<"Number of arguments: "<<argc<<std::endl<<"Argument Entered: " << *argv[1]<<std::endl;

    if(*argv[1]=='n') myIssue.createIssue();

    else if(*argv[1]=='s')
    {
        std::cout<<"Please enter an issue number you are checking the status of: ";
        std::cin>>issueNum;
        myIssue.checkStatus(issueNum);
    }

    else if(*argv[1]=='f')
    {
        std::cout<<"Please enter an issue number you wish to find: ";
        std::cin>>issueNum;
        myIssue.findIssue(issueNum);
    }

    else if(*argv[1]=='c')
    {
        std::cout<<"Please enter an issue number: ";
        std::cin>>issueNum;
        myIssue.checkStatus(issueNum);

        std::cout<<"Please enter the new status of this issue: ";
        std::cin.ignore();
        std::getline(std::cin, status);
        myIssue.changeStatus(issueNum,status);
    }

    else if(*argv[1]=='e')
    {
        std::cout<<"Please enter a status: ";
        std::getline(std::cin,status);
        myIssue.getExistingIssues(status);
    }

    else if(*argv[1]=='u')
    {
        std::cout<<"Please enter an issue number: ";
        std::cin>>issueNum;
        myIssue.updateIssue(issueNum);
    }

    else
    {
        myIssue.help();
    }

    return 0;
}


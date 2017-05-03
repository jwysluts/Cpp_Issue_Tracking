#include <iostream>
#include <string>


#include "issue.h"

int main(int argc, char*argv[])
{
    Issue myIssue;
    int issueNum;
    std::string description, status;

    if(*argv[1]=='n') myIssue.createIssue();

    else if(*argv[1]=='s')
    {
        std::cout<<"Please enter an issue number you are checking the status of: ";
        std::cin>>issueNum;
        std::cout<<std::endl;
        myIssue.checkStatus(issueNum);
    }

    else if(*argv[1]=='f')
    {
        std::cout<<"Please enter an issue number you wish to find: ";
        std::cin>>issueNum;
        std::cout<<std::endl;
        myIssue.findIssue(issueNum);
    }

    else if(*argv[1]=='c')
    {
        std::cout<<"Please enter an issue number: ";
        std::cin>>issueNum;
        std::cout<<std::endl;
        std::cout<<std::endl;
        myIssue.checkStatus(issueNum);

        std::cout<<"Please enter the new status of this issue: ";
        std::cin.ignore();
        std::getline(std::cin, status);
        std::cout<<std::endl;
        myIssue.changeStatus(issueNum,status);
    }

    else if(*argv[1]=='e')
    {
        std::cout<<"Please enter a status or \"All\": ";
        std::getline(std::cin,status);
        std::cout<<std::endl;
        myIssue.getExistingIssues(status);
    }

    else if(*argv[1]=='u')
    {
        std::cout<<"Please enter an issue number: ";
        std::cin>>issueNum;
        std::cout<<std::endl;
        myIssue.updateIssue(issueNum);
    }

    else
    {
        std::cout<<std::endl;
        myIssue.help();
    }

    std::cout<<std::endl;

    return 0;
}


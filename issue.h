#ifndef ISSUE_H
#define ISSUE_H

#include <iostream>
#include <fstream>
#include <string>

class Issue
{
private:
        ifstream issueIn,
        issueListIn; //JSON File Storing List of Issues by status
        ofstream issueOut,
        issueListOut; //JSON File Storing List of Issues by status

        //Necessary Functions for Issue Class
        int getNextNumber(); //Gets the next sequential Issue Number

        //User Functions
        void checkStatus(int); //Check the Status of a user given Issue Number
        void findIssue(int); //Find the Issue Number given by the user and print the data
        void createIssue(); // Create a new issue
        void changeStatus(int, std::string); //Change the status of an issue
        void getExistingIssues(std::string); //List existing issues that are in user provided status
        void updateIssue(int); //Update issue named by the user;

};


#endif // ISSUE_H

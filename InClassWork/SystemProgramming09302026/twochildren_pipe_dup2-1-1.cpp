//Goal is to practice using fork, wait, dup, dup2, pipe, execvp system calls.
/*this program implements piping process in Linux.One child executes the first command
and feeds the output to the second child which executes the second commmand on the coming data.*/

#include <stdio.h>
#include <stdlib.h> // exit
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream> // std::stringstream

using namespace std;

//tokenizing function
vector <string> getTokenVector(string);
int main() {

	string userLine;

	//reading the first command from the user:
	cout << "Enter the first command:\n";
	getline(cin, userLine);
	vector<string> cmd1TokenVector = getTokenVector(userLine);
	//moving the tokens to a c string so that it is passed to the execvp function
	char* cmd1[cmd1TokenVector.size() + 1];

	for (int i = 0; i < cmd1TokenVector.size(); ++i)
		cmd1[i] = (char*)cmd1TokenVector[i].c_str();

	cmd1[cmd1TokenVector.size()] = NULL;

	//reading the second command from the user:
	cout << "Enter the second command:\n";
	getline(cin, userLine);
	vector<string> cmd2TokenVector = getTokenVector(userLine);
	char* cmd2[cmd2TokenVector.size() + 1];

	for (int i = 0; i < cmd2TokenVector.size(); ++i)
		cmd2[i] = (char*)cmd2TokenVector[i].c_str();

	cmd2[cmd2TokenVector.size()] = NULL;

	//let us work on the pipe:
	int fds[2]; // this is for the pipe file descriptors
	if (pipe(fds) < 0) {
		cout << "Error: Cannot create the pipe" << endl;
		exit(1);
	}

	//store original std in and out
	int originalSTDIN = dup(0);
	int originalSTDOUT = dup(1);

	pid_t pid;
	pid = fork();  //first child for cmd1
	if (pid < 0) {
		cout << "Error: Cannot create a process" << endl;
		exit(2);
	}
	else if (pid == 0) { // I am inside the first child

		/*We change the stdout for the first child*/
		dup2(fds[1], 1);
		close(fds[1]);
		/*closing the reading end*/
		close(fds[0]);

		//change the execution image of the child with the first command (program) entered by the user.
		if (execvp(cmd1[0], cmd1) < 0) {
			cout << "Error: Cannot chnage the process exe image a process" << endl;
			exit(3);
		}
	}
	else if (pid > 0) { /*inside the parent*/
		wait(0); // wait for the first child

		/*We change the stdin for the second child*/
		dup2(fds[0], 0);
		close(fds[0]); // closing the duplicated end
		/*closing the wrting end*/
		dup2(originalSTDOUT, 1);
		close(fds[1]);
		pid_t pid2;
		pid2 = fork(); // second child
		if (pid2 < 0) {
			cout << "Error: Cannot create a process" << endl;
			exit(4);
		}
		else if (pid2 == 0) { // I am inside the second child
			//change the execution image of the second child with the second command (program) entered by the user.
			if (execvp(cmd2[0], cmd2) < 0) {
				cout << "Error: Cannot change the process exe image of the second child process " << endl;
				exit(5);
			}
		}
		else if (pid2 > 0) {
			wait(0); // wait for the second child
			//we get things stdin and out back to normal
			dup2(originalSTDIN, 0);
			dup2(originalSTDOUT, 1);
			close(originalSTDIN);
			close(originalSTDOUT);
			fflush(stdout);
			cout << "I am the parent and done with the children work!" << endl;
		}
	}
	return 0;
} //end of main

//tokenizing function
vector <string> getTokenVector(string userLine) {
	vector<string> tmpVec;
	stringstream streamObj = stringstream(userLine);
	string currentToken;
	while (streamObj >> currentToken)
		tmpVec.push_back(currentToken);
	return tmpVec;
}

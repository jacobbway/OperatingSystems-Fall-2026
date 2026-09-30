#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <string.h>
#include<unistd.h>  //getcwd
#include <sstream>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
using namespace std;
int main() {
	string fileName = "input.txt";

	//open file for input
	int inFd = open(((char*) fileName.c_str()), O_RDONLY);
	int orgIn = dup(0);
	dup2(inFd, 0);
	string currentToken;
	while (cin >> currentToken)
		cout << currentToken << endl;
	dup2(orgIn, 0);

	cout << "Done Reading the file!\n";

	return 0;
}
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
	string fileName = "output.txt";

	//open file for output
	//0666 for read and write access
	//O_CREAT if file is not there will be created for you.

	int outFd = open( ( (char*) fileName.c_str() ), O_WRONLY | O_CREAT, 0666);
	int orgOut = dup(1);
	dup2(outFd, 1);
	
	for (int i = 0; i < 10; ++i)
		cout << "token" << i << endl;

	dup2(orgOut, 1);

	cout << "Done writing to the file!\n";

	return 0;
}
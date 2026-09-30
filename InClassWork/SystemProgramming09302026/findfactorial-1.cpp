#include <iostream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include<sys/wait.h>
#include <stdlib.h>     /* exit, EXIT_FAILURE */
using namespace std;
int main() {

	//creating two pipes
	int fdparent2child[2], fdchild2parent[2];

	if (pipe(fdparent2child) < 0)
	{
		cout << "Cannot create the pipe\n";
		exit(1);
	}
	if (pipe(fdchild2parent) < 0)
	{
		cout << "Cannot create the pipe\n";
		exit(2);
	}

	int pid = fork();
	if (pid < 0) {
		cout << "Cannot create the child process\n";
		exit(3);
	}
	else if (pid > 0) //parent
	{
		int intValue;
		cout << "Please enter an integer number -> ";
		cin >> intValue;
		int orgSTDOut = dup(1);  // store the original input FD
		/* Parent process closes up input side of pipe */
		close(fdparent2child[0]);
		/* Send the integer value through the output side of the pipe */
		//change stdout to be the pipe
		dup2(fdparent2child[1], 1);
		cout << intValue << endl;  //this will be written to the pipe
		//back to normal stdout
		dup2(orgSTDOut, 1);
		//wait for the child to finish the work.
		wait(NULL);

		//receiving the result from the child via the other pipe
		close(fdchild2parent[1]);

		int orgSTDIN = dup(0);  // store the original input FD
		//changing the stdin
		dup2(fdchild2parent[0], 0);
		int result;
		cin >> result; //reading from the pipe
		cout << "From Parent: Received result: " << result << endl;
		//back to normal stdin
		dup2(orgSTDIN, 0);
	}
	else //child
	{
		/* Child process closes up output side of pipe */
		close(fdparent2child[1]);
		/* Read in the number from the pipe */
		int orgSTDIN = dup(0);  // store the original input FD
		dup2(fdparent2child[0], 0);
		int comingInteger, factorial = 1;
		cin >> comingInteger;
		cout << "From Child: Received int: " << comingInteger << endl;
		for (int i = 1; i <= comingInteger; ++i)
			factorial = factorial * i;
		dup2(orgSTDIN, 0); /// get the input FD back to normal

		//sending the factorial via the second pipe
		int orgSTDOut = dup(1);  // store the original input FD
		close(fdchild2parent[0]);
		/* Send the integer value through the output side of the pipe */
		cout << "I am sending " << factorial << endl;
		dup2(fdchild2parent[1], 1);
		cout << factorial << endl;  //this will be written to the pipe
		dup2(orgSTDOut, 1);
		exit(0);
	}


	return 0;
}
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include<sys/wait.h>
#include <stdlib.h>     /* exit, EXIT_FAILURE */
#include <iostream>
using namespace std;
int main()
{
	size_t Maxsize = 80;
	int     fd[2], nbytes;
	pid_t   childpid;
	char    readbuffer[80];

	char    sharedStr[] = "Hello, CS442!";

	if (pipe(fd) < 0)  //create a pipe
		exit(1);  // error. No pipe was created.
	////////////////////////////////////


	if ((childpid = fork()) == -1)
	{
		perror("fork did not work; Sorry!");
		exit(1);
	}


	if (childpid == 0)
	{
		int orgSTDIN = dup(0);  // store the original input FD

		/* Child process closes up output side of pipe */
		close(fd[1]);
		/* Read in a string from the pipe */
		string readbuffer2, fullName, address;
		dup2(fd[0], 0);
		getline(cin, readbuffer2);
		getline(cin, fullName);
		getline(cin, address);
		cout << "From Child: Received string: " << readbuffer2 << endl;
		cout << "From Child: Received string: " << fullName << endl;
		cout << "From Child: Received string: " << address << endl;
		dup2(orgSTDIN, 0); /// get the input FD back to normal

		exit(0);
	}
	else
	{
		int orgSTDOut = dup(1);  // store the original output FD
		/* Parent process closes up input side of pipe */
		close(fd[0]);
		/* Send "string" through the output side of pipe */
		dup2(fd[1], 1);
		cout << sharedStr << endl;
		cout << "Saleh M. Alnaeli" << endl;
		cout << "Menomonie, WI 54751" << endl;
		dup2(orgSTDOut, 1);

		wait(NULL);
		cout << "back to the screen" << endl;
	}

	return(0);
}

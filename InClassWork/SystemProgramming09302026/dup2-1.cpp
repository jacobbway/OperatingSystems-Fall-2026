#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <string>
using namespace std;
int main()
{
	int orgOut = dup(1); // save the original stdout
	/* system call open() returns a file
	descriptor fd to a the file "duptest.txt"
		stores in the same location*/
	int fd = open("dup2test.txt", O_WRONLY | O_APPEND);
	if (fd < 0) {
		cout << "Can not open the file" << endl;
		exit(1);
	}
	// here the newfd is the file descriptor of 
   //stdout (i.e. 1) 
	dup2(fd, 1);
	/* All the output statements will be written in the file*/
		// "dup2test.txt" 
	cout << "I will be written to the file dup2test.txt" << endl;


	// write() will write msg1 and msg2 to the 
	//file using  the file descriptor
	string msg1 = "I am Dr. Alnaeli\n";
	string msg2 = "I live in Menomonie\n";
	cout << msg1;
	write(fd, (char*)msg2.c_str(), msg2.size());
	close(fd);

	//get things back to normal
	fflush(stdout); //clearing buffer

	dup2(orgOut, 1);
	cout << "Back to the original output\n";
	return 0;
}//end of main
#include<stdio.h>

#include<stdlib.h>

#include <unistd.h>

#include <fcntl.h>

#include <iostream>

#include <string>

using namespace std;

int main()

{   // system call open() returns

//a file descriptor fd to a the file

//"duptest.txt" stored in the same location

	int fd = open("duptest.txt",

		O_WRONLY | O_APPEND);

	if (fd < 0) {

		cout << "Can not open the file" << endl;

		exit(1);

	} //end if

	// dup() will create the copy of fd as the //copy_fd then both can be used interchangeably //as needed.
	//means a new slot in the table will be used and the fd file descriptor will be copied there.
	int copy_fd = dup(fd);
	//not the same cells in the file descriptor table. But should be the same content. 
	//cout << fd << endl;
	//cout << copy_fd << endl;
	//write() will write msg1 and msg2 to the file //using  the file descriptors

	string msg1 = "I am Dr. Alnaeli\n";

	string msg2 = "I live in Menomonie\n";

	//writing via the copy file descriptors

	write(copy_fd, (char*)msg1.c_str(), msg1.size());

	//writing via the original file descriptors

	write(fd, (char*)msg2.c_str(), msg2.size());

	return 0;

} //end of main
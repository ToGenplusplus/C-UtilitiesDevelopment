/**
 *This file will mv or rename  all the information of the file passed
 *as the second argument parameter to the third argument in parameter.
 * Author: Temi Owoaje
 * 250980280
 * October 2nd 2019
 **/
#include <iostream>
#include <stdio.h>
#include "Filemanager.h"

using namespace std;

int main (int args, char * argv[])
{

	if(args == 1)
	{
		cout<< "Missing file operand "<<endl;

	}
	else if(args ==2)// does the same thing as cp command, prints missing destination,
	{
		cout<< "Missing destination "<<endl;

	}
	else if(args == 3)	//ensure all arguments needed  for command to work are presented
	{
		Filemanager file1(argv[1]);

		if(file1.setFileName(argv[2]) != 0)
		{
			ofstream destination(argv[2], ios_base:: out | ios_base :: binary);
			if(destination.is_open())
			{

				file1.dump_file(&destination);

				file1.remove_file();

				destination.close();
			}


		}


	}
	else
	{

		cout<<"invalid number of arguments"<<endl;
	}



	return 0;

}

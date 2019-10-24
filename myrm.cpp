
/**
 * Author: Temi Owoaje
 * myrm.cpp - removes files passed as parameters from the file system.
 *250980280
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
	else if (args > 1)
	{

		for(int i = 1; i < args; i++)
		{
			Filemanager file(argv[i]);// create new file objects for each file listed as paramters

			file.remove_file();	//remove each file from system. 

		}
	}

return 0;
}


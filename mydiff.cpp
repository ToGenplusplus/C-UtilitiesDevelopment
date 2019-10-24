/**
 * Temi Owoaje
 * mydiff.cpp file - compare to files passed as paramters
 * 250980280
 * Oct 2nd 2019
**/

#include <iostream>
#include <stdio.h>
#include "Filemanager.h"

using namespace std;

int main (int args, char * argv[])
{

        if(args == 1)
        {
                cout<< "Missing file operand after ./mydiff "<<endl;

        }
        else if(args ==2)
        {


                cout<< "Missing comparison file "<<endl;

        }
	else if(args == 3)
	{

		Filemanager file1(argv[1]);

		Filemanager file2(argv[2]);

		if(file1.getfile_type() =="" || file2.getfile_type() == "")
		{

			cout<<"file doesn't exist"<<endl;
		}
		else if(file1.geterr_num() == 0 && file2.geterr_num() == 0)
		{

			file1.compare_files(file2);

		}
	}
	return 0;
}


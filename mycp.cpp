/**
 * Temi Owoaje
 * mycp.cpp file, used to copy contents of one file to another
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
                cout<< "Missing file operand after cp "<<endl;

        }
        else if(args ==2)
        {
                cout<< "Missing destination "<<endl;

        }
	else if(args == 3)// ensures we have all arguments needed for command to work.
        {
                Filemanager file1(argv[1]);

		ofstream destination(argv[2], ios_base:: out | ios_base :: binary);

		if(destination.is_open())
		{

			file1.dump_file(&destination);
			destination.close();
		}
	}
	else
	{
		cout<<"invalid number of argumnets"<<endl;
	}

return 0;

}

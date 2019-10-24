/**
 * Temi Owoaje
 *250980280
 *mycat.cpp displays file contents passed as paramters to the terminal
 * October 2nd 2019
 **/
#include <iostream>
#include <stdio.h>
#include <fstream>
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

			if(file.getfile_type() == "")//checks to see if file donest exist (the stat isn't returning the right error number so had to do this manually

			{

				cout<<file.getFileName()<< ": "<< " No such file or directory"<<endl;
				break;
			}

			else
			{

	                        file.dump_file(&cout);

			}
                }
 
     }

return 0;
}


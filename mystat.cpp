/**
 *Temi Owoaje
 *250980280
 *mystat.cpp impelements the unix like stat command.
 * Oct 2nd 2019
 **/
#include <iostream>
#include <stdio.h>
#include "Filemanager.h"
#include <time.h>
using namespace std;

int main (int args, char * argv[])
{

        if(args == 1)
        {
                cout<< "Missing file operand ./mystat "<<endl;

        }
	else if(args == 2)
	{

		time_t act,modt,statt;

		Filemanager file1(argv[1]);




		if(file1.getfile_type() == "")
		{
			file1.reset_attributes();
			cout<<"no such file or directory"<<endl;
		}

		else if(file1.geterr_num() == 0)
		{

			cout<< "File : "<<file1.getFileName()<<endl;
			cout<< "Size : "<<file1.get_filesize()<<"	";
			cout<< "Blocks : "<<file1.get_blksize()<<"	";
			cout<< "Filetype : "<<file1.getfile_type()<<endl;
			cout<< "Access: ";
			file1.printPermissions(file1.getFilemode(),file1.getBuffer());
			cout<< "		";
			cout<< "(Owner : "<<file1.get_ownernumber()<<"/ "<<file1.get_ownerstring()<<")		";
			cout<< "(Gid  : ( "<<file1.get_grp_id_number()<<"/ 	"<<file1.get_grp_id_string()<<" )   	"<<endl;

			act =file1.getAccesstime();
			modt = file1.getmodtime();
			statt = file1.getstatuschange();
			char * actime = ctime(&act);
			char * modtime = ctime(&modt);
			char * stattime = ctime(&statt);

			cout<< "Access: "<<actime<<endl;
			cout<< "Modify: "<<modtime<<endl;
			cout<< "Change: "<<stattime<<endl;

		}


	}



return 0;
}



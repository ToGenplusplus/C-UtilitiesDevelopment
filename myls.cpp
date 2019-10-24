/**
* Temi Owoaje
* 250980280
* myls.cpp stripped down version of the unix ls command
* Ocotober 2nd 2019
**/
#include <iostream>
#include <stdio.h>
#include "Filemanager.h"

using namespace std;

int main (int args, char * argv[])
{

        if(args == 1)//check to see if ony ./myls was called and will display only contents under current directory
        {
                Filemanager dirfile(".");
		dirfile.Expand();

		int size =dirfile.getChildren().size();

		for(int i= 0; i < size; i++)
		{
			cout<<dirfile.getChildren()[i].getFileName()<<"	";
		}
		cout<<endl;

        }
	else if(args == 2)
	{

		string arg = argv[1];

		if(arg == "-l")	// want to check if the -l option is set for current directory
		{

			Filemanager dirfile(".");
        	        dirfile.Expand();

	                int size =dirfile.getChildren().size();

	                for(int i= 0; i < size; i++)
        	        {
                	        dirfile.getChildren()[i].printPermissions(dirfile.getChildren()[i].getFilemode(),dirfile.getChildren()[i].getBuffer());
				cout<<" "
				<<dirfile.getChildren()[i].get_ownerstring()<<" "
				<<dirfile.getChildren()[i].get_grp_id_string()
				<< " "<<dirfile.getChildren()[i].getFileName()<<endl;
                	}
                	cout<<endl;

		}
		else
		{

			Filemanager dirfile(argv[1]);
	                if(dirfile.getfile_type() == "Regular")
			{

				cout<<dirfile.getFileName()<<endl;
			}

			if(dirfile.Expand() == 0)
			{

        	        	int size =dirfile.getChildren().size();

	                	for(int i= 0; i < size; i++)
       	         		{
                        		cout<<dirfile.getChildren()[i].getFileName()<<"	";
                		}
				cout<<endl;

			}
			else
			{

				cout<< dirfile.geterr_message(dirfile.geterr_num())<<endl;

			}
		}
	}
	else if(args ==3)

	{

		string argument =argv[1];

		if(argument == "-l")// check is the -l option is set for a specified path or file
                {
			Filemanager dirfile(argv[2]);

			if(dirfile.getfile_type() == "Regular")
			{

				dirfile.printPermissions(dirfile.getFilemode(),dirfile.getBuffer());
        	                cout<<" "
                	        <<dirfile.get_ownerstring()<<" "
                        	<<dirfile.get_grp_id_string();
				cout<< " 	";

				cout<< dirfile.getFileName()<<endl;

			}

			if(dirfile.Expand() == 0)

			{
                		int size =dirfile.getChildren().size();

                		for(int i= 0; i < size; i++)
                		{

				dirfile.getChildren()[i].printPermissions(dirfile.getChildren()[i].getFilemode(),dirfile.getChildren()[i].getBuffer());
				cout<<" "
                        	<<dirfile.getChildren()[i].get_ownerstring()<<" "
                        	<<dirfile.getChildren()[i].get_grp_id_string()
                        	<< " "<<dirfile.getChildren()[i].getFileName()<<endl;

                		}
               			 cout<<endl;
			}
			else
			{
				cout<< dirfile.geterr_message(dirfile.geterr_num())<<endl;



			}

                }
		else
		{


			cout<<"operation not supported"<<endl;
		}

	}
	else
	{
		cout<<"operation  not supported, invalid number of arguments"<<endl;

	}

return 0;

}

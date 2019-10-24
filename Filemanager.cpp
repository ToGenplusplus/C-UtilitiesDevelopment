
/**
 * File manager class to  help manage files on the raspberry pi Desktop system.
 * Author : Temi Owoaje, 250980280.
 * October 2nd 2019
 **/

#include <iostream>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fstream>
#include <time.h>
#include <dirent.h>
#include "Filemanager.h"


using namespace std;





		Filemanager :: Filemanager (char *filename)
		{
			struct stat buf;
			f_name = string(filename);

			if(stat(filename,&buf)== 0)

			{
				this->buffer = buf;
				getsetfile_type(buf.st_mode,this->buffer);
				f_mode = buf.st_mode;
				f_size = buf.st_size;
				f_ownernumber = buf.st_uid;
				f_ownerstring= getpwuid(buf.st_uid)->pw_name;
				grp_idnumber = buf.st_gid;
				grp_idstring = getgrgid(buf.st_gid)->gr_name;
				file_accesstime = buf.st_atim.tv_sec;
				file_modificationtime = buf.st_mtim.tv_sec;
				file_statuschange = buf.st_ctim.tv_sec;
				blk_size = buf.st_blksize;

			}


		}

		/**
		 *This function will take a file stream as a parameter and dump the
		 * contents of the named file to that file stream, returns error number, 0 if
		 * succesful.
		**/ 

		int Filemanager :: dump_file(ostream * contents_destination)
		{
			if(getfile_type() != "Regular")
			{
				error_num = ENOTSUP;
				cout<< "an error has occured: "<< geterr_message(error_num)<<endl;
			}

			fstream basefile(this->f_name.c_str(), ios_base :: in);


			if (basefile.is_open())
			{


				char  * buffer = new char[ this->blk_size];




				basefile.read(buffer,this->blk_size);
				contents_destination->write(buffer,this->blk_size);



				delete [] buffer;	//release dynamically allocated memory.

				basefile.close();
				//contents_destination->close();
			error_num = errno;// check for succesful operation of close
			}

			else
			{

			error_num = errno;
			cout <<"operation not succesful : "<< geterr_message(error_num)<<endl;

			}


		return error_num;

		}

		/**
                 * Function renames the file invoked by this filemanager object with new file name passed in
		 * the parameter, return error number, 0 if succesfull.
		**/

		int Filemanager :: rename_file(char * newname)
		{


			rename(this->f_name.c_str(),newname);
			error_num = errno;
			if(error_num != 0)
			{

				cout<< "Operation could not be completed : " << geterr_message(error_num) <<endl;
			}

			this->f_name = newname;

			return error_num;

		}


		/**
		 * Function removes the file invoked by this filemanager object from the system.
		 **/


		int Filemanager :: remove_file()
		{
			if(unlink(this->f_name.c_str()) == 0)
			{

				reset_attributes();

			}
			else
			{
				this->error_num = errno;
				cout<< "Operation could not be completed : " << geterr_message(error_num) <<endl;
			}

			return error_num;

		}



		/**
		 *Function takes in another filemanager objet as a parameter and
 		 *compares the contents of the file this fileobject was invoked with the paramter fileobject.
		**/

		int Filemanager :: compare_files(Filemanager newobject)
		{


			if(this->blk_size != newobject.get_blksize())
			{

				cout<< "file contents not the same"<<endl;
				error_num = errno;

			}

			else
			{

				fstream invokedFile(this->f_name.c_str(),ios_base :: in | ios_base ::binary);

				fstream compareFile(newobject.getFileName().c_str(),ios_base :: in | ios_base ::binary);

				if (invokedFile.is_open() && compareFile.is_open())
                        	{


                                	char  * buffer = new char[ this->blk_size];
					char  * buffer1 = new char [newobject.get_blksize()];



                                        	invokedFile.read(buffer,this->blk_size);
                                        	compareFile.read(buffer1,this->blk_size);


					if(invokedFile.gcount() == compareFile.gcount())	//validate that both files
												//have the same number of characters

					{
						for(int i=0; i <= invokedFile.gcount(); i++)
						{
							if(buffer[i] != buffer1[i])
							{
								cout<< "file contents are not the same"<<endl;
								break;
							}

							if(i = invokedFile.gcount() && buffer[i] == buffer1[i])
							{
								cout<<"file contents are the same"<<endl;
								break;
							}
						}
					}
					else
					{
						cout<< "file contents are not the same"<<endl;

					}
					error_num = errno;





                                	delete [] buffer;
								//delete dynamically allocated memory.
					delete [] buffer1;

                                	invokedFile.close();
                                	compareFile.close();
                        	error_num = errno;

				if(error_num != 0)
                        	{
                                cout<< "operation could not be compeleted : " << geterr_message(error_num)<< endl;
                        	}

                        	}
			}


			return error_num;

		}

		/**
		 *This function operates on directories only and is used to fill
		 * in the children of the file object this function was invoked upon.
		 * returns 0 if operation succesfull else returns error_number.
		**/

		int Filemanager :: Expand()
		{

			if(this->file_type == "Directory")
			{

				DIR * dfile = opendir(this->f_name.c_str());


				error_num = errno;

				errno = 0;
				struct dirent *d_info;
				error_num = errno;


				while(  (d_info=readdir(dfile)) != NULL)
				{

					Filemanager file_to_insert(d_info->d_name);
					children.push_back(file_to_insert);
					error_num = errno;

				}

				closedir(dfile);



			}

			if(this->file_type == "")
			{
				cout<< "file does not exist"<<endl;

			}

			return error_num;

		}

		/**
		* function gets and returns the filename
		* of specific filemanager instance
		**/

		string Filemanager ::  getFileName()
		{
			return this->f_name;
		}


		/**
		 * This function renames the inoked file with the name passed in the parameter
		 * it also renames the file in the system.
		 **/
		int Filemanager :: setFileName(char * file_name)
		{
			return rename_file(file_name);		//calls above rename_file method to rename the file in system.

		}

		/**
		* this funciton returns the string representation
		* of the type of file in specific filemanager object
		**/

		string Filemanager :: getfile_type()
		{
			return this->file_type;
		}

		mode_t Filemanager ::  getFilemode()
		{
			return this->f_mode;
		}

		/**
                *getter function to get file owners name.
                **/

		string Filemanager ::get_ownerstring()
                {
                        return this->f_ownerstring;
                }

		/**
                *getter function to get group id as a string.
                **/


                string Filemanager :: get_grp_id_string()
                {
                        return this->grp_idstring;
                }


		/**
		* this is a helper function to get the type of file from the buffer
		* and set the filetype attribute accordingly.
		* takes in two parameters,buffer and a mode_t type
		**/


		void Filemanager :: getsetfile_type(mode_t name,struct stat buf)
		{

			if((buf.st_mode & S_IFMT) == S_IFREG)
                        {
				this->file_type = "Regular";
                        }
			else if((buf.st_mode & S_IFMT) == S_IFDIR)
			{

                                this->file_type = "Directory";
			}
			else if((buf.st_mode & S_IFMT) == S_IFLNK)
			{

                                this->file_type = "symbolic link";

			}
			else if((buf.st_mode & S_IFMT) == S_IFBLK)
			{
				this->file_type = "Block device";

			}else if((buf.st_mode & S_IFMT) == S_IFSOCK)
			{
				this->file_type =  "socket";

			}
			else if((buf.st_mode & S_IFMT) == S_IFCHR)
			{
				this->file_type = "character device";

			}
			else if((buf.st_mode & S_IFMT) == S_IFIFO)
			{

				this->file_type = "FIFO";
			}
			else
			{
				cout<< " prohibited file type" <<endl;
				this->file_type = "Not appplicable";
			}


		}
		/**
		* Function prints the invoked file names permissions.
		*
		**/

		void Filemanager :: printPermissions(mode_t name, struct stat buf)
		{


			printf( (S_ISDIR(buf.st_mode)) ? "d" : "-");
    			printf( (buf.st_mode & S_IRUSR) ? "r" : "-");
    			printf( (buf.st_mode & S_IWUSR) ? "w" : "-");
    			printf( (buf.st_mode & S_IXUSR) ? "x" : "-");
    			printf( (buf.st_mode & S_IRGRP) ? "r" : "-");
    			printf( (buf.st_mode & S_IWGRP) ? "w" : "-");
    			printf( (buf.st_mode & S_IXGRP) ? "x" : "-");
    			printf( (buf.st_mode & S_IROTH) ? "r" : "-");
    			printf( (buf.st_mode & S_IWOTH) ? "w" : "-");
    			printf( (buf.st_mode & S_IXOTH) ? "x" : "-");



		}



		/**
		 * Helper function to help reset an invoked files attributes
		 *
		**/

		void Filemanager :: reset_attributes()
		{

			time_t reset;
			mode_t resetMode;


			this->error_num == 0;
			this->file_type = "Not applicable";
                        this->f_size = 0;
			this->f_mode = resetMode;
			this->f_permissions = "n/a";
                        this->f_ownernumber = 0;
                        this->f_ownerstring = "Not applicable";
                        this->grp_idnumber = 0;
                        this->grp_idstring = "Not applicable";
                        this->file_accesstime = reset;
                        this->file_modificationtime = reset;
                        this->file_statuschange = reset;
                        this->blk_size = 0;


		}

		/**
                *getter function to get file group id number.
                **/

		int Filemanager :: get_grp_id_number()
		{
			return this->grp_idnumber;
		}

		/**
                *getter function to get file owner number.
                **/


		int Filemanager :: get_ownernumber()
		{
			return this->f_ownernumber;

		}

		/**
                *getter function to get the file size
                **/

		int Filemanager :: get_filesize()
		{
			return this->f_size;
		}

		/**
                *getter function to get file block size.
                **/

		int Filemanager :: get_blksize()
		{

			return this->blk_size;
		}


		struct stat Filemanager :: getBuffer()
		{

		return this->buffer;
		}


		/**
                *getter function to get children in direcotory.
                **/

		vector<Filemanager> Filemanager :: getChildren()
		{

			return this->children;

		}

		/**
                *getter function to get acces  time
                **/

		time_t Filemanager :: getAccesstime()
		{
			return this->file_accesstime;

		}

		/**
                *getter function to get last modification time
                **/

		time_t Filemanager :: getmodtime()
                {

			return this->file_modificationtime;;

                }

		/**
                *getter function to get status change time
                **/


		time_t Filemanager :: getstatuschange()
                {

                        return this->file_statuschange;;

                }


		/**
		*getter function to get error number
		**/

		int Filemanager :: geterr_num()
		{
			return this->error_num;

		}

		/**
		* this function takes in an error numbr as paramter
		* returns corresponding error message
		**/

		string Filemanager :: geterr_message(int errnum)
		{

			return strerror(errnum);
		}

		/**
		*destructor function, destroys and frees up any resources
		* attached to the object the destructor was called on
		**/

		Filemanager ::~Filemanager()
		{


		}


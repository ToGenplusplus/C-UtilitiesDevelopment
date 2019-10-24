
#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <fstream>
#include <vector>



class Filemanager{

	private:
		int f_size, f_ownernumber,grp_idnumber, blk_size, error_num = 0;
                std :: string file_type,f_ownerstring, grp_idstring;
                std :: string f_name, f_permissions;
		mode_t f_mode;
                std :: vector<Filemanager> children;
		struct stat buffer;
                time_t file_accesstime, file_modificationtime, file_statuschange;

	public:
		Filemanager (char *filename);

		~Filemanager();

		int dump_file(std :: ostream * contents_destination);

		int rename_file(char * newname);

		int remove_file();

		int compare_files(Filemanager newobject);

		int Expand();

		std::string  getFileName();

		int setFileName(char * file_name);

		std :: string getfile_type();

		mode_t getFilemode();

		std :: string get_ownerstring();

		std :: string get_grp_id_string();

		void getsetfile_type(mode_t name,struct stat buf);

		void printPermissions(mode_t name,struct stat buf);

		void reset_attributes();

		int get_grp_id_number();

		int get_ownernumber();

		int get_filesize();

		int get_blksize();

		struct stat getBuffer();

		std :: vector<Filemanager> getChildren();

		time_t getAccesstime();

		time_t getmodtime();

		time_t getstatuschange();

		int geterr_num();

		std :: string geterr_message(int errnum);


	};
#endif



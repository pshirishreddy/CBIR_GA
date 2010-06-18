/*
 * System.cpp
 *
 *  Created on: 26-May-2010
 *      Author: shirish
 */

#include "System.h"
#include "headers.h"

using namespace std;

System::System() {
}


System::~System() {
}

/**
 * Read the files in the directory DB and store the file names in a LIST
 * @params: String containing location to the directory
 */
list<string> System::file_names(char dir[])
{
	list<string> file_n;
	struct dirent *dp;
	DIR *dfd = opendir(dir);
	if(dfd != NULL) {
		while((dp = readdir(dfd)) != NULL) {
			if(strcmp(dp->d_name,"."))
				if(strcmp(dp->d_name,".."))
				file_n.push_back(dp->d_name);
		}
		closedir(dfd);
	}
	return file_n;
}

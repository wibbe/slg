
#include "slg/File.hpp"
#include <stdio.h>
#include <sys/stat.h>

namespace slg {

  bool fileContent(const char * filename, char ** data, int & length)
  {
	  FILE * file = fopen(filename, "r");
	  
	  if (!file)
	  	return false;
	  
	  fseek(file, 0, SEEK_END);
	  length = ftell(file);
	  rewind(file);

    *data = new char[length];
	  
	  fread(*data, sizeof(char), length, file);
	  fclose(file);
	  
	  return true;
  }

  time_t fileModifiedTime(const char * filename)
  {
    struct stat statInfo;
    stat(filename, &statInfo);
    return statInfo.st_mtime;
  }

}


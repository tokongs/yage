#include <Util.h>
 
std::string getCurrentWorkingDir( void ) {
  char buff[FILENAME_MAX];
  getCurrentDir( buff, FILENAME_MAX );
  std::string current_working_dir(buff);
  return current_working_dir;
}
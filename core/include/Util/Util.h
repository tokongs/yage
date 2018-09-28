#include <config.h>
#ifdef WINDOWS
#include <direct.h>
#define getCurrentDir _getcwd
#else
#include <unistd.h>
#define getCurrentDir getcwd
#endif
#include<iostream>
 
std::string getCurrentWorkingDir( void );
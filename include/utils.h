#ifndef _UTILS_H
#define _UTILS_H

#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define CUS_BUFSIZ 512
#define MAXDIRNAME 128
#define MAXFILENAME MAXDIRNAME * 2
#define MAXFILES 100

void catf(const char* filename);
int listdir(const char* dirname, char filenames[MAXFILES][MAXFILENAME]);

#endif
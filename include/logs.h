#ifndef _LOGS_H
#define _LOGS_H

#include <stdbool.h>

void init_logs();
void end_logs();
void logMsg(const char*, ...);

#endif
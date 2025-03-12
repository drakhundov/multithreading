#include "logs.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdlib.h>

const char* logfn = ".log";
int logfd;

void init_logs() {
	logfd = open(logfn, O_WRONLY | O_CREAT, 0644);
	if (logfd == -1) {
		perror("Failed to open log file.");
		exit(1);
	}
}

void end_logs() {
	close(logfd);
}

void logMsg(const char* fmt, ...) {
	va_list args;
	va_start(args, fmt);
	char msg[1024];
	vsnprintf(msg, sizeof(msg), fmt, args);
	va_end(args);
	write(logfd, msg, strlen(msg));
	fsync(logfd);  // Ensure the log message is written to disk.
}

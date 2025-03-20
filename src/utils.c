#include "utils.h"

#include "logs.h"

void catf(const char* filename) {
	logMsg("Call to `catf`. Opening file \"%s\"\n", filename);
	int fd = open(filename, O_RDONLY);
	if (fd == -1) {
		perror("File open failed.");
		exit(1);
	}
	char buffer[CUS_BUFSIZ];
	ssize_t bytes_read;
	while ((bytes_read = read(fd, buffer, BUFSIZ)) > 0) {
		write(STDOUT_FILENO, buffer, bytes_read);
	}
	close(fd);
}

int listdir(const char* dirname, char filenames[MAXFILES][MAXFILENAME]) {
	logMsg("Call to `listdir`.\n");
	int counter;
	struct dirent* entry;
	DIR* dir = opendir(dirname);
	if (dir == NULL) {
		fprintf(stderr, "Unable to open directory: %s.", dirname);
		return 1;
	}
	counter = 0;
	while ((entry = readdir(dir)) != NULL) {
		if (entry->d_name[0] == '.') {
			// Skip the current and parent directories.
			continue;
		}
		sprintf(filenames[counter++], "%s/%s", dirname, entry->d_name);
	}
	closedir(dir);
	return counter;
}
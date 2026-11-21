#include <sys/stat.h>

#include "validpath.h"

struct stat sb;

bool isValidPath(char *path) {

	if (stat(path, &sb) == 0 && (S_ISDIR(sb.st_mode) || S_ISREG(sb.st_mode) )) {
		return true;
	} else {
		return false;
	}

}

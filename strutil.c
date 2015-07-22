#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "str.h"
#include "util.h"

static int v4l2_util_translate_openmode (const enum V4L2UtilOpenMode mode)
{
	int retval = 0;
	switch (mode)
	{
		case V4L2UtilOpenReadOnly:
			retval = O_RDONLY;
			break;
		case V4L2UtilOpenWriteOnly:
			retval = O_WRONLY;
			break;
		case V4L2UtilOpenReadWrite:
			retval = O_RDWR;
			break;
		default:
			bug("bad mode in v4l2utilopenmod");
			break;
	}
	return retval;
}

int v4l2_util_open_file (const char *p_filename, const enum V4L2UtilOpenMode mode)
{
	return open (p_filename, v4l2_util_translate_openmode(mode) | O_NONBLOCK);
}




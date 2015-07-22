#ifndef V4L2_STR_H
#define V4L2_STR_H

/* file create/open/close */
enum V4L2UtilOpenMode
{
	V4L2UtilOpenReadOnly = 0,
	V4L2UtilOpenWriteOnly,
	V4L2UtilOpenReadWrite
};

struct mystr
{
	char *PRIVATE_HANDS_p_buf;
	unsigned int PRIVATE_HANDS_len;
	unsigned int PRIVATE_HANDS_alloc_bytes;
};

#define INIT_MYSTR { (void *)0, 0, 0 }


int v4l2_util_open_file(const char *p_filename, const enum V4L2UtilOpenMode)

#endif

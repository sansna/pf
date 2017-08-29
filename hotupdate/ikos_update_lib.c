#include <stdio.h>
#include <dlfcn.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#include <openssl/md5.h>

#include "ikos_update_lib.h"

struct funcname_pointer {
	char *name;
	fvoid *pointer;
};

#define IK_MAX_BUF 256
#define IK_LIB "./b1.so"
#define IK_NEW_DB "./b2.db"
#define IK_NEW_LIB "./b2.so"

/*
 * Each lib should contain a function called ikos_libversion which 
 * returns a float representing a version of current lib.
 * Note that version number lower than current lib will not replace
 * any current lib has. 
 */
#define IKOS_LIBVERSION_FUNC "ikos_libversion"

/* function name - function pointer registration */
#define IK_FUNC_COUNT 2
static struct funcname_pointer
FUNCNAME_POINTER_const[IK_FUNC_COUNT] = {
	{"b", (fvoid*)&f},
	{IKOS_LIBVERSION_FUNC,(fvoid*)&fver},
};

static inline void
ik_update_lib__ (char *dbname, char *libname)
{
	void *new_hdl = NULL;
	int fd = 0;
	int len = 0;
	int i = 0;
	char buf[IK_MAX_BUF], *func_name = NULL;
	char *pbuf;

	fd = open(dbname, O_RDONLY);

	do{
		len = read(fd, &buf, IK_MAX_BUF);
		if (len == 0)
			break;
		while( NULL != (pbuf = strchr((const char*)&buf,'\n')) ) {
			*pbuf = ' ';
		}
		for (func_name = strtok((char*)&buf, " "); 
			 func_name != NULL;
			 func_name = strtok(NULL, " ")) {
			if ((func_name - buf) >= len) {
				break;
			}
			for (i = 0; i < IK_FUNC_COUNT; i ++) {
				if (!strcmp(FUNCNAME_POINTER_const[i].name,func_name)) {
					break;
				}
			}
			if (i == IK_FUNC_COUNT) {
				sprintf((char*)&buf,
						"ik_update_lib: db file corrupted at pos %d.\n",
						i + 1);
				perror((const char*)&buf);
				break;
			}
			new_hdl = dlopen(libname,RTLD_LAZY);
			*FUNCNAME_POINTER_const[i].pointer = dlsym(new_hdl,func_name);
		}
	} while(0);

	close(fd);
}

static inline void
ik_md5_of_file(char *filename, char *out)
{
	MD5_CTX c;
	int fd = 0;
	char buf[512];
	ssize_t bytes;

	MD5_Init(&c);
	fd = open(filename,O_RDONLY);
	bytes = read(fd, buf, 512);
	while (bytes) {
		MD5_Update (&c, buf, bytes);
		bytes = read (fd, buf, 512);
	}
	MD5_Final (out, &c);
	close(fd);
}

static inline void
ik_update_lib (char *dbname, char *libname)
{
	char filename[IK_MAX_BUF];
	char buf[IK_MAX_BUF];
	unsigned char out[MD5_DIGEST_LENGTH];
	int i = 0;
	void *nhdl = NULL;
	ffloat nfver;

	/* Lib version check */
	nhdl = dlopen(libname, RTLD_LAZY);
	nfver = dlsym(nhdl, IKOS_LIBVERSION_FUNC);
	if (nfver() < fver()) {
		dlclose(nhdl);
		return;
	}
	/* Lib version check */
	
	ik_md5_of_file(IK_NEW_LIB, out);
	strcpy(buf, ".");
	for (; i < MD5_DIGEST_LENGTH; i ++) {
		sprintf(&buf[2*i+1], "%02x", out[i]);
	}
	buf[2*i+2] = 0;
	sprintf(filename, IK_NEW_LIB"%s", buf);
	rename(IK_NEW_LIB,filename);
	ik_update_lib__(IK_NEW_DB,filename);
	rename(filename,IK_LIB);
}

int main(void)
{
	void *hdl = NULL;

	hdl = dlopen(IK_LIB,RTLD_LAZY);
	f = dlsym(hdl,"b");
	fver = dlsym(hdl,IKOS_LIBVERSION_FUNC);
	(*f)();

	if (access(IK_NEW_LIB,X_OK) != -1) {
		ik_update_lib(IK_NEW_DB,IK_NEW_LIB);
		(*f)();
		(*fver)();
	}

	return 0;
}

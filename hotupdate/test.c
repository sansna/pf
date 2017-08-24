#include <stdio.h>
#include <dlfcn.h>
#include <unistd.h>

int main(void)
{
	int (*f)(void);
	void *hdl = NULL;
	int i = 0;

	for (;i < 2; i ++) {
		hdl = dlopen("./b1.so",RTLD_LAZY);
		f = dlsym(hdl, "b");
		(*f)();
		dlclose(hdl);

		if (access("./b2.so",X_OK) != -1) {
			rename("./b2.so", "./b1.so");
		}
	}

	return 0;
}

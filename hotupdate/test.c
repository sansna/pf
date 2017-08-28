#include <stdio.h>
#include <dlfcn.h>
#include <unistd.h>

int main(void)
{
	int (*f)(void);
	float (*fver)(void);
	void *hdl = NULL, *hdl2 = NULL;
	int i = 0;
	float version = 0;

	for (;i < 2; i ++) {
		hdl = dlopen("./b1.so",RTLD_LAZY);
		f = dlsym(hdl, "b");
		fver = dlsym(hdl, "libversion");
		(*f)();
		version = (*fver)();
		dlclose(hdl);

		if (access("./b2.so",X_OK) != -1) {
			hdl2 = dlopen("./b2.so",RTLD_LAZY);
			fver = dlsym(hdl2,"libversion");
			if ( version < (*fver)() )
				rename("./b2.so", "./b1.so");
			else 
			{
				remove("./b2.so");
				fprintf(stdout, 
						"./b2.so version is earlier than current version\n");
			}
			dlclose(hdl2);
		}
	}

	return 0;
}

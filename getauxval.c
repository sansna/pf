#include <stdio.h>
#include <sys/auxv.h>

int main()
{
	fprintf(stdout, "AT_BASE: %lx\n", getauxval(AT_BASE));
	fprintf(stdout, "AT_BASE_PLATFORM: %lx\n", getauxval(AT_BASE_PLATFORM));
	fprintf(stdout, "AT_CLKTCK: %lx\n", getauxval(AT_CLKTCK));
	fprintf(stdout, "AT_DCACHEBSIZE: %lx\n", getauxval(AT_DCACHEBSIZE));
	fprintf(stdout, "AT_EGID: %lx\n", getauxval(AT_EGID));
	fprintf(stdout, "AT_ENTRY: %lx\n", getauxval(AT_ENTRY));
	fprintf(stdout, "AT_EUID: %lx\n", getauxval(AT_EUID));
	fprintf(stdout, "AT_EXECFD: %lx\n", getauxval(AT_EXECFD));
	fprintf(stdout, "AT_EXECFN: %lx\n", getauxval(AT_EXECFN));
	fprintf(stdout, "AT_FLAGS: %lx\n", getauxval(AT_FLAGS));
	fprintf(stdout, "AT_FPUCW: %lx\n", getauxval(AT_FPUCW));
	fprintf(stdout, "AT_GID: %lx\n", getauxval(AT_GID));
	fprintf(stdout, "AT_HWCAP: %lx\n", getauxval(AT_HWCAP));
	fprintf(stdout, "AT_HWCAP2: %lx\n", getauxval(AT_HWCAP2));
	fprintf(stdout, "AT_ICACHEBSIZE: %lx\n", getauxval(AT_ICACHEBSIZE));
	fprintf(stdout, "AT_PHDR: %lx\n", getauxval(AT_PHDR));
	fprintf(stdout, "AT_PHENT: %lx\n", getauxval(AT_PHENT));
	fprintf(stdout, "AT_PHNUM: %lx\n", getauxval(AT_PHNUM));
	fprintf(stdout, "AT_PLATFORM: %lx\n", getauxval(AT_PLATFORM));
	fprintf(stdout, "AT_RANDOM: %lx\n", getauxval(AT_RANDOM));
	fprintf(stdout, "AT_SECURE: %lx\n", getauxval(AT_SECURE));
	fprintf(stdout, "AT_SYSINFO: %lx\n", getauxval(AT_SYSINFO));
	fprintf(stdout, "AT_SYSINFO_EHDR: %lx\n", getauxval(AT_SYSINFO_EHDR));
	fprintf(stdout, "AT_UCACHEBSIZE: %lx\n", getauxval(AT_UCACHEBSIZE));
	fprintf(stdout, "AT_UID: %lx\n", getauxval(AT_UID));

	while(1);

	return 0;
}

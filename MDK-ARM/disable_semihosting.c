// This file disables the semi-hosting feature in Keil 6, by stubbing out the funtions the related functions.
// This is done to allow execution of the TouchGFX application without having a debugger connected.
// To enable the semi-hosting functionality, this file should simply be excluded from the project.

#if __ARMCC_VERSION >= 6000000

__asm(".global __use_no_semihosting");

#include <rt_sys.h>
#include <time.h>

FILEHANDLE _sys_open(const char * name, int openmode)
{
    return 0;
}

int _sys_close(FILEHANDLE fh)
{
    return 0; //return success
}

int _sys_write(FILEHANDLE fh, const unsigned char * buf, unsigned len, int mode)
{
    return 0;
}

int _sys_read(FILEHANDLE fh, unsigned char * buf, unsigned len, int mode)
{
     return 0;
}

void _ttywrch(int ch)
{
}

int _sys_istty(FILEHANDLE fh)
{
    return 1; // no interactive device present
}

int _sys_seek(FILEHANDLE fh, long pos)
{
    return -1; // error
}

int _sys_ensure(FILEHANDLE fh)
{
    return 0; // success
}

long _sys_flen(FILEHANDLE fh)
{
    return 0;
}

int _sys_tmpnam(char * name, int sig, unsigned maxlen)
{
    return 0; // fail, not supported
}

void _sys_exit(int returncode)
{
    while(1) {};
}

time_t time(time_t *p)
{
    return 0;
}

#endif

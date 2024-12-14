/*
** Based on code by Groepaz.
** 2012-05-30, Ullrich von Bassewitz
** 2021-02-15, Greg King
** 2024-05-27, Sodiumlightbaby
*/



#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <loci.h>


struct dirent* __fastcall__ readdir (register DIR* dir)
{
    unsigned i;
    char d [sizeof(struct dirent)];
    
    mia_set_ax(dir->fd);
    mia_call_int_errno (MIA_OP_READDIR);

    for (i=0; i < sizeof(struct dirent);i++) {
        d[i] = mia_pop_char ();
    }
    return (struct dirent*)&d;
}

/*
** Ullrich von Bassewitz, 2012-05-30. Based on code by Groepaz.
** Sodiumlightbaby 2024 CUmini version
*/

#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <loci.h>

int __fastcall__ closedir (DIR* dir)
{
    mia_set_ax(dir->fd);
    return mia_call_int_errno (MIA_OP_CLOSEDIR);
}




/*
** Ullrich von Bassewitz, 2012-05-30. Based on code by Groepaz.
** Sodiumlightbaby 2024 LOCI version
*/

#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <loci.h>


int __fastcall__ mount (int drive, register const char* path,register const char* filename)
{
    unsigned i;
    mia_set_ax(drive);
    for (i = strlen(filename); i;) {
        mia_push_char (((char*)filename)[--i]);
    }
    mia_push_char('/');
    for (i = strlen(path); i;) {
        mia_push_char (((char*)path)[--i]);
    }
    return mia_call_int_errno (MIA_OP_MOUNT);
}

int __fastcall__ umount (int drive)
{
    mia_set_ax(drive);
    return mia_call_int_errno (MIA_OP_UMOUNT);
}



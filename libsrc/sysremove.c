#include <loci.h>
#include <errno.h>
#include <string.h>

unsigned char __fastcall__ _sysremove (const char* name)
{
    size_t namelen;
    namelen = strlen (name);
    if (namelen > 255) {
        return _mappederrno (EINVAL);
    }
    while (namelen) {
        mia_push_char (name[--namelen]);
    }
    return mia_call_int_errno (MIA_OP_UNLINK);
}

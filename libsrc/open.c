#include <loci.h>
#include <errno.h>
#include <string.h>

int __cdecl__ open (const char* name, int flags, ...)
{
    size_t namelen = strlen (name);
    if (namelen > 255) {
        return _mappederrno (EINVAL);
    }
    while (namelen) {
        mia_push_char (name[--namelen]);
    }
    mia_set_ax (flags);
    return mia_call_int_errno (MIA_OP_OPEN);
}

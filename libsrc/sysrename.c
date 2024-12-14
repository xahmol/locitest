#include <loci.h>
#include <errno.h>
#include <string.h>

unsigned char __fastcall__ _sysrename (const char* oldpath, const char* newpath)
{
    size_t oldpathlen, newpathlen;
    oldpathlen = strlen (oldpath);
    newpathlen = strlen (newpath);
    if (oldpathlen + newpathlen > 254) {
        return _mappederrno (EINVAL);
    }
    while (oldpathlen) {
        mia_push_char (oldpath[--oldpathlen]);
    }
    mia_push_char (0);
    while (newpathlen) {
        mia_push_char (newpath[--newpathlen]);
    }
    return mia_call_int_errno (MIA_OP_RENAME);
}

#include <loci.h>
#include <errno.h>
#include <sys/utsname.h>

int __fastcall__ _sysuname (struct utsname* buf)
{
    unsigned i;
    int ret;

    ret = mia_call_int_errno (MIA_OP_UNAME);

    for (i=0; i < sizeof(struct utsname);i++) {
        ((char*)buf)[i] = mia_pop_char ();
    }
    return ret;
}
#include <loci.h>

int __fastcall__ write_xstack (const void* buf, unsigned count, int fildes)
{
    unsigned i;
    for (i = count; i;) {
        mia_push_char (((char*)buf)[--i]);
    }
    mia_set_ax (fildes);
    return mia_call_int_errno (MIA_OP_WRITE_XSTACK);
}

#include <loci.h>

int __fastcall__ read_xstack (void* buf, unsigned count, int fildes)
{
    int i, ax;
    mia_push_int (count);
    mia_set_ax (fildes);
    ax = mia_call_int_errno (MIA_OP_READ_XSTACK);
    for (i = 0; i < ax; i++) {
        ((char*)buf)[i] = mia_pop_char ();
    }
    return ax;
}

#include <loci.h>
#include <errno.h>

int __fastcall__ close (int fd)
{
    mia_set_ax (fd);
    return mia_call_int_errno (MIA_OP_CLOSE);
}

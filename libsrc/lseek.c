#include <loci.h>
#include <unistd.h>

off_t __fastcall__ lseek (int fd, off_t offset, int whence)
{
    /* Modified argument order for short stacking offset */
    mia_push_long (offset);
    mia_push_char (whence);
    mia_set_ax (fd);
    return mia_call_long_errno (MIA_OP_LSEEK);
}

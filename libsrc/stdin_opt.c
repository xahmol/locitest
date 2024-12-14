
#include <loci.h>

int __fastcall__ stdin_opt (unsigned long ctrl_bits, unsigned char str_length)
{
    mia_push_long (ctrl_bits);
    mia_set_a (str_length);
    return mia_call_int_errno (MIA_OP_STDIN_OPT);
}

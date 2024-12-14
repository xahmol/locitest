#include <loci.h>

int __fastcall__ codepage (void)
{
    return mia_call_int (MIA_OP_CODEPAGE);
}

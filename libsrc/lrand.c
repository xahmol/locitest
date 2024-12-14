#include <loci.h>

long __fastcall__ lrand (void)
{
    return mia_call_long (MIA_OP_LRAND);
}

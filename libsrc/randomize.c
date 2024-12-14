#include <loci.h>
#include <stdlib.h>

void _randomize (void)
{
    srand (mia_call_int (MIA_OP_LRAND));
}

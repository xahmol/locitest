#include <loci.h>
#include <time.h>

int clock_gettimezone (clockid_t clock_id, struct _timezone* tz)
{
    int ax;
    mia_set_ax (clock_id);
    ax = mia_call_int_errno (MIA_OP_CLOCK_GETTIMEZONE);
    if (ax >= 0) {
        char i;
        for (i = 0; i < sizeof (struct _timezone); i++) {
            ((char*)tz)[i] = mia_pop_char ();
        }
    }
    return ax;
}

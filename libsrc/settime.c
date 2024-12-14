#include <loci.h>
#include <time.h>

int clock_settime (clockid_t clock_id, const struct timespec* tp)
{
    mia_set_ax (clock_id);
    mia_push_long (tp->tv_nsec);
    mia_push_long (tp->tv_sec);
    return mia_call_int_errno (MIA_OP_CLOCK_SETTIME);
}

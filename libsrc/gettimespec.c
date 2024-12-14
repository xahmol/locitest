#include <loci.h>
#include <time.h>

int __clock_gettimespec (struct timespec* ts, unsigned char op)
/* Internal method shared by clock_getres and clock_gettime. */
{
    int ax = mia_call_int_errno (op);
    if (ax >= 0) {
        ts->tv_sec = mia_pop_long ();
        ts->tv_nsec = mia_pop_long ();
    }
    return ax;
}

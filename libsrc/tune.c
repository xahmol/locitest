
#include <loci.h>

int __fastcall__ tune_tmap (unsigned char delay)
{
    mia_set_ax (delay);
    return mia_call_int_errno (MIA_OP_TUNE_TMAP);
}
int __fastcall__ tune_tior (unsigned char delay)
{
    mia_set_ax (delay);
    return mia_call_int_errno (MIA_OP_TUNE_TIOR);
}
int __fastcall__ tune_tiow (unsigned char delay)
{
    mia_set_ax (delay);
    return mia_call_int_errno (MIA_OP_TUNE_TIOW);
}
int __fastcall__ tune_tiod (unsigned char delay)
{
    mia_set_ax (delay);
    return mia_call_int_errno (MIA_OP_TUNE_TIOD);
}
int __fastcall__ tune_tadr (unsigned char delay)
{
    mia_set_ax (delay);
    return mia_call_int_errno (MIA_OP_TUNE_TADR);
}

void __fastcall__ tune_scan_enable (void)
{
    mia_call_void(MIA_OP_TUNE_SCAN);
}
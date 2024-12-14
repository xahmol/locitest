#include "loci.h"

//Tape emulation counter / file seek
long tap_seek(long pos){
    mia_set_axsreg(pos);
    return mia_call_long_errno(MIA_OP_TAP_SEEK);
}

//Tape emulation counter / file seek
long tap_tell(void){
    return mia_call_long(MIA_OP_TAP_TELL);
}

//Read next header from current postion of tap file
long tap_read_header(tap_header_t* header){
    unsigned char i;
    unsigned char * h = (unsigned char*)header;
    long axsreg;
    axsreg = mia_call_long_errno (MIA_OP_TAP_HDR);
    for (i=0; i < sizeof(tap_header_t);i++) {
        h[i] = mia_pop_char ();
    }
    return axsreg;
}    

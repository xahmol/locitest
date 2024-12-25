// LOCI API CC65 library
//
// Based on:
// - LOCI ROM by Sodiumlightbaby, 2024, https://github.com/sodiumlb/loci-rom
// - Picocomputer 6502 by Rumbledethumps, 2023, https://github.com/picocomputer/rp6502
// - cc65 by Ullrich von Bassewitz,  Based on code by Groepaz. https://github.com/cc65/cc65
//
// Apapted and extended by Xander Mol, 2024

#include <loci.h>

int __fastcall__ phi2(void)
// Function to retrieves the PHI2 setting from the LOCI.
// Returns: The 6502 clock speed in kHz. 500 <= x <= 8000
// Errno:   will not fail
{
    return mia_call_int(MIA_OP_PHI2);
}

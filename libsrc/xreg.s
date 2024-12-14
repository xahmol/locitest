;
; 2023, Rumbledethumps
; 2024, Sodiumlightbaby
;
; CC65 will promote variadic char arguments to int. It will not demote longs.
; int __cdecl__ xreg(char device, char channel, unsigned char address, ...);

.export _xreg
.importzp sp
.import addysp, _mia_call_int_errno

.include "loci.inc"

.code

.proc _xreg

    ; save variadic size in X
    tya
    tax

@copy: ; copy stack
    dey
    lda (sp),y
    sta MIA_XSTACK
    tya
    bne @copy

    ; recover variadic size and move sp
    txa
    tay
    jsr addysp

    ; run MIA operation
    lda #MIA_OP_XREG
    jmp _mia_call_int_errno

.endproc

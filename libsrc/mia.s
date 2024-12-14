;
; 2023, Rumbledethumps
; 2024, Sodiumlightbaby
;
; Helpers for building API shims

.include "loci.inc"
.include "errno.inc"
.export _mia_push_long, _mia_push_int
.export _mia_pop_long, _mia_pop_int
.export _mia_set_axsreg, _mia_set_ax
.export _mia_call_int, _mia_call_long
.export _mia_call_int_errno, _mia_call_long_errno
.export _mia_call_void

.importzp sp, sreg
.import incsp1

.code

; void __fastcall__ mia_push_long(unsigned long val);
_mia_push_long:
    ldy sreg+1
    sty MIA_XSTACK
    ldy sreg
    sty MIA_XSTACK
; void __fastcall__ mia_push_int(unsigned int val);
_mia_push_int:
    stx MIA_XSTACK
    sta MIA_XSTACK
    rts

; long __fastcall__ mia_pop_long(void);
_mia_pop_long:
    jsr _mia_pop_int
    ldy MIA_XSTACK
    sty sreg
    ldy MIA_XSTACK
    sty sreg+1
    rts

; int __fastcall__ mia_pop_int(void);
_mia_pop_int:
    lda MIA_XSTACK
    ldx MIA_XSTACK
    rts

; void __fastcall__ mia_set_axsreg(unsigned long axsreg);
_mia_set_axsreg:
    ldy sreg
    sty MIA_SREG
    ldy sreg+1
    sty MIA_SREG+1
; void __fastcall__ mia_set_ax(unsigned int ax);
_mia_set_ax:
    stx MIA_X
    sta MIA_A
    rts

; int __fastcall__ mia_call_int(unsigned char op);
_mia_call_int:
    sta MIA_OP
    jmp MIA_SPIN

; long __fastcall__ mia_call_long(unsigned char op);
_mia_call_long:
    sta MIA_OP
    jsr MIA_SPIN
    ldy MIA_SREG
    sty sreg
    ldy MIA_SREG+1
    sty sreg+1
    rts

; int __fastcall__ mia_call_int_errno(unsigned char op);
_mia_call_int_errno:
    sta MIA_OP
    jsr MIA_SPIN
    ldx MIA_X
    bmi ERROR
    rts

; long __fastcall__ mia_call_long_errno(unsigned char op);
_mia_call_long_errno:
    jsr _mia_call_long
    bmi ERROR
    rts

; void __fastcall__ mia_call_void(unsigned char op);
_mia_call_void:
    sta MIA_OP
    rts

ERROR:
    lda MIA_ERRNO
.ifdef OLD_CC65
    jmp __mappederrno
.else
    jmp ___mappederrno
.endif


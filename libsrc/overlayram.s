        .export         _overlay_memcpy
        .import         popax, memcpy_getparams
        .importzp       ptr1, ptr2, ptr3

        MICRODISCCFG    := $0314

.code

; void* __fastcall__ _overlay_memcpy (void* dest, const void* src, size_t count);
; ----------------------------------------------------------------------
; Get the parameters from stack as follows:
;
;       size            --> ptr3
;       src             --> ptr1
;       dest            --> ptr2
;       First argument (dest) will remain on stack and is returned in a/x!
_overlay_memcpy:
        jsr     memcpy_getparams        ; Get parameters from stack

        ; Enable overlay RAM and disable interrupts
        php                             ; Push processor status
        sei                             ; Disable interrupts
        lda      #%11111101             ; Enable overlay RAM
        sta      MICRODISCCFG           ; Write to register

        ldx     ptr3+1                  ; Get high byte of size
        beq     mct2                    ; Jump if zero

mct1:   .repeat 2                       ; Unroll this a bit to make it faster...
        lda     (ptr1),Y                ; Read a byte
        sta     (ptr2),Y                ; Copy to destination
        iny                             ; Increase loop counter
        .endrepeat
        bne     mct1                    ; End of page?
        inc     ptr1+1                  ; Increase high byte of source
        inc     ptr2+1                  ; Increase high byte of destination        
        dex                             ; Next 256 byte block
        bne     mct1                    ; Repeat if any

mct2:   ldx     ptr3                    ; Get the low byte of count
        beq     mctd                    ; something to copy?

mct3:   lda     (ptr1),Y                ; Read a byte
        sta     (ptr2),Y                ; Copy to destination
        iny                             ; Increase loop counter
        dex                             ; Decrease bytes left counter
        bne     mct3                    ; Loop until done

        ; Disable overlay RAM and enable interrupts
        lda      #%11111111
        sta      MICRODISCCFG
        plp
        rts

mctd:   jmp     popax                   ; Pop ptr and return as result
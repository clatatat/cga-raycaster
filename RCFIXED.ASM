; RCFIXED.ASM - Fixed-point 8.8 arithmetic routines for raycaster
; Assemble: MASM /Mx RCFIXED.ASM;
; /Mx preserves case of PUBLIC/EXTRN symbols (required for C linkage)
;
; Calling convention: C (cdecl) - caller pushes args right-to-left,
; caller cleans stack. Return value in AX.
;
; These replace C equivalents for speed on 8086/8088:
;   fix_mul(a,b) = (short)(((long)a * b) >> 8)
;   fix_div(a,b) = (short)(((long)a << 8) / b)
;
; 8.8 fixed-point: high byte = integer part, low byte = fraction
; Range: -128.0 to +127.996 (0x8000 .. 0x7FFF)

        .MODEL  SMALL, C
        .CODE

        PUBLIC  fix_mul
        PUBLIC  fix_div

;--------------------------------------------------------------
; short fix_mul(short a, short b)
;
; Multiply two 8.8 fixed-point values, return 8.8 result.
; Uses IMUL to get 32-bit signed product in DX:AX, then
; extracts bits 8..23 (the 8.8 portion of the 16.16 product).
;
; Cycle cost (8088): ~150 clocks including call overhead
;--------------------------------------------------------------
fix_mul PROC    NEAR
        push    bp
        mov     bp, sp
        mov     ax, [bp+4]             ; a
        imul    word ptr [bp+6]        ; DX:AX = a * b (signed 32-bit)
        ; Extract bits 8-23: AH has bits 8-15, DL has bits 16-23
        mov     al, ah
        mov     ah, dl
        pop     bp
        ret
fix_mul ENDP

;--------------------------------------------------------------
; short fix_div(short a, short b)
;
; Divide 8.8 by 8.8, return 8.8 result.
; Computes (a << 8) as 32-bit in DX:AX, then IDIV by b.
;
; WARNING: Caller must ensure b != 0 and |a/b| < 128.0
; or a divide overflow interrupt (#DE) will fire.
;
; Cycle cost (8088): ~190 clocks including call overhead
;--------------------------------------------------------------
fix_div PROC    NEAR
        push    bp
        mov     bp, sp
        mov     ax, [bp+4]             ; a (16-bit signed)
        cwd                             ; sign-extend AX into DX:AX
        ; Shift DX:AX left by 8 to get (a << 8) as 32-bit
        ; Before: DX = sign extension, AX = a
        ; After:  DX:AX = a << 8
        mov     dh, dl                  ; DH = old DL (sign byte)
        mov     dl, ah                  ; DL = old AH (high byte of a)
        mov     ah, al                  ; AH = old AL (low byte of a)
        xor     al, al                  ; AL = 0 (shifted in)
        idiv    word ptr [bp+6]         ; AX = (a << 8) / b
        pop     bp
        ret
fix_div ENDP

        END

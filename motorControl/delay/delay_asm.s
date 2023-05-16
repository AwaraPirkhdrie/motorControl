/*
 * delay.inc
 *
 * Author: Mouad
 *
 * Date:	2018-11-27
 */ 


;==============================================================================
; Delay of 1 µs (including RCALL)
;==============================================================================
.global delay_1_micros
delay_1_micros:   /* UPPGIFT: komplettera med ett antal NOP-instruktioner!!! */
	NOP /* 8 NOP + 4 cycles + 4 cycles = 1 µs */
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	RET

;==============================================================================
; Delay of X µs,
;	LDI + RCALL = 4 cycles
;==============================================================================
.global delay_micros
delay_micros:			/* UPPGIFT: komplettera med ett antal NOP-instruktioner!!! */
	DEC R24
	CPI R24, 0			; more loops to do?
	NOP					/* 12 NOP to make this subroutine 16 cycles */
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	BRNE delay_micros;
	RET

;==============================================================================
; Delay of X ms
;	LDI + RCALL = 4 cycles
;==============================================================================
.global delay_ms
delay_ms:
	MOV R18, R24
loop_dms:
	LDI R24, 250
	RCALL delay_micros
	LDI R24, 250
	RCALL delay_micros
	LDI R24, 250
	RCALL delay_micros
	LDI R24, 250
	RCALL delay_micros
	DEC R18
	CPI R18, 0			; more loops to do?
	BRNE loop_dms		;	continue!
	RET

;==============================================================================
; Delay of X ms
;
;==============================================================================
.global delay_s
delay_s:
	MOV R18, R24
	LDI R24, 250
	RCALL delay_ms
	LDI R24, 250
	RCALL delay_ms
	LDI R24, 250
	RCALL delay_ms
	LDI R24, 250
	RCALL delay_ms
	CPI R24,0
	BRNE delay_micros
	RET
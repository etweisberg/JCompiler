	.CODE
	.FALIGN
main
	STR R7, R6, #-2
	STR R5, R6, #-3
	ADD R6, R6, #-3
	ADD R5, R6, #0
	ADD R6, R5, #0
	ADD R6, R6, #3
	LDR R7, R6, #0
	STR R7, R6, #-1
	LDR R5, R6, #-3
	LDR R7, R6, #-2
	RET
	CONST R7, #5
	ADD R6, R6, #-1
	STR R7, R6, #0
	CONST R7, #3
	ADD R6, R6, #-1
	STR R7, R6, #0
	CONST R7, #2
	ADD R6, R6, #-1
	STR R7, R6, #0
	JSR printnum
	ADD R6, R5, #0
	ADD R6, R6, #3
	LDR R7, R6, #0
	STR R7, R6, #-1
	LDR R5, R6, #-3
	LDR R7, R6, #-2
	RET
	JSR endl
	ADD R6, R5, #0
	ADD R6, R6, #3
	LDR R7, R6, #0
	STR R7, R6, #-1
	LDR R5, R6, #-3
	LDR R7, R6, #-2
	RET
	CONST R7, #3
	ADD R6, R6, #-1
	STR R7, R6, #0
	CONST R7, #4
	ADD R6, R6, #-1
	STR R7, R6, #0
	CONST R7, #5
	ADD R6, R6, #-1
	STR R7, R6, #0
	JSR printnum
	ADD R6, R5, #0
	ADD R6, R6, #3
	LDR R7, R6, #0
	STR R7, R6, #-1
	LDR R5, R6, #-3
	LDR R7, R6, #-2
	RET
	JSR endl
	ADD R6, R5, #0
	ADD R6, R6, #3
	LDR R7, R6, #0
	STR R7, R6, #-1
	LDR R5, R6, #-3
	LDR R7, R6, #-2
	RET
	ADD R6, R5, #0
	ADD R6, R6, #3
	LDR R7, R6, #0
	STR R7, R6, #-1
	LDR R5, R6, #-3
	LDR R7, R6, #-2
	RET

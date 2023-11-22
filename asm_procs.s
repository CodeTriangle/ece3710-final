	.global flash_image
	.type flash_image, "function"
	.p2align 4 
flash_image:
	; r0 = pointer to bitmap
	; r1 = length of bitmap
	PUSH	{r4, r5, r6, r7}

	;; SETUP

	; r2 = offset counter
	LDR	r2, =0
	; r4 = mask
	LDR	r4, =0x80
	; r3 = data byte
	LDRB	r3, [r0, +r2]

	; r5 = GPIOB_BASE
	LDR	r5, =GPIOB_BASE

	; r6 = GPIOB_ODR with logic high
	LDR	r6, [r5, #GPIO_ODR]
	ORR	r6, 0x01 ; offset subject to change

	; r7 = GPIOB_ODR with logic low
	LDR	r7, [r5, #GPIO_ODR]
	BIC	r7, 0x01 ; offset subject to change

start_send:
	; start by storing logic high
	STR	r6, [r5, #GPIO_ODR]
	;; LOGIC

	; test masked data
	TST	r3, r4

	; wait until the timing period is over
	; for 32MHz, minimum time to wait is 8 cycles
	NOP
	NOP
	NOP
	NOP

	NOP
	NOP
	NOP
	NOP

	; if byte & mask, send one
	BEQ	send_one
send_zero:
	; should reach here 11 clock cycles after setting logic high
	STR	r7, [r5, #GPIO_ODR]

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
	NOP

	B	finish_send

send_one:
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
	NOP

	; should reach here 24 clock cycles after setting logic high
	STR	r7, [r5, #GPIO_ODR]

finish_send:
	; iterating and getting the next byte take about 10 clock cycles
	; this adds just a little buffer so we don't miss a timing window
	; for the .45us window, we'll have 12cc
	; for the .85us window, we'll have 27cc
	NOP
	NOP

iterate:
	;; LOOPING
	
	; check if we're at the end of the byte
	TEQ	r4, #0x01
	; if not, just go to the next offset
	; if so, go to the next byte
	BNE	next_offset

next_byte:
	; add one to offset
	ADD	r2, #1
	; check if we're done
	TEQ	r2, r1
	; if so go to epilogue
	BEQ	epilogue

	; set byte mask to 0x80
	LDR	r4, =0x80
	; load new data byte
	LDR	r3, [r0, +r2]

	B	start_send

next_offset:
	; go to next least significant byte
	RSL	r4, #1

	; pad until other branch is done
	NOP
	NOP

	B	start_send

epilogue:
	POP	{r4, r5, r6, r7}

	RET

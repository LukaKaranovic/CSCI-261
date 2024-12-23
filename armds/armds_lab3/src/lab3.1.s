/*
 * lab3.1.s
 *
 *  Created on: Nov 19, 2024
 *      Author: Luka Karanovic
 *		Student Id: 665778833
 */

	.data

str:		.space 200
inputMsg:	.string "Enter a string.\n"
outputMsg:  .string "The reversed string is %s.\n"


 	.text
	.type main, %function
	.global main

main:
	stp x29, x30, [sp, #-16]!

	// Get string
	adr x0, inputMsg
	bl printf

	adr x0, str
	bl gets

// load start of string, go through it until null to find the last character
	adr x0, str 	// address of start of string
findEnd:
	ldrb w1, [x0]
	cmp x1, xzr
	beq outLoop

	add x0, x0, #1
	b findEnd

outLoop:
	sub x0, x0, #1 	// address of last bit in string.
	adr x1, str 	// address of first bit in string
reverse:
	cmp x0, x1
	ble end
	// swap two chars
	ldrb w4, [x1]
	ldrb w5, [x0]

	strb w4, [x0]
	strb w5, [x1]

	add x1, x1, #1
	sub x0, x0, #1

	b reverse

end:
	adr x0, outputMsg
	adr x1, str
	bl printf

	ldp x29, x30, [sp], #16
	mov x0, 0
	ret

	.size main, (.-main)

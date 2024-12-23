/*
 * lab5.s
 *
 *  Created on: Nov 28, 2024
 *      Author: Luka Karanovic
 *		Student Id: 665778833
 *
 *  ARM program that calculates the power of a base x raised to an exponent n (x^n), using recursion.
 */

	.data
x:			.word 0
n:			.word 0
printX:		.string "Enter a base number x.\n"
printN:		.string "Enter a non-negative exponent number n.\n"
outputMsg:	.string "%d to the power of %d is %d.\n"
scanFmt:	.string "%d"

	.text
	.type main, %function
	.global main

main:
	stp x29, x30, [sp, #-16]!

	adr x0, printX
	bl printf
	adr x0, scanFmt
	adr x1, x
	bl scanf

	adr x0, printN
	bl printf
	adr x0, scanFmt
	adr x1, n
	bl scanf

	ldr w0, x
	ldr w1, n
	bl power

	mov w3, w0
	adr x0, outputMsg
	ldr w1, x
	ldr w2, n
	bl printf

	ldp x29, x30, [sp], #16
	mov x0, #0
	ret

power:
	stp x29, x30, [sp, #-16]!
	cmp w1, #0 	// if n = 0, return 1
	beq end

	sub sp, sp, #16  // push on stack
	sub w1, w1, #1   // n = n-1
	bl power

	// recursive case
	ldr w1, x
	smull x0, w0, w1
	add sp, sp, #16  // pop the stack
	b tend

// only for base case we want to return 1
end:
		mov w0, #1

tend:	ldp x29, x30, [sp], #16
		ret

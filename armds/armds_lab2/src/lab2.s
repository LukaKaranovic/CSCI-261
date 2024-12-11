/*
 * lab2.s
 *
 *  Created on: Nov 5, 2024
 *      Author: Luka Karanovic
 *		Student Id: 665778833
 */
// To determine whether the roots of a given quadratic equation ax^2 + bx + c = 0 are real or complex based on the discriminant D = b^2 − 4ac.

// If D < 0, then the roots are complex.
// If D >= 0, then the roots are real.

			.data
a:			.word 0
b:			.word 0
c:			.word 0
D:			.word 0
inputMsg:	.string "Enter a number.\n"
scanFmt:	.string "%d"
complex: 	.string "Roots are complex."
real: 		.string "Roots are NOT complex."




	.text
	.type main, %function
	.global main

main:
	stp x29, x30, [sp, #-16]!

	// Input a
	adr x0, inputMsg
	bl printf

	adr x0, scanFmt
	adr x1, a
	bl scanf


	// Input b
	adr x0, inputMsg
	bl printf

	adr x0, scanFmt
	adr x1, b
	bl scanf


	// Input c
	adr x0, inputMsg
	bl printf

	adr x0, scanFmt
	adr x1, c
	bl scanf


	ldr w0, a
	ldr w1, b
	ldr w2, c

	// Calculate D = b^2 - 4ac
	ldr w3, D
	mul w1, w1, w1 // b = b * b
	mov w4, #4
	mul w0, w4, w0 // a = 4 * a
	mul w0, w0, w2 // a = 4a * c
	sub w3, w1, w0 // D = b^2 - 4ac

	// Check if D >= 0 or not
	cmp w3, wzr
	blt comp // if not, print complex string

	// Print not complex string
	adr x0, real
	bl printf
	b end

comp:
	adr x0, complex
	bl printf

// Ends the program
end:
	ldp x29, x30, [sp], #16
	mov x0, 0
	ret

	.size main, (.-main)

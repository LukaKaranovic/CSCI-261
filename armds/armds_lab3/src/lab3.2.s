///*
// * lab3.2.s
// *
// *  Created on: Nov 19, 2024
// *      Author: Luka Karanovic
// *		Student Id: 665778833
// *
// *  Writes a multiplication table of base number a from 1 to n.
// */
//
//	.data
//a:			.word 0
//n:			.word 0
//inputA:		.string "Enter a base number for your table.\n"
//inputN:		.string "Enter the number you want your multiplication table up to.\n"
//scanFmt:	.string "%d"
//outputMsg:	.string "%d X %d = %d\n"
//
//
// 	.text
//	.type main, %function
//	.global main
//
//main:
//	stp x29, x30, [sp, #-16]!
//
//
//	// Input a
//	adr x0, inputA
//	bl printf
//
//	adr x0, scanFmt
//	adr x1, a
//	bl scanf
//
//
////	// Input n (this was so it would multiply to a user input and not 10
////	adr x0, inputN
////	bl printf
////
////	adr x0, scanFmt
////	adr x1, n
////	bl scanf
//
//	mov w18, #1 	// int i = 1
//	// ldr w19, n 	// int n
//	mov w19, #10
//	ldr w20, a  	// int a
//
//loop:
//	cmp w19, w18
//	blt end
//	adr x0, outputMsg
//	mov w1, w20
//	mov w2, w18
//	mul w3, w1, w2
//	bl printf
//	add w18, w18, #1
//	b loop
//
//end:
//
//	ldp x29, x30, [sp], #16
//	mov x0, 0
//	ret
//
//	.size main, (.-main)

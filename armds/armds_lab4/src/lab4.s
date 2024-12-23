/*
 * lab4.s
 *
 *  Created on: Nov 28, 2024
 *      Author: Luka Karanovic
 *		Student Id: 665778833
 *
 *  Determines the day of the week for a given date using an algorithm published by Michael Keith and Tom Craver in 1990.
 */

	.data
day:		.word 0
month:		.word 0
year:		.word 0
weekday:	.word 0
t:			.word 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4
printDay:	.string "Enter a day.\n"
printMonth:	.string "Enter a month.\n"
printYear:	.string "Enter a year.\n"
scanFmt:	.string "%d"
outputMsg:	.string "Weekday is %d.\n"


	.text
	.type main, %function
	.global main

main:
	stp x29, x30, [sp, #-16]!

	// I wanted to user input the date rather than predefine it.
	adr x0, printDay
	bl printf
	adr x0, scanFmt
	adr x1, day
	bl scanf

	adr x0, printMonth
	bl printf
	adr x0, scanFmt
	adr x1, month
	bl scanf

	adr x0, printYear
	bl printf
	adr x0, scanFmt
	adr x1, year
	bl scanf

	ldr w0, year
	ldr w1, month
	ldr w2, day
	bl dayOfWeek

	mov w1, w0
	adr x0, outputMsg
	bl printf

	ldp x29, x30, [sp], #16
	mov x0, #0
	ret

dayOfWeek:
	stp x29, x30, [sp, #-16]!
	cmp w1, #3 		// m < 3
	bge return
	sub w0, w0, #1 	// year - 1

return:
	mov w3, w0 		// x3 is result, has y
	mov w5, #4
	udiv w6, w0, w5
	add w3, w3, w6  // y + y/4

	mov w5, #100
	udiv w6, w0, w5
	sub w3, w3, w6  // y + y/4 - y/100

	mov w5, #400
	udiv w6, w0, w5
	add w3, w3, w6  // y + y/4 - y/100 + y/400

	sub w1, w1, #1 	// m-1

	adr x4, t
	ldr w6, [x4, w1, uxtw #2] // t[m-1]
	add w3, w3, w6  // y + y/4 - y/100 + y/400 + t[m-1]

	add w3, w3, w2  // y + y/4 - y/100 + y/400 + t[m-1] + d

modulo:
	cmp w3, #7
	blt end
	sub w3, w3, #7

	b modulo


end:
	mov w0, w3  // Weekday in r0

	ldp x29, x30, [sp], #16
	ret




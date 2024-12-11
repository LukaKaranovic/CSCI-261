/*
 * lab1.s
 *
 *  Created on: Nov 5, 2024
 *      Author: Luka Karanovic
 		Student Id: 665778833
 		//Correspinding C code
 		int x = 9;
 		int y = 3;
 		int z = 0;

 		int main(){
 		z = x - y;
 		return 0;
 		}
 */
// To subtract two global varibales (x and y) with initail values 9 and 3 and store the result in variable z

	.data
x:	.word 9
y:	.word 3
z:	.word 0

	.text
	.type main, %function
	.global main

main:
	stp x29, x30, [sp, #-16]!
	ldr w2, x
	ldr w3, y
	sub w2, w2, w3
	adr x0, z
	str w2, [x0]

	ldp x29, x30, [sp], #16
	mov x0, 0
	ret

	.size main, (.-main)


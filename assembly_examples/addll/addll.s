	.text
	.syntax unified
	.thumb
	.global	addll	
	.type	addll, %function
addll:
	adds	r0,r2
	adcs    r1,r3
	bx	lr

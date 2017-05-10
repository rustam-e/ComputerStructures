	.text
	.syntax unified
	.thumb
	.global	addshift	
	.type	addshift, %function
addshift:
	adds	r0, r0, r1, lsl #2
	bx	lr

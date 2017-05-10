	.text
	.syntax unified
	.thumb
	.global	inc	
	.type	inc, %function
inc:
	add	r0,r0,#1
	bx	lr

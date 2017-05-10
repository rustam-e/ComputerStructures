	.text
	.syntax unified
	.thumb
	.global	plus3	
	.type	plus3, %function
plus3:
	adds	r0,r0,#3
	bx	lr

	.global add3op
	.type   add3op, %function
add3op:	adds r0, r1, r2
	bx  lr

	.global add3opnoflag
	.type   add3opnoflag, %function
add3opnoflag:
	add r0, r1, r2
	bx  lr
	

	.global add2op
	.type   add2op, %function
add2op:	adds r0, r1
	bx  lr
	
	.global sub3op
	.type   sub3op, %function
sub3op:	subs r0, r1, r2
	bx  lr
	
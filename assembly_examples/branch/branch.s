	.text
	.syntax unified
	.thumb

	b forward
	adds r1, r2, #4
	adds r0, r6, #2
	adds r3, r7, #4
forward:
	subs r1, r2, #4

backward:
	adds r1, r2, #4
	subs r1, r2, #4
	b backward

conditional:
	subs r1, r1, #1
	bne conditional

call:
	bl subroutine
	cmp r1, #5
	it eq
	moveq r1,#0

subroutine:
	/* code for sub */
	mov pc, lr
	.text
	.syntax unified
	.thumb

	add r1, r2
	add r1, #35
	add r1, r2, r3
	add r1, r2, #56

	adds r1, r2
	adds r1, #35
	adds r1, r2, r3
	adds r1, r2, #56
	adds r1, r2, #4

        cmp   r0, #10
	ite   eq
	addeq r1, r2, r3
	addne r1,r2
	
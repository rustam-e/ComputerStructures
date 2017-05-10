	.syntax unified
	.cpu cortex-m3
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 1
	.eabi_attribute 18, 4
	.thumb
	.file	"test.c"
	.text
	.align	2
	.global	foo
	.thumb
	.thumb_func
	.type	foo, %function
foo:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	add	r0, r0, #1
	bx	lr
	.size	foo, .-foo
	.align	2
	.global	bar
	.thumb
	.thumb_func
	.type	bar, %function
bar:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, lr}
	bl	foo
	pop	{r3, pc}
	.size	bar, .-bar
	.ident	"GCC: (Sourcery G++ Lite 2011.03-42) 4.5.2"

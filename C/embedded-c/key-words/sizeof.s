	.file	"sizeof.c"
	.text
	.globl	a
	.data
	.align 4
	.type	a, @object
	.size	a, 4
a:
	.long	10
	.globl	b
	.bss
	.align 4
	.type	b, @object
	.size	b, 4
b:
	.zero	4
	.globl	c
	.align 4
	.type	c, @object
	.size	c, 4
c:
	.zero	4
	.text
	.globl	my_sizeof
	.type	my_sizeof, @function
my_sizeof:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	$4, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	my_sizeof, .-my_sizeof
	.section	.rodata
.LC0:
	.string	"sizeof = %ld \n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movl	$10, -4(%rbp)
	leaq	.LC0(%rip), %rax
	movl	$4, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$4, b(%rip)
	movl	-4(%rbp), %eax
	movl	%eax, %edi
	call	my_sizeof
	movl	%eax, c(%rip)
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (GNU) 15.2.1 20260103"
	.section	.note.GNU-stack,"",@progbits

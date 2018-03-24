# Generated assembly from stack-abuse.c and is further modified
# to skip some instructions after function()
	.file	"stack-abuse.c"
	.text
	.p2align 4,,15
	.globl	function
	.type	function, @function

# This function is modified.
function:
.LFB11:
	.cfi_startproc
	pushq	%rbp
	movq	%rsp, %rbp
# Let %rax denote address of return %rip address, 8 bytes before %rbp, 
# because %rip is 8 bytes long.
	leaq	8(%rbp),%rax
# The value $119 is calculted from: objdump -S -j .text stack-abuse.out.
	addq	$119,(%rax)
	popq 	%rbp
	ret
	.cfi_endproc
.LFE11:
	.size	function, .-function
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%d\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB12:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
# This call step is also added, because the gcc -O2 -S stack-abuse.c step
# removes calling of function.
	call 	function
# %rip in function points the next instruction in assembly.
	movl	$1, %esi
	movl	$.LC0, %edi
	xorl	%eax, %eax
	call	printf
	movl	$1, %esi
	movl	$.LC0, %edi
	xorl	%eax, %eax
	call	printf
	movl	$1, %esi
	movl	$.LC0, %edi
	xorl	%eax, %eax
	call	printf
	movl	$1, %esi
	movl	$.LC0, %edi
	xorl	%eax, %eax
	call	printf
	movl	$1, %esi
	movl	$.LC0, %edi
	xorl	%eax, %eax
	call	printf
	movl	$1, %esi
	movl	$.LC0, %edi
	xorl	%eax, %eax
	call	printf
	movl	$1, %esi
	movl	$.LC0, %edi
	xorl	%eax, %eax
	call	printf
# %rip is modified in function to be here.
	movl	$1, %esi
	movl	$.LC0, %edi
	xorl	%eax, %eax
	call	printf
	xorl	%eax, %eax
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	ret
# The following is used to enlarge the target object file by 1M.
# And fill the enlarged space with 1, default 0.
	.org 1048576, 1
	.cfi_endproc
.LFE12:
	.size	main, .-main
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-16)"
	.section	.note.GNU-stack,"",@progbits

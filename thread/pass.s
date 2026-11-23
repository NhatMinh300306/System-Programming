	.file	"pass_arg.c"
	.intel_syntax noprefix
	.text
	.globl	primes
	.data
	.align 32
	.type	primes, @object
	.size	primes, 40
primes:
	.long	2
	.long	3
	.long	5
	.long	7
	.long	11
	.long	13
	.long	17
	.long	19
	.long	23
	.long	29
	.section	.rodata
.LC0:
	.string	"%d "
	.text
	.globl	routine
	.type	routine, @function
routine:
.LFB6:
	.cfi_startproc
	endbr64
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR -24[rbp], rdi
	mov	rax, QWORD PTR -24[rbp]
	mov	eax, DWORD PTR [rax]
	mov	DWORD PTR -4[rbp], eax
	mov	eax, DWORD PTR -4[rbp]
	cdqe
	lea	rdx, 0[0+rax*4]
	lea	rax, primes[rip]
	mov	eax, DWORD PTR [rdx+rax]
	lea	rdx, .LC0[rip]
	mov	esi, eax
	mov	rdi, rdx
	mov	eax, 0
	call	printf@PLT
	mov	rax, QWORD PTR -24[rbp]
	mov	rdi, rax
	call	free@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	routine, .-routine
	.section	.rodata
.LC1:
	.string	"Failed to create thread"
.LC2:
	.string	"Failed to join thread"
	.text
	.globl	main
	.type	main, @function
main:
.LFB7:
	.cfi_startproc
	endbr64
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	add	rsp, -128
	mov	DWORD PTR -116[rbp], edi
	mov	QWORD PTR -128[rbp], rsi
	mov	rax, QWORD PTR fs:40
	mov	QWORD PTR -8[rbp], rax
	xor	eax, eax
	mov	DWORD PTR -108[rbp], 0
	jmp	.L3
.L5:
	mov	edi, 4
	call	malloc@PLT
	mov	QWORD PTR -104[rbp], rax
	mov	rax, QWORD PTR -104[rbp]
	mov	edx, DWORD PTR -108[rbp]
	mov	DWORD PTR [rax], edx
	lea	rax, -96[rbp]
	mov	edx, DWORD PTR -108[rbp]
	movsxd	rdx, edx
	sal	rdx, 3
	lea	rdi, [rax+rdx]
	mov	rax, QWORD PTR -104[rbp]
	lea	rdx, routine[rip]
	mov	rcx, rax
	mov	esi, 0
	call	pthread_create@PLT
	test	eax, eax
	je	.L4
	lea	rax, .LC1[rip]
	mov	rdi, rax
	call	perror@PLT
.L4:
	add	DWORD PTR -108[rbp], 1
.L3:
	cmp	DWORD PTR -108[rbp], 9
	jle	.L5
	mov	DWORD PTR -108[rbp], 0
	jmp	.L6
.L8:
	mov	eax, DWORD PTR -108[rbp]
	cdqe
	mov	rax, QWORD PTR -96[rbp+rax*8]
	mov	esi, 0
	mov	rdi, rax
	call	pthread_join@PLT
	test	eax, eax
	je	.L7
	lea	rax, .LC2[rip]
	mov	rdi, rax
	call	perror@PLT
.L7:
	add	DWORD PTR -108[rbp], 1
.L6:
	cmp	DWORD PTR -108[rbp], 9
	jle	.L8
	mov	eax, 0
	mov	rdx, QWORD PTR -8[rbp]
	sub	rdx, QWORD PTR fs:40
	je	.L10
	call	__stack_chk_fail@PLT
.L10:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 15.2.0-16ubuntu1) 15.2.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:

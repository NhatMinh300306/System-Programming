	.file	"race_condition.c"
	.intel_syntax noprefix
	.text
	.globl	mails
	.bss
	.align 4
	.type	mails, @object
	.size	mails, 4
mails:
	.zero	4
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
	mov	QWORD PTR -24[rbp], rdi
	mov	DWORD PTR -4[rbp], 0
	jmp	.L2
.L3:
	mov	eax, DWORD PTR mails[rip]
	add	eax, 1
	mov	DWORD PTR mails[rip], eax
	add	DWORD PTR -4[rbp], 1
.L2:
	cmp	DWORD PTR -4[rbp], 99999
	jle	.L3
	nop
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	routine, .-routine
	.section	.rodata
.LC0:
	.string	"Number of mails: %d\n"
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
	sub	rsp, 48
	mov	DWORD PTR -36[rbp], edi
	mov	QWORD PTR -48[rbp], rsi
	mov	rax, QWORD PTR fs:40
	mov	QWORD PTR -8[rbp], rax
	xor	eax, eax
	lea	rdx, routine[rip]
	lea	rax, -24[rbp]
	mov	ecx, 0
	mov	esi, 0
	mov	rdi, rax
	call	pthread_create@PLT
	test	eax, eax
	je	.L5
	mov	eax, 1
	jmp	.L10
.L5:
	lea	rdx, routine[rip]
	lea	rax, -16[rbp]
	mov	ecx, 0
	mov	esi, 0
	mov	rdi, rax
	call	pthread_create@PLT
	test	eax, eax
	je	.L7
	mov	eax, 2
	jmp	.L10
.L7:
	mov	rax, QWORD PTR -24[rbp]
	mov	esi, 0
	mov	rdi, rax
	call	pthread_join@PLT
	test	eax, eax
	je	.L8
	mov	eax, 3
	jmp	.L10
.L8:
	mov	rax, QWORD PTR -16[rbp]
	mov	esi, 0
	mov	rdi, rax
	call	pthread_join@PLT
	test	eax, eax
	je	.L9
	mov	eax, 4
	jmp	.L10
.L9:
	mov	eax, DWORD PTR mails[rip]
	lea	rdx, .LC0[rip]
	mov	esi, eax
	mov	rdi, rdx
	mov	eax, 0
	call	printf@PLT
	mov	eax, 0
.L10:
	mov	rdx, QWORD PTR -8[rbp]
	sub	rdx, QWORD PTR fs:40
	je	.L11
	call	__stack_chk_fail@PLT
.L11:
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

GLOBAL _syscall
GLOBAL invalid_opcode_test


_syscall:
	push rbp
	mov rbp, rsp
	int 0x80
	mov rsp, rbp
	pop rbp
	ret

invalid_opcode_test:
	push rbp
	mov rbp, rsp
	mov rbx, 0x20
	mov cr6, rax
	mov rsp, rbp
	pop rbp
	ret
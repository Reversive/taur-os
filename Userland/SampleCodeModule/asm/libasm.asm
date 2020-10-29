GLOBAL sys_get_time, puts
GLOBAL invalid_opcode_test



puts:
    push rbp
	mov rbp, rsp
    mov rsi, rdi
    mov rdi, 1
    int 80h
    mov rsp, rbp
	pop rbp
	ret 

sys_get_time:
    push rbp
	mov rbp, rsp
    mov rsi, rdi
    mov rdi, 0
    int 80h
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
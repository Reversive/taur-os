GLOBAL sys_get_time



sys_get_time:
    push rbp
	mov rbp, rsp
    mov rsi, rdi
    mov rdi, 0
    int 80h
    mov rsp, rbp
	pop rbp
	ret 
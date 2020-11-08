GLOBAL cpuVendor
GLOBAL get_time
GLOBAL _hlt
GLOBAL _rsp
GLOBAL _cli
GLOBAL _sti
GLOBAL haltcpu
GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL _fetch_key
GLOBAL save_registers_data

section .text

_fetch_key:
	in al, 64h
	test al, 1
	jz abort
	xor rax, rax
	in al, 60h
	jmp end
abort:
	xor rax, rax
end:
	ret


haltcpu:
	cli
	hlt
	ret

_rsp:
	mov rax, rsp
	ret

_hlt:
	hlt
	jmp _hlt

_cli:
	cli
	ret


_sti:
	sti
	ret

picMasterMask:
	push rbp
    mov rbp, rsp
    mov ax, di
    out	21h,al
    pop rbp
    retn

picSlaveMask:
	push    rbp
    mov     rbp, rsp
    mov     ax, di  ; ax = mascara de 16 bits
    out	0A1h,al
    pop     rbp
    retn
	
cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret


get_time:
    push rbp
 	mov rbp,rsp
    mov rax, 0
    cli
    mov rax, rdi
    out 70h, al
    in al, 71h
    sti
    mov rsp,rbp
    pop rbp
    ret


save_registers_data:
	push rsp ;{"R15","R14","R13","R12","R11","R10"," R9"," R8","RAX","RBX","RCX","RDX","RDI","RSI","RBP","RIP","RSP"}
	push rax
	push rsi
	mov rax, rsp
	add rax, 32 ; apuntamos a la dir de retorno de la func
	mov rsi, [rax]
	push rsi ;rip
	push rbp
	push rdi
	push rdx
	push rcx
	push rbx
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15

	mov rbp,rsp
	mov rbx,17
	mov rcx,rdi
ciclo:
	mov QWORD rdx,[rbp]
	mov QWORD [rcx],rdx
	add rcx,8
	add rbp,8
	dec rbx
	cmp rbx,0
	jne ciclo

    pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rbx
	pop rcx
	pop rdx
	pop rdi
	
	pop rbp
	pop rsi
	pop rsi
	pop rax
	pop rsp
	ret


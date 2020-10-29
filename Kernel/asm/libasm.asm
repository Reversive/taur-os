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


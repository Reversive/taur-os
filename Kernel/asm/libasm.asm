GLOBAL cpuVendor, invalid_opcode_test
GLOBAL get_time

section .text

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

invalid_opcode_test:
	push rbp
	mov rbp, rsp
	mov rbx, 0x20
	mov cr6, rax
	mov rsp, rbp
	pop rbp
	ret


get_time:
  push rbp
  mov rbp,rsp

  mov rax, 0

  mov rax, rdi
  out 70h, al
  in al, 71h

  mov rsp,rbp
  pop rbp
  ret


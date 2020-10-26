GLOBAL cpuVendor, invalidOpcodeTest
GLOBAL get_Time

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

invalidOpcodeTest:
	push rbp
	mov rbp, rsp
	mov rbx, 0x20
	mov cr6, rax
	mov rsp, rbp
	pop rbp
	ret


get_Time:
  push rbp
  mov rbp,rsp

  mov rax, 0

  mov rax, rdi
  out 70h, al
  in al, 71h

  mov rsp,rbp
  pop rbp
  ret

	section .data
msg     db      0x1B,'[H',0x1B,'[2J'
len     equ     $-msg

	section .text
global  _start
_start:
	mov     edx,len
	mov     ecx,msg
	mov     ebx,1
	mov     eax,4
	int     0x80

	mov     ebx,0
	mov     eax,1
	int     0x80

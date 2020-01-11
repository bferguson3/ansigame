PNEMONICS:

mov x,y
cmp x,y
jmp x (or j... x)
call / ret
syscall

conditional jumps:
j..
e, ne, g, ge, l, le, z, nz, o, no, s, ns 
=, !=, >, >=, <, <=, 0, !0, ...
unsigned conditional jumps:
j...
a, ae, b, be

default registers can be pointers
i.e. mov rax, [rbx] ; load $(rbx) into rax

there are SIXTEEN REGISTERS in x86_64

rax
rbx
rcx
rdx

rsi
rdi

rbp
rsp

r8-r15

pointers:
rip - index pointer (eip/ip)
rsp - stack pointer (esp/sp)
rbp - stack base (ebp, bp)

SYSTEM CALL REGISTERS:
sys call id: rax
arguments 1-6: rdi, rsi, rdx, r10, r8, r9

sys_read: 0h
1: #filedescriptor
2: $buffer
3: #count

sys_write: 1h
1: #filedescriptor - 0 stdin, 1 stdout, 2 stderr
2: $buffer
3: count

sys_open: 2h
1: $filename
2: #flags
3: #mode

sys_close: 3h
1: #filedescriptor

sys_exit: 60d
1: #errorcode


HALF-REGS:
eax
ebx
ecx
edx

esi
edi

ebp
esp

r8d-r15d

QUARTER-REGS (16bit):
ax
bx
cx
dx

si
di
bp
sp

r8w-r15w

8BIT REGS:
al
bl
cl
dl
sil
dil
bpl
spl
r8b-r15b

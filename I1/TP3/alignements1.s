.data

x: .byte 0x01
y: .byte 0x02
z: .byte 0x04
.balign 4
a: .word 0x0A0B0C0D
b: .byte 0x08
.balign 2
c: .hword 0xABCD

        .text
        .global main
main:
@ impression du mot x
        LDR r2, LD_x
        LDRB r3, [r2]
        MOV r1, r3
        BL EcrHexa8
@ impression du mot y
        LDR r2, LD_y
        LDRB r3, [r2]
        MOV r1, r3
        BL EcrHexa8
@ impression du mot z
        LDR r2, LD_z
        LDRB r3, [r2]
        MOV r1, r3
        BL EcrHexa8
@ impression du mot a
        LDR r2, LD_a
        LDR r3, [r2]
        MOV r1, r3
        BL EcrHexa32
@ impression du mot b
        LDR r2, LD_b
        LDRB r3, [r2]
        MOV r1, r3
        BL EcrHexa8
@impression du mot c
	LDR r2, LD_c
	LDRH r3, [r2]
	MOV r1, r3
	BL EcrHexa16


fin: B exit

LD_x: .word x
LD_y: .word y
LD_z: .word z
LD_a: .word a
LD_b: .word b
LD_c: .word c

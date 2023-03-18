    .data
cc: @ ne pas modifier cette partie
    .byte 0x42
    .byte 0x4f
    .byte 0x4e
    .byte 0x4a
    .byte 0x4f
    .byte 0x55
    .byte 0x52
    .byte 0x00     @ code de fin de chaine
    @ la suite pourra etr emofifiee
    .word 12
    .word 0x11223344
rv: .asciz "au revoir..."

    .text
    .global main
main:


@ impression de la chaine de caractere d'adresse cc
     LDR r1, LD_cc
     BL EcrChaine

@ impression de la chaine "au revoir..."
     LDR r1, LD_rv
     BL EcrChaine

@ modification de la chaine d'adresse cc
     LDR r2, LD_cc
     LDRB r3, [r2]
     ORR r3, r3, #32
     STRB r3, [r2]
     ADD r2, r2, #1

     LDRB r3, [r2]
     ORR r3, r3, #32
     STRB r3, [r2]
     ADD r2, r2, #1

     LDRB r3, [r2]
     ORR r3, r3, #32
     STRB r3, [r2]
     ADD r2, r2, #1

     LDRB r3, [r2]
     ORR r3, r3, #32
     STRB r3, [r2]
     ADD r2, r2, #1

     LDRB r3, [r2]
     ORR r3, r3, #32
     STRB r3, [r2]
     ADD r2, r2, #1

     LDRB r3, [r2]
     ORR r3, r3, #32
     STRB r3, [r2]
     ADD r2, r2, #1

     LDRB r3, [r2]
     ORR r3, r3, #32
     STRB r3, [r2]
     ADD r2, r2, #1

@ impression de la chaine cc modifiee
     LDR r1, LD_cc
     BL EcrChaine

fin: B exit  @ terminaison immédiate du processus (plus tard on saura faire mieux)

LD_cc: .word cc
LD_rv: .word rv

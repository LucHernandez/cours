  GNU nano 5.4                                                                              ecrmem.s *                                                                                          .data
DW:    .word  0
DH:    .hword 0
DB:    .byte 0

    .text
    .global main
main:
      LDR r0, LD_DW
      LDR r1, [r0]
      BL EcrHexa32
      BL EcrZdecimal32

      MOV r4, #-10
      LDR r5, LD_DW
      STR r4, [r5]

      LDR r0, LD_DW
      LDR r1, [r0]
      BL EcrHexa32
      BL EcrZdecimal32

      LDR r0, LD_DH
      LDR r1, [r0]
      BL EcrHexa16
      BL EcrZdecimal16

      LDR r5, LD_DH
      STR r4, [r5]

      LDR r0, LD_DH
      LDR r1, [r0]
      BL EcrHexa16
      BL EcrZdecimal16


      LDR r0, LD_DB
      LDR r1, [r0]
      BL EcrHexa8
      BL EcrZdecimal8

      LDR r5, LD_DB
      STR r4, [r5]

      LDR r0, LD_DB
      LDR r1, [r0]
      BL EcrHexa8
      BL EcrZdecimal8





fin:  B exit  @ terminaison immédiate du processus (plus tard on saura faire mieux)

LD_DW:   .word DW
LD_DH:   .word DH
LD_DB:   .word DB
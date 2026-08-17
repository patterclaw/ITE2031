.data
flag: .word 0

.text
main:
    li $t0, 1
    li $t1, 2
    slt $t2, $t0, $t1
    beq $t2, $zero, move
    sw $t2, flag($gp)
move:
    nop
    li $v0, 10
    syscall

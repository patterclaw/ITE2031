.data


.text
main:
    j jump
    addi $t0, $zero, 1
jump:
    addi $t0, $zero, 2
    addi $t1, $t0, -2
    li $v0, 10
    syscall





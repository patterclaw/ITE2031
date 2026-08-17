.data


.text
main:
	lw $t0, 3
    lw $t1, 6
    beq $t0, $t1, equal
    addi $t2, $zero, 1
equal:
    addi $t2, $zero, 2
    li $v0, 10
	syscall

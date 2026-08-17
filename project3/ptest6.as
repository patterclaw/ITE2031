.data
value1: .word 1
value2: .word 0

.text
main:
	lw $t0, value1($gp)
	add $t1, $t0, $t0
	sw $t1, value2($gp)
	addi $v0, $zero, 10
	syscall

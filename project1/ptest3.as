.data
value1: .word 1

.text
main:
	lw $t0, value1($gp)
	add $t1, $t0, $t0
	addi $v0, $zero, 10
	syscall

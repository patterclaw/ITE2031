.data
value1: .word 1
value2: .word 0

.text
main: 
	lw $t0, value1($gp)
	sw $t0, value2($gp)
	addi $v0, $zero, 10
	syscall


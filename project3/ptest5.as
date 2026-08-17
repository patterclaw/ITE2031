.data
value1: .word 1

.text
main:
	lw $t0, value1($gp)
	beq $t0, $zero, jump
	addi $t1, $zero, 1

jump:
	addi $vo, $zero, 10
	syscall


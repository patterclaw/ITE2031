.text
main:
	addi $t0, $zero, 1
	addi $t1, $zero, 2
	add $t2, $t0, $t1
	beq $t2, $zero, jump
	addi $t3, $zero, 4

jump:
	addi $v0, $zero, 10
	syscall

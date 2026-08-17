.text
main:
	addi $t0, $zero, 1
	addi $t1, $zero, 1
	beq $t0, $t1, target
	addi $t2, $zero, 99

target:
	addi $t3, $zero, 3
	addi $v0, $zero, 10
	syscall

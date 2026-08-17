.data
value1: .word 1
value2: .word 2

.text
main:
	addi $t0, $zero, 1
	addi $t1, $zero, 2
	addi $t2, $zero, 3
	add $t3, $t0, $t1
	add $t4, $t3, $t1
	addi $v0, $zero, 10
	syscall

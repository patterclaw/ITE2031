.data
value1:	.word	1
value2:	.word	2

.text
main:
	lw	$t0, value1($gp)
	lw  $t1, value2($gp)
    addi $t2, $zero, 4
    add $t4, $t0, $t1
	addi $v0, $zero, 10
	syscall

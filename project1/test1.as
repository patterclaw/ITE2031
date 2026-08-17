.data
num1:	.word	1
num2:	.word	2

.text
main:
	lw	$t0, num1($gp)	# load $t1 with 1 (symbolic address)
	lw	$t1, num2($gp)	# load $t2 with 2 (symbolic address)
	add	$t2, $t0, $t1	
	sw $t2, num1($gp)
	li	$v0, 10	# exit(0)
	syscall

    

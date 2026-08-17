.data



.text
main:
    jal func
    li $v0, 10
    syscall


func: 
    nor $t0, $zero, $zero
    jr $ra





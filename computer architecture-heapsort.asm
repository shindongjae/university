.data
	count:		.word 0			# number of elements in integer array
	array: 		.word 0:40		# data buffer for integer array
	input:		.space 64		# buffer for input string
	message1: 	.asciiz "Enter numbers be sorted: "	# output message 1
	message2:	.asciiz "Sorted output: "			# output message 2
	string:		.asciiz " "
	message3:	.asciiz "Sorted numbers::"
	
	
	.text
main:    
	jal		data_input		# call data_input to accept input data
	
	la	$s0, input	#s0 input string
	la	$s1, array	#s1 숫자 저장될 배열, 첫째칸 0
	la	$s2, count	#s2 저장된 숫자수
	
	lw 	$t1,($s2)
	addi 	$t1,$t1,1
	sw	$t1,($s2)
	

	while:
			lb	$t0,0($s0)		#input한글자 읽어서 t0에 저장
			
			beq	$t0,32,space		#스페이스바라면 다음숫자로 넘어가야함.
			beq	$t0,10,enter		#엔터라면 반복문 종료
			
			lw	$t1,($s1)			#s1에서 현재 배열값 읽어옴
	
			mul	$t1,$t1,10			#t1에 10배후에 이번자릿수 더한후에 -48
			add	$t1,$t1,$t0
			addi	$t1,$t1,-48
			
			sw	$t1,($s1)		#그 값을 다시 배열 현재위치에 저장.
	
			addi 	$s0, $s0, 1		#다음 string input			
			j while
	
	
	
	space:
		#현재 인덱스 가져와서
		#인덱스가 1이 되거나 현재인덱스/2보다 지금꺼가 작으면 루프 종료
		
		lw 	$t1,($s2)	#현재 인덱스를 t1에 가져옴
		
		addi 	$s1,$s1,4 #스페이스바 일시 다음 칸으로
		addi 	$s0,$s0,1 #string도 다음걸로
		lw 	$t1,($s2)
		addi 	$t1,$t1,1
		sw	$t1,($s2)

		j while
		
	enter:		#input 입력완료후 heap생성
		j heapsort
		
	
#
# Implement heapify  (프로그램 필요)
#		
heapsort:
		
	lw	$t0,count	#t0 i=n/2-1
	div	$t0,$t0,2
	sub	$t0,$t0,1

	
	loop1:
		lw	$s3,count 	#s3 count
		add	$s4,$zero, $t0	#arr,n,i
		jal heapify	#heapify 에는 arr, $s3, s4가 들어감
				#heapify(arr, n, i);
		
		beq	$t0,0,out1	#i>=0
		addi	$t0,$t0,-1
		j loop1
	out1:
	
	lw	$t0,count
	sub	$t0,$t0,1	#int i=n-1


	
	loop2:	
		la	$s5,array
		mul	$t0,$t0,4
		la	$s6,array($t0)	#swap(&arr[0], &arr[i]);
		div	$t0,$t0,4
		
		j swap
		
		loop2_1:
		
		add	$s3,$zero, $t0
		add	$s4,$zero, $zero
	
		jal heapify	#heapify(arr, i, 0);
		
		sub	$t0,$t0,1
		beq	$t0,0,end2

		j loop2
	end2:

	lw	$s2, count
	addi	$t9,$zero,0
	addi	$t0,$zero,0
	
	la	$a0,message3
	li	$v0,4
	syscall
	
	jal print
										


#																			#
# One by one extraction from heap  (프로그램 필요)
#																			
heapify:		#arr,$s3,$s4 순서로 들어감.
	add	$t3,$zero,$s4	#t3 largest=i
	add	$t4,$zero,$t3
	mul	$t4,$t4,2	
	addi	$t4,$t4,1	#t4 left=2*i+1
	add	$t5,$zero,$t3
	mul	$t5,$t5,2	
	addi	$t5,$t5,2	#t5 right=2*i+2	
	
		
	
	blt	$t4,$s3,and1	#l<n
	j out2
		and1:
		mul	$t4,$t4,4
		lw	$t6,array($t4)	#arr[l]
		div	$t4,$t4,4
		
		mul	$t3,$t3,4
		lw	$t7,array($t3)	#arr[largest]
		div	$t3,$t3,4
		
		blt	$t7,$t6,check1	#&&arr[r] > arr[largest])
		j out2
		
		check1:
			addi	$t3,$t4,0	#largest = l;
			j out2
	out2:
	
	blt	$t5,$s3,and2		#if (r < n
	j out3
		and2:
		mul	$t5,$t5,4
		lw	$t6,array($t5)	#arr[r]
		div	$t5,$t5,4
		
		mul	$t3,$t3,4
		lw	$t7,array($t3)	#arr[largest]
		div	$t3,$t3,4
		
		blt	$t7,$t6,check2	#arr[r] > arr[largest])
		j out3
		
		check2:
			addi	$t3,$t5,0	#largest = r;
			j out3
	out3:
		bne	$t3,$s4,notroot	#if (largest != i)
		jr	$ra
		notroot:
			mul	$s4,$s4,4
			la	$s5,array($s4)
			div	$s4,$s4,4
			
			mul	$t3,$t3,4
			la	$s6,array($t3)	#arr[largest]
			div	$t3,$t3,4	
			
			j swap2		#swap(&arr[i], &arr[largest]);
			loop3_1:
			
			addi	$s4,$t3,0	#heapify(arr, n, largest);
			j heapify
			
			
	
	jr 	$ra

#
#  swap function  (프로그램 필요)
#
	
swap:		 	#swap
	lw   $t8,($s5)
   	lw   $t9,($s6)
  	sw   $t9,($s5)
   	sw   $t8,($s6)
 	     	
	j	loop2_1	

swap2:
	lw   $t8,($s5)
   	lw   $t9,($s6)
  	sw   $t9,($s5)
   	sw   $t8,($s6)
 	     	
	j	loop3_1																												
																																																										
data_input:
		la 	$a0,message1  		# print 
		li 	$v0,4				# "Enter numbers be sorted: "input (e.g.):"
		syscall
		la 	$a0,input			# load input buffer from keyboard         
		li  $a1,64				# max string length = 60  
		li  $v0,8 	    		# read string
		syscall
		jr	$ra



print:		#앞의 원소 4개와 count출력

	beq	$s2,$t9,END
	
	lw	$a0,array($t0)	#배열 원소 출력
	li	$v0, 1
	syscall
	
	la	$a0,string
	li	$v0,4
	syscall
	
	addi	$t9,$t9,1
	addi	$t0,$t0,4
	j print
	
END:	
	li $v0,10
	syscall

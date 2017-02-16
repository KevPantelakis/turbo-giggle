#TP3 INF1600
#1792473 17947465

.text
.global filter

filter:
	#Paramètres
	push %ebp
	mov %esp, %ebp
  mov $0, %eax
	movl 16(%esp),%ebx #height
	movl 12(%esp),%ecx #widht
	movl 8(%esp),%edx

	#Header

	mov $'B', %eax
	mov %eax, g_output_buf				#*g_output_buf = 'B';
	mov $'M', %eax
	mov %eax, g_output_buf+0x01		#*(g_output_buf + 0x01) = 'M';
	mov $0, %eax
	mov %eax, g_output_buf+0x06		#*((uint16_t*)(g_output_buf + 0x06)) = 0;
	mov $0, %eax
	mov %eax, g_output_buf+0x08		#*((uint16_t*)(g_output_buf + 0x08)) = 0;
	mov $54, %eax
	mov %eax, g_output_buf+0x0a		#*((uint32_t*)(g_output_buf + 0x0a)) = 54;
	mov $40, %eax
	mov %eax, g_output_buf+0x0e		#*((uint32_t*)(g_output_buf + 0x0e)) = 40;
	mov %ecx, g_output_buf+0x12	 	#width en 0x12
	mov %ebx, g_output_buf+0x16	 	#height en 0x16
	mov $1, %eax
	mov %eax, g_output_buf+0x1a		#*((uint16_t*)(g_output_buf + 0x1a)) = 1;
	mov $24, %eax
	mov %eax, g_output_buf+0x1c		#*((uint16_t*)(g_output_buf + 0x1c)) = 24;
	mov $0, %eax
	mov %eax, g_output_buf+0x1e		#*((uint32_t*)(g_output_buf + 0x1e)) = 0;
	mov $11811, %eax
	mov %eax, g_output_buf+0x26		#*((uint32_t*)(g_output_buf + 0x26)) = 11811;
	mov $11811, %eax
	mov %eax, g_output_buf+0x2a		#*((uint32_t*)(g_output_buf + 0x2a)) = 11811;
	mov $0, %eax
	mov %eax, g_output_buf+0x2e		#*((uint32_t*)(g_output_buf + 0x2e)) = 0;
	mov $0, %eax
	mov %eax, g_output_buf+0x32 	#*((uint32_t*)(g_output_buf + 0x32)) = 0;
	mov %ecx, %eax
	mul %ebx
	imul $3, %eax, %edi				#uint32_t nbOctets = w * h * 3;
	mov %edi, g_output_buf+0x22		#*((uint32_t*)(g_output_buf + 0x22)) = nbOctets;
	add $54, %edi
	mov %edi, g_output_buf+0x02		#*((uint32_t*)(g_output_buf + 0x02)) = (nbOctets + 54);

	#Filtering
	#Looping
	#La patience du Panda n`a d`égale que la danse du tigre saoul.  ``Léonidas le belge``
	# eax,ebx,edx,esi,edi,ecx

	imul $3,%eax,%eax 					# %eax est le nombre d`octets (boucle sur tous les octets);
    mov %ecx, %edi				# widt	
	mov %ebx,%ecx
	dec %ecx						
	xor %esi,%esi					# %esi est un itterateur	x

	# %eax=nombre doctets
	# %ebx=height /offset
	# %ecx=height-1    itt y
	# %edx=ImageInput
	# %edi=width
	# %esi=0           itt x
	
	movl 8(%esp),%edx
	loopH:
	cmp $0,%ecx
	jl end
	xor %esi,%esi
	loopW:
	cmp %esi,%edi
	jle endloopW

	#code de la boucle
	push %ebx
	push %eax


	xor %eax,%eax
	xor %ebx,%ebx

	imul %ecx,%edi,%eax
	add %esi,%eax
	imul $3,%eax,%eax
	mov %eax,%ebx
	movb 0(%edx,%ebx),%eax 		
	add 1(%edx,%ebx),%eax
	add 2(%edx,%ebx),%eax
	push %ecx
	mov $3,%ecx
	div %ecx
	pop %ecx
	
	lea g_output_buf,%eax
	lea g_output_buf+1,%eax
	lea g_output_buf+2,%eax
	
	pop %eax
	pop %ebx
	#fin du code de la boucle
	inc %esi
	jmp loopW
	endloopW:
	dec %ecx
	jmp loopH
	end:


	# retour
	# mov nbrOctetEcrit, %eax
	ret

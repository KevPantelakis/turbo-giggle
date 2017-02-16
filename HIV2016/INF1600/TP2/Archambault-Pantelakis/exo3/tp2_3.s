.global func_s

func_s:
    mov a, %eax
    mov b, %ebx
    mov c, %ecx
    mov d, %edx
    mov e, %esi
    mov $0, %edi
    jmp for_condition
    for_begin:
        cmp %edi,%esi
        jae if
        cmp %ebx,%ecx
        je if
        jmp else
    if:
        add %ecx,%eax
        add $2,%ebx
        jmp for_end
    else:
        add %edx,%eax
        add $-1,%ecx
    for_end:
        add $1,%edi
    for_condition:
        cmp $10,%edi
        jna for_begin
    mov %eax,a
    ret
    
; dmemset
; fill array with double words

.386
.model flat, c
.stack
.data
.code

dmemset proc _ptr : dword, _val : dword, _size : dword

	mov ebx, dword ptr [_val];
	mov eax, [ebx];

	mov edi, _ptr;
	mov ecx, _size;

	rep stosd;

    mov eax, _ptr;
    ret;

dmemset endp

end
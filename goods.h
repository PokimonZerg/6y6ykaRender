#ifndef _GOODS_H_
#define _GOODS_H_

inline void *dmemset(void *_ptr, void *_val, size_t _size)
{
	__asm
	{
		mov ebx, dword ptr [_val];
		mov eax, [ebx];

		mov edi, _ptr;
		mov ecx, _size;

		rep stosd;
	}

	return _ptr;
}

#endif
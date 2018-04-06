; FUNCIONES de C
	extern malloc
	extern free
	extern fopen
	extern fclose
	extern fprintf
	extern str_copy
	extern str_len

; /** defines bool y puntero **/
	%define NULL 0
	%define TRUE 1
	%define FALSE 0

; structs sizes
	%define STRUCT_STRING_PROC_LIST_SIZE 24
	%define STRUCT_STRING_PROC_KEY_SIZE 12
	%define STRUCT_STRING_PROC_NODE_SIZE 33

; structs offsets
	%define STRUCT_STRING_PROC_LIST_NAME_OFFSET 0
	%define STRUCT_STRING_PROC_LIST_FIRST_OFFSET 8
	%define STRUCT_STRING_PROC_LIST_LAST_OFFSET 16
	
	%define STRUCT_STRING_PROC_KEY_LENGTH_OFFSET 0
	%define STRUCT_STRING_PROC_KEY_VALUE_OFFSET 4
	
	%define STRUCT_STRING_PROC_NODE_NEXT_OFFSET 0
	%define STRUCT_STRING_PROC_NODE_PREVIOUS_OFFSET 8
	%define STRUCT_STRING_PROC_NODE_F_OFFSET 16
	%define STRUCT_STRING_PROC_NODE_G_OFFSET 24
	%define STRUCT_STRING_PROC_NODE_TYPE_OFFSET 32
	
	
section .data


section .text

global string_proc_list_create
string_proc_list_create: ; name(rdi) : void
	push rbp ; a
	mov rbp, rsp

	push rdi ; n/a; guardo name 

	; pido memoria para la list
	mov rdi, STRUCT_STRING_PROC_LIST_SIZE
	sub rsp, 8 ; a
	call malloc
	add rsp, 8 ; n/a
	; list(rax)

	pop rdi ; a; name(rdi)
	
	; guardo el *list en RBX 
	push rbx ; n/a
	mov rbx, rax
	; list(rbx)

	; copio name
	sub rsp, 8 ; a
	call str_copy
	add rsp, 8 ; n/a
	; nameCopy(rax)

	; inicializo struct
	mov [rbx + STRUCT_STRING_PROC_LIST_NAME_OFFSET], rax
	mov qword [rbx + STRUCT_STRING_PROC_LIST_FIRST_OFFSET], NULL
	mov qword [rbx + STRUCT_STRING_PROC_LIST_LAST_OFFSET], NULL
	mov rax, rbx 
	; list(rax)

	pop rbx ; a
	pop rbp ; n/a
	ret

global string_proc_node_create
string_proc_node_create: ; f(rdi), g(rsi), type(dl) : void
	push rbp ; a
	mov rbp, rsp

	push rdi ; n/a; guardo f
	push rsi ; a; guardo g
	push rdx ; n/a; guardo type (rec: tiene basura en parte alta)

	; pido memoria para el node
	mov rdi, STRUCT_STRING_PROC_NODE_SIZE
	sub rsp, 8 ; a
	call malloc
	add rsp, 8 ; n/a
	; node(rax)

	pop rdx ; a; type(dl)
	pop rsi ; n/a; g(rsi)
	pop rdi ; a; f(rdi)

	; inicializo node
	mov qword [rax + STRUCT_STRING_PROC_NODE_NEXT_OFFSET], NULL
	mov qword [rax + STRUCT_STRING_PROC_NODE_PREVIOUS_OFFSET], NULL
	mov [rax + STRUCT_STRING_PROC_NODE_F_OFFSET], rdi
	mov [rax + STRUCT_STRING_PROC_NODE_G_OFFSET], rsi
	mov byte [rax + STRUCT_STRING_PROC_NODE_TYPE_OFFSET], dl
	; node(rax)

	pop rbp ; n/a
	ret

global string_proc_key_create
string_proc_key_create: ; value(rdi) : void
	push rbp ; a 
	mov rbp, rsp

	; copio value
	call str_copy ; strValue(rdi) : char*
	mov rdi, rax
	; valueCopy(rdi)

	; calculo length
	call str_len ; strValue(rdi) : uint32_t
	; length(eax)

	push rdi ; n/a; guardo valueCopy
	push rax ; a; guardo length (rec: parte alta con basura)

	; pido memoria para la key
	mov rdi, STRUCT_STRING_PROC_KEY_SIZE
	call malloc
	; key(rax)

	pop rdi ; n/a; length(edi)
	pop rsi ; a; valueCopy(rsi)

	; inicializo key
	mov dword [rax + STRUCT_STRING_PROC_KEY_LENGTH_OFFSET], edi 
	mov qword [rax + STRUCT_STRING_PROC_KEY_VALUE_OFFSET], rsi
	; key(rax)

	pop rbp ; n/a
	ret

global string_proc_list_destroy
string_proc_list_destroy: ; list(rdi) : void
	push rbp ; a
	mov rbp, rsp

 	push rdi ; n/a; guardo list

	; borro nodos
	mov rdi, [rdi + STRUCT_STRING_PROC_LIST_FIRST_OFFSET] ; nodoActual(rdi)
	.delete_node_cycle:
		cmp rdi, NULL
		jz .delete_name
		push qword [rdi + STRUCT_STRING_PROC_NODE_NEXT_OFFSET] ; a; guardo siguiente de nodoActual
		call string_proc_node_destroy ; node(rdi) : void
		pop rdi ; n/a; nodoActual->siguiente(rdi)
		jmp .delete_node_cycle
	.delete_name:
		pop rsi ; a; list(rsi)
		mov rdi, [rsi + STRUCT_STRING_PROC_LIST_NAME_OFFSET] ; name(rdi)
		push rsi ; n/a; guardo list
		sub rsp, 8 ; a
		call free
		add rsp, 8 ; n/a
		pop rsi ; a; list(rsi)
	.delete_list: 
		mov rdi, rsi ; list(rdi)
		call free ; ptr(rdi) : void
	pop rbp ; n/a
	ret

global string_proc_node_destroy
string_proc_node_destroy: ; node(rdi) : void
	push rbp ; a
	mov rbp, rsp

	call free ; ptr(rdi) : void

	pop rbp
	ret

global string_proc_key_destroy
string_proc_key_destroy: ; key(rdi) : void
	push rbp ; a
	mov rbp, rsp

	push rdi ; n/a; guardo key
	.delete_value:
		mov rdi, [rdi + STRUCT_STRING_PROC_KEY_VALUE_OFFSET] ; value(rdi)
		sub rsp, 8 ; a
		call free ; ptr(rdi) : void
		add rsp, 8 ; n/a
	.delete_key:
		pop rdi ; a ; key(rdi)
		call free ; ptr(rdi) : void
	pop rbp
	ret

global string_proc_list_add_node
string_proc_list_add_node: ; list(rdi), f(rsi), g(rdx), type(cl) 
	push rbp ; a
	mov rbp, rsp

	push rdi ; n/a; guardo list
	push rsi ; a; guardo f
	push rdx ; n/a; guardo g
	push rcx ; a; guardo type (ojo: parte alta basura)

	; creo node
	mov rdi, rsi ; f(rdi)
	mov rsi, rdx ; g(rsi)
	mov rdx, rcx ; type(rdx)
	call string_proc_node_create
	; node(rax)

	pop rcx ; n/a; type(rcx)
	pop rdx ; a; g(rdx)
	pop rsi ; n/a; f(rsi)
	pop rdi ; a; list(rdi)

	cmp qword [rdi + STRUCT_STRING_PROC_LIST_FIRST_OFFSET], NULL
	jz .list_is_empty
	.list_is_not_empty:
		; engancho nuevo nodo a ultimo nodo de la lista
		mov r8, [rdi + STRUCT_STRING_PROC_LIST_LAST_OFFSET] ; guardo ultimo nodo en r8
		mov [r8 + STRUCT_STRING_PROC_NODE_NEXT_OFFSET], rax ; 
		mov [rax + STRUCT_STRING_PROC_NODE_PREVIOUS_OFFSET], r8 ; 

		; seteo nuevo nodo como el ultimo de la lista
		mov [rdi + STRUCT_STRING_PROC_LIST_LAST_OFFSET], rax 
		jmp .finish
	.list_is_empty:
		; apunto list->first,last a node
		mov [rdi + STRUCT_STRING_PROC_LIST_FIRST_OFFSET], rax
		mov [rdi + STRUCT_STRING_PROC_LIST_LAST_OFFSET], rax
	.finish: 
	pop rbp ; n/a
	ret

global string_proc_list_apply
string_proc_list_apply: ; list(rdi), key(esi), bool(dl)
	push rbp ;a 
	mov rbp, rsp

	; guardo regs
	push rbx ; n/a
	push r12 ; a
	push r13 ; n/a
	%define first rbx
	%define function r12
	%define next r13

	; ¿encode o decode?
	cmp dl, 1
	jz .encode
	.decode:
		mov first, STRUCT_STRING_PROC_LIST_LAST_OFFSET
		mov function, STRUCT_STRING_PROC_NODE_G_OFFSET
		mov next, STRUCT_STRING_PROC_NODE_PREVIOUS_OFFSET
		jmp .bring_first
	.encode:
		mov first, STRUCT_STRING_PROC_LIST_FIRST_OFFSET
		mov function, STRUCT_STRING_PROC_NODE_F_OFFSET
		mov next, STRUCT_STRING_PROC_NODE_NEXT_OFFSET
	.bring_first: 
		mov rdx, [rdi + first] ; nodoActual(rdx)
	.cycle:
		; termino si es nulo
		cmp rdx, NULL
		jz .finish

		; ejecuto funcion
		mov rdi, rsi ; key(rdi)
		push rsi ; a ; guardo key
		push rdx ; n/a; guardo nodoActual
		sub rsp, 8 ; a
		call [rdx + function] ; key(rdi) : void
		add rsp, 8 ; n/a
		pop rdx ; nodoActual(rdx)
		pop rsi ; key(esi)
		
		; pongo al nodo siguiente en rdx y repito
		mov rdx, [rdx + next] ; nodoActual->next/prev(rdx)
		jmp .cycle
	.finish:
		; reestablezo regs
		pop r13 ; a
		pop r12 ; n/a
		pop rbx ; a
	pop rbp ; n/a
	ret

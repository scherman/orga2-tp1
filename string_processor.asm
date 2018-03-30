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
	%define STRUCT_STRING_PROC_NODE_SIZE 40

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
string_proc_list_create:
	push rbp
	mov rbp, rsp

	push rdi ; guardo *name

	; pido memoria para la list
	mov rdi, STRUCT_STRING_PROC_LIST_SIZE
	sub rsp, 8 ;
	call malloc
	add rsp, 8 ;
	; obtengo el *list en RAX

	pop rdi ; recupero *name en RDI
	
	; guardo el *list en en RBX 
	push rbx 
	mov rbx, rax

	; copio name
	sub rsp, 8 
	call str_copy
	add rsp, 8 
	; obtengo *name(copy) en RAX

	; inicializo struct (*list en RBX, *name en RAX)
	mov qword [rbx + STRUCT_STRING_PROC_LIST_NAME_OFFSET], rax
	mov qword [rbx + STRUCT_STRING_PROC_LIST_FIRST_OFFSET], NULL
	mov qword [rbx + STRUCT_STRING_PROC_LIST_LAST_OFFSET], NULL

	mov rax, rbx ; guardo *list en RAX

	pop rbx
	pop rbp
	ret

global string_proc_node_create
string_proc_node_create:
	push rbp
	mov rbp, rsp

	push rdi ; guardo f
	push rsi ; guardo g
	push rdx ; guardo type

	; pido memoria para el node
	mov rdi, STRUCT_STRING_PROC_NODE_SIZE
	sub rsp, 8
	call malloc
	add rsp, 8
	; obtengo *node en rax

	pop rdx ; recupero type
	pop rsi ; recupero g
	pop rdi ; recupero f

	; inicializo node
	mov qword [rax + STRUCT_STRING_PROC_NODE_NEXT_OFFSET], NULL
	mov qword [rax + STRUCT_STRING_PROC_NODE_PREVIOUS_OFFSET], NULL
	mov qword [rax + STRUCT_STRING_PROC_NODE_F_OFFSET], rdi
	mov qword [rax + STRUCT_STRING_PROC_NODE_G_OFFSET], rsi
	mov qword [rax + STRUCT_STRING_PROC_NODE_TYPE_OFFSET], rdx

	pop rbp
	ret

global string_proc_key_create
string_proc_key_create:
	push rbp
	mov rbp, rsp

	; copio value y lo guardo en rdi
	call str_copy
	mov rdi, rax

	; calculo length
	call str_len 

	push rdi ; guardo *value
	push rax ; guardo length

	; pido memoria para la key
	mov rdi, STRUCT_STRING_PROC_KEY_SIZE
	call malloc
	; obtengo *key en rax

	pop rdi ; recupero length en rdi
	pop rsi ; recupero *value en rsi

	; inicializo key
	mov qword [rax + STRUCT_STRING_PROC_KEY_LENGTH_OFFSET], rdi 
	mov qword [rax + STRUCT_STRING_PROC_KEY_VALUE_OFFSET], rsi

	pop rbp
	ret

global string_proc_list_destroy
string_proc_list_destroy:
	push rbp
	mov rbp, rsp

	; borro name
	push rdi
	sub rsp, 8
	mov rdi, [rdi + STRUCT_STRING_PROC_LIST_NAME_OFFSET]
	call free
	add rsp, 8

	; borro list
	pop rdi
	call free

	pop rbp
	ret

global string_proc_node_destroy
string_proc_node_destroy:
	push rbp
	mov rbp, rsp

	call free

	pop rbp
	ret

global string_proc_key_destroy
string_proc_key_destroy:
	push rbp
	mov rbp, rsp

	push rdi ; guardo *key

	; borro value
	mov rdi, [rdi + STRUCT_STRING_PROC_KEY_VALUE_OFFSET]
	sub rsp, 8
	call free
	add rsp, 8

	; borro key
	pop rdi
	call free

	pop rbp
	ret

global string_proc_list_add_node
string_proc_list_add_node:
	push rbp
	mov rbp, rsp

	push rdi ; guardo *list
	push rsi ; guardo f
	push rdx ; guardo g
	push rcx ; guardo type

	; creo node
	mov rdi, rsi
	mov rsi, rdx
	mov rdx, rcx
	call string_proc_node_create
	; obtengo *node en rax

	pop rcx ; recupero type 
	pop rdx ; recupero g
	pop rsi ; recupero f
	pop rdi ; recupero *list

	cmp qword [rdi + STRUCT_STRING_PROC_LIST_FIRST_OFFSET], NULL
	jz list_is_empty
list_is_not_empty:
	
	; engancho nuevo nodo a ultimo nodo de la lista
	mov r8, [rdi + STRUCT_STRING_PROC_LIST_LAST_OFFSET] ; guardo ultimo nodo en r8
	mov [r8 + STRUCT_STRING_PROC_NODE_NEXT_OFFSET], rax ; 
	mov [rax + STRUCT_STRING_PROC_NODE_PREVIOUS_OFFSET], r8 ; 

	; seteo nuevo nodo como el ultimo de la lista
	mov [rdi + STRUCT_STRING_PROC_LIST_LAST_OFFSET], rax 
	jmp finish
list_is_empty:
	; apunto list->first,last a node
	mov [rdi + STRUCT_STRING_PROC_LIST_FIRST_OFFSET], rax
	mov [rdi + STRUCT_STRING_PROC_LIST_LAST_OFFSET], rax
finish: 
	pop rbp
	ret

global string_proc_list_apply
string_proc_list_apply:
	ret

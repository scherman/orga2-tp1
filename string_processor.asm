; FUNCIONES de C
	extern malloc
	extern free
	extern fopen
	extern fclose
	extern fprintf
	extern str_copy

; /** defines bool y puntero **/
	%define NULL 0
	%define TRUE 1
	%define FALSE 0

; structs sizes
	%define STRUCT_STRING_PROC_LIST_SIZE 24

; structs offsets
	%define STRUCT_STRING_PROC_LIST_NAME_OFFSET 0
	%define STRUCT_STRING_PROC_LIST_FIRST_OFFSET 8
	%define STRUCT_STRING_PROC_LIST_LAST_OFFSET 16
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
	mov qword [rbx + STRUCT_STRING_PROC_LIST_FIRST_OFFSET], 0
	mov qword [rbx + STRUCT_STRING_PROC_LIST_LAST_OFFSET], 0

	mov rax, rbx ; guardo *list en RAX

	pop rbx
	pop rbp
	ret

global string_proc_node_create
string_proc_node_create:
	ret

global string_proc_key_create
string_proc_key_create:
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
	ret

global string_proc_key_destroy
string_proc_key_destroy:
	ret

global string_proc_list_add_node
string_proc_list_add_node:
	ret

global string_proc_list_apply
string_proc_list_apply:
	ret

; FUNCIONES de C
	extern malloc
	extern free
	extern fopen
	extern fclose
	extern fprintf

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

	push rdi ; salvo name de rdi

	; pido memoria para el struct
	mov rdi, STRUCT_STRING_PROC_LIST_SIZE
	call malloc
	; obtengo ptr en rax

	pop rdi ; reestablezco name en rdi

	; inicializo struct
	mov qword [rax + STRUCT_STRING_PROC_LIST_NAME_OFFSET], rdi
	mov qword [rax + STRUCT_STRING_PROC_LIST_FIRST_OFFSET], 0
	mov qword [rax + STRUCT_STRING_PROC_LIST_LAST_OFFSET], 0

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
	mov rsp, rbp

	; libero rdi
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

#include "string_processor.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <assert.h>

#define LIST_NAME "Marcelo"
#define LIST_NAME_LENGTH 7
#define ANOTHER_LIST_NAME "Jose"

#define KEY_NAME "Miguel"
#define KEY_NAME_LENGTH 6
#define KEY_NAME_ENCODED "Miguel"
#define KEY_NAME_ENCODED_LENGTH 6

#define NODE_FUNCTION_F shift_2
#define NODE_FUNCTION_G unshift_2
#define NODE_TYPE REVERSIBLE
#define ANOTHER_NODE_FUNCTION_F shift_position
#define ANOTHER_NODE_FUNCTION_G unshift_position
#define ANOTHER_NODE_TYPE IRREVERSIBLE


void test_str_len() {
	printf("Corriendo test_str_len... ");
	assert(str_len(LIST_NAME) == LIST_NAME_LENGTH);

	printf("OK \n");
}

void test_str_cmp() {
	printf("Corriendo test_str_cmp... ");
	assert(str_cmp(LIST_NAME, LIST_NAME));
	assert(!str_cmp(LIST_NAME, ANOTHER_LIST_NAME));

	printf("OK \n");
}

void test_str_copy() {
	printf("Corriendo test_str_copy... ");
	char *name = LIST_NAME;
	char *nameCopy = str_copy(name);

	assert(str_cmp(name, nameCopy));
	assert(name != nameCopy);

	free(nameCopy);
	printf("OK \n");
}

/**
*	crea y destruye a una lista vacía
*/
void test_create_destroy_empty_list(){
	printf("Corriendo test_create_destroy_empty_list... ");

	char* name = LIST_NAME;
	string_proc_list* list =  string_proc_list_create(name);

	// chequeo name correcto y que se haya hecho por copia
	assert(list->name != name);
	assert(str_cmp(name, LIST_NAME));

	string_proc_list_destroy(list);

	printf("OK \n");
}

/**
*	crea y destruye un nodo
*	para esta función es conveniente haber implementado al menos un par de funciones
*	(por ej. shift_2, unshift_2)
*/
void test_create_destroy_node(){
	printf("Corriendo test_create_destroy_node... ");
	string_proc_func f = NODE_FUNCTION_F;
	string_proc_func g = NODE_FUNCTION_G;
	string_proc_func_type type = NODE_TYPE;
	string_proc_node *node = string_proc_node_create(f,g, type);

	assert(node->f == NODE_FUNCTION_F);
	assert(node->g == NODE_FUNCTION_G);
	assert(node->type == NODE_TYPE);
	assert(node->next == NULL);
	assert(node->previous == NULL);

	string_proc_node_destroy(node);
	printf("OK \n");
}

/**
*	crea y destruye una clave
*/
void test_create_destroy_key(){
	printf("Corriendo test_create_destroy_key... ");
	string_proc_key *key = string_proc_key_create(KEY_NAME);
	assert(str_cmp(key->value, KEY_NAME));
	assert(key->length == KEY_NAME_LENGTH);

	string_proc_key_destroy(key);
	printf("OK \n");
}

void test_add_node_to_list() {
	printf("Corriendo test_add_node_to_list... ");

	string_proc_list *list = string_proc_list_create(LIST_NAME);
	
	// agrego primer nodo
	string_proc_list_add_node(list, NODE_FUNCTION_F, NODE_FUNCTION_G, NODE_TYPE);
	assert(list->first != NULL);
	assert(list->first == list->last);
	assert(list->first->f == NODE_FUNCTION_F);
	assert(list->first->g == NODE_FUNCTION_G);
	assert(list->first->type == NODE_TYPE);
	assert(list->first->next == NULL);
	assert(list->first->previous == NULL);

	// agrego segundo nodo
	string_proc_list_add_node(list, ANOTHER_NODE_FUNCTION_F, ANOTHER_NODE_FUNCTION_G, ANOTHER_NODE_TYPE);
	
	assert(list->first != NULL);
	assert(list->first->f == NODE_FUNCTION_F);
	assert(list->first->g == NODE_FUNCTION_G);
	assert(list->first->type == NODE_TYPE);
	assert(list->first->previous == NULL);
	assert(list->last != NULL);
	assert(list->last->f == ANOTHER_NODE_FUNCTION_F);
	assert(list->last->g == ANOTHER_NODE_FUNCTION_G);
	assert(list->last->type == ANOTHER_NODE_TYPE);
	assert(list->last->next == NULL);
	assert(list->last->previous == list->first);
	assert(list->first->next == list->last); 

	string_proc_list_destroy(list);
	printf("OK \n");
}

void test_create_destroy_nonempty_list() {
	printf("Corriendo test_create_destroy_nonempty_list... ");
	string_proc_list *list = string_proc_list_create(LIST_NAME);
	string_proc_list_add_node(list, NODE_FUNCTION_F, NODE_FUNCTION_G, NODE_TYPE);
	string_proc_list_add_node(list, ANOTHER_NODE_FUNCTION_F, ANOTHER_NODE_FUNCTION_G, ANOTHER_NODE_TYPE);

	string_proc_list_destroy(list);
	printf("OK \n");
}


void test_apply() {
	printf("Corriendo test_apply... ");
	string_proc_list *list = string_proc_list_create(LIST_NAME);
	string_proc_list_add_node(list, NODE_FUNCTION_F, NODE_FUNCTION_G, NODE_TYPE);
	string_proc_list_add_node(list, ANOTHER_NODE_FUNCTION_F, ANOTHER_NODE_FUNCTION_G, ANOTHER_NODE_TYPE);

	string_proc_key *key = string_proc_key_create(KEY_NAME);
	string_proc_list_apply(list, key, 0);
	assert(str_cmp(key->value, KEY_NAME_ENCODED));
	assert(key->length == KEY_NAME_ENCODED_LENGTH);
	
	string_proc_key_destroy(key);
	string_proc_list_destroy(list);
	printf("OK \n");
}

/**
*	crea una lista y la imprime por salida standard (stdout)		
*/
void test_print_list(){
}

/**
*	crea una lista con un solo nodo con  f:shift_2, g:unshift_2, type:reversible
*	y prueba encode y decode por separado sobre "hola mundo" imprimiendo
*	el string procesado (aplicando encode primero y luego decode a través de string_proc_list_apply) 
* 	e imprima ambos strings por salida estandard seguido de un '\n'
*/
void test_shift_2(){
	printf("Probando shift_2, unshift_2\n============\n");
}

/**
*	crea una lista con un solo nodo con  f:shift_position, g:unshift_position, type:reversible
*	y prueba encode y decode por separado sobre "hola mundo" imprimiendo
*	el string procesado (aplicando encode primero y luego decode) e imprima ambos strings por salida estandard seguido de un '\n'
*/
void test_shift_position(){
	printf("Probando shift_positon, unshift_position\n============\n");
}

/**
*	crea una lista con un solo nodo con  f:saturate_2, g:unsaturate_2, type:irreversible
*	y prueba encode y decode por separado sobre "hola mundo" imprimiendo
*	el string procesado (aplicando encode primero y luego decode) e imprima ambos strings por salida estandard seguido de un '\n'
*/
void test_saturate_2(){
	printf("Probando saturate_2, unsaturate_2\n============\n");
}

/**
*	crea una lista con un solo nodo con f:saturate_position, g:unsaturate_position, type:irreversible
*	y prueba encode y decode por separado sobre "hola mundo" imprimiendo
*	el string procesado (aplicando encode primero y luego decode) e imprima ambos strings por salida estandard seguido de un '\n'
*/
void test_saturate_position(){
	printf("Probando saturate_position, unsaturate_position\n============\n");
}

/**
*	crea una lista con dos nodos 
*		- el primero con f:shif_2, g:unshift_2, type:reversible
*		- el primero con f:shif_position, g:unshift_position, type:reversible
*	y prueba encode y decode por separado sobre "hola mundo!" imprimiendo
*	el string procesado (aplicando encode primero y luego decode) e imprima ambos strings por salida estandard seguido de un '\n'
*	Consiga la copia que invierte las funciones de la lista y pruebe ésta con el string 
*	"hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar" imprimiendo
*	el string procesado (aplicando encode primero y luego decode) e imprima ambos strings por salida estandard seguido de un '\n'
*/
void test_combo_reversible(){
	printf("Probando combo reversible\n============\n");

	printf("Probando combo irreversible invertido\n============\n");
}

/**
*	crea una lista con dos nodos 
*		- el primero con f:shif_2, g:unshift_2, type:reversible
*		- el primero con f:saturate_position, g:saturate_position, type:irreversible
*	y prueba encode y decode por separado sobre "hola mundo!" imprimiendo
*	el string procesado (aplicando encode primero y luego decode) e imprima ambos strings por salida estandard seguido de un '\n'
*	Consiga la copia que invierte las funciones de la lista y pruebe ésta con el string 
*	"hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar" imprimiendo
*	el string procesado (aplicando encode primero y luego decode) e imprima ambos strings por salida estandard seguido de un '\n'
*	Consiga la copia que filtra la primer lista dejando sólo los nodos reversibles
*	y pruebe ésta con el string "mother forgive me" imprimiendo
*	el string procesado (aplicando encode primero y luego decode) e imprima ambos strings por salida estandard seguido de un '\n'
*/
void test_combo_irreversible(){
	printf("Probando combo irreversible\n============\n");

	printf("Probando combo irreversible invertido\n============\n");

	printf("Probando combo filtrado\n============\n");

}

/**
* Corre los test a se escritos por lxs alumnxs	
*/
void run_tests(){

	test_str_len();

	test_str_cmp();

	test_str_copy();

	test_create_destroy_key();

	test_create_destroy_empty_list();

	test_create_destroy_node();

    test_add_node_to_list();

	test_create_destroy_nonempty_list();
	
	test_apply();

    // test_print_list();

	// test_shift_2();
	
	// test_shift_position();

	// test_saturate_2();

	// test_saturate_position();

	// test_combo_reversible();

	// test_combo_irreversible();
}

int main (void){
	run_tests();
	return 0;    
}

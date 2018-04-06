#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include "string_processor.h"
#include "string_processor_utils.h"

#define LIST_NAME "Marcelo"
#define LIST_NAME_LENGTH 7
#define ANOTHER_LIST_NAME "Jose"

#define KEY_NAME "Miguel"
#define KEY_NAME_LENGTH 6

#define NODE_REV_FUNCTION_F shift_2
#define NODE_REV_FUNCTION_G unshift_2
#define NODE_REV_TYPE REVERSIBLE
#define ANOTHER_NODE_REV_FUNCTION_F shift_position
#define ANOTHER_NODE_REV_FUNCTION_G unshift_position
#define ANOTHER_NODE_REV_TYPE REVERSIBLE
#define NODE_IRREV_FUNCTION_F shift_2
#define NODE_IRREV_FUNCTION_G unshift_2
#define NODE_IRREV_TYPE IRREVERSIBLE
#define ANOTHER_NODE_IRREV_FUNCTION_F shift_position
#define ANOTHER_NODE_IRREV_FUNCTION_G unshift_position
#define ANOTHER_NODE_IRREV_TYPE IRREVERSIBLE

#define ENCODE true
#define DECODE false

/**
*	crea y destruye a una lista vacía
*/
void test_create_destroy_list(){
	string_proc_list * list	= string_proc_list_create("nueva lista");
	string_proc_list_destroy(list);
}

/**
*	crea y destruye un nodo
*	para esta función es conveniente haber implementado al menos un par de funciones
*	(por ej. shift_2, unshift_2)
*/
void test_create_destroy_node(){
	string_proc_node* node	= string_proc_node_create(&shift_2, &unshift_2, REVERSIBLE);
	string_proc_node_destroy(node);
}

/**
*	crea y destruye una clave 
*/
void test_create_destroy_key(){
	string_proc_key* key	= string_proc_key_create("hola mundo");
	string_proc_key_destroy(key);
}

/**
*	crea una lista y la imprime por salida standard (stdout)		
*/
void test_print_list(){
	string_proc_list * list	= string_proc_list_create("nueva lista");
	string_proc_list_print(list, stdout);
	string_proc_list_destroy(list);
}

/**
*	crea una lista con un solo nodo con  f:shift_2, g:unshift_2, type:reversible
*	y prueba encode y decode por separado sobre "hola mundo" imprimiendo
*	el string procesado (aplicando encode primero y luego decode a través de string_proc_list_apply) 
* 	e imprima ambos strings por salida estandard seguido de un '\n'
*/
void test_shift_2(){
	printf("Probando shift_2, unshift_2\n============\n");
	string_proc_list * list	= string_proc_list_create("nueva lista");
	string_proc_list_add_node(list, &shift_2, &unshift_2, REVERSIBLE);
	string_proc_key* key	= string_proc_key_create("hola mundo");

	string_proc_list_apply(list, key, true);
	printf("%s\n", key->value);
	string_proc_list_apply(list, key, false);
	printf("%s\n", key->value);
	printf("\n");
	string_proc_key_destroy(key);
	string_proc_list_destroy(list);
}

/**
*	crea una lista con un solo nodo con  f:shift_position, g:unshift_position, type:reversible
*	y prueba encode y decode por separado sobre "hola mundo" imprimiendo
*	el string procesado (aplicando encode primero y luego decode) e imprima ambos strings por salida estandard seguido de un '\n'
*/
void test_shift_position(){
	printf("Probando shift_positon, unshift_position\n============\n");
	string_proc_list * list	= string_proc_list_create("nueva lista");
	string_proc_list_add_node(list, &shift_position, &unshift_position, REVERSIBLE);
	string_proc_key* key	= string_proc_key_create("hola mundo");

	string_proc_list_apply(list, key, true);
	printf("%s\n", key->value);
	string_proc_list_apply(list, key, false);
	printf("%s\n", key->value);
	printf("\n");
	string_proc_key_destroy(key);
	string_proc_list_destroy(list);
}

/**
*	crea una lista con un solo nodo con  f:saturate_2, g:unsaturate_2, type:irreversible
*	y prueba encode y decode por separado sobre "hola mundo" imprimiendo
*	el string procesado (aplicando encode primero y luego decode) e imprima ambos strings por salida estandard seguido de un '\n'
*/
void test_saturate_2(){
	printf("Probando saturate_2, unsaturate_2\n============\n");
	string_proc_list * list	= string_proc_list_create("nueva lista");
	string_proc_list_add_node(list, &saturate_2, &unsaturate_2, IRREVERSIBLE);
	string_proc_key* key	= string_proc_key_create("hola mundo");

	string_proc_list_apply(list, key, true);
	printf("%s\n", key->value);
	string_proc_list_apply(list, key, false);
	printf("%s\n", key->value);
	printf("\n");
	string_proc_key_destroy(key);
	string_proc_list_destroy(list);
}

/**
*	crea una lista con un solo nodo con f:saturate_position, g:unsaturate_position, type:irreversible
*	y prueba encode y decode por separado sobre "hola mundo" imprimiendo
*	el string procesado (aplicando encode primero y luego decode) e imprima ambos strings por salida estandard seguido de un '\n'
*/
void test_saturate_position(){
	printf("Probando saturate_position, unsaturate_position\n============\n");
	string_proc_list * list	= string_proc_list_create("nueva lista");
	string_proc_list_add_node(list, &saturate_position, &unsaturate_position, IRREVERSIBLE);
	string_proc_key* key	= string_proc_key_create("hola mundo");

	string_proc_list_apply(list, key, true);
	printf("%s\n", key->value);
	string_proc_list_apply(list, key, false);
	printf("%s\n", key->value);
	printf("\n");
	string_proc_key_destroy(key);
	string_proc_list_destroy(list);
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
	string_proc_list * list	= string_proc_list_create("nueva lista");
	string_proc_list_add_node(list, &unshift_2, &shift_2, REVERSIBLE);
	string_proc_list_add_node(list, &unshift_position, &shift_position, REVERSIBLE);
	string_proc_key* key	= string_proc_key_create("hola mundo");

	string_proc_list_apply(list, key, true);
	printf("%s\n", key->value);
	string_proc_list_apply(list, key, false);
	printf("%s\n", key->value);
	printf("\n");

	printf("Probando combo irreversible invertido\n============\n");
	string_proc_list* inverted_list	= string_proc_list_invert(list);
	string_proc_key* inverted_key	= string_proc_key_create("hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar");
	string_proc_list_apply(inverted_list, inverted_key, true);
	printf("%s\n", inverted_key->value);
	string_proc_list_apply(inverted_list, inverted_key, false);
	printf("%s\n", inverted_key->value);
	printf("\n");
	string_proc_key_destroy(inverted_key);
	string_proc_list_destroy(inverted_list);

	string_proc_key_destroy(key);
	string_proc_list_destroy(list);
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
	string_proc_list * list	= string_proc_list_create("nueva lista");
	string_proc_list_add_node(list, &shift_2, &unshift_2, REVERSIBLE);
	string_proc_list_add_node(list, &unsaturate_position, &saturate_position, REVERSIBLE);
	string_proc_key* key	= string_proc_key_create("hola mundo");

	string_proc_list_apply(list, key, true);
	printf("%s\n", key->value);
	string_proc_list_apply(list, key, false);
	printf("%s\n", key->value);
	printf("\n");

	printf("Probando combo irreversible invertido\n============\n");
	string_proc_list* inverted_list	= string_proc_list_invert(list);
	string_proc_key* inverted_key	= string_proc_key_create("hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar");
	string_proc_list_apply(inverted_list, inverted_key, true);
	printf("%s\n", inverted_key->value);
	string_proc_list_apply(inverted_list, inverted_key, false);
	printf("%s\n", inverted_key->value);
	printf("\n");

	printf("Probando combo filtrado\n============\n");
	string_proc_list* filtered_list	= string_proc_list_filter_by_type(list, REVERSIBLE);
	string_proc_key* filtered_key	= string_proc_key_create("mother forgive me");
	string_proc_list_apply(filtered_list, inverted_key, true);
	printf("%s\n", inverted_key->value);
	string_proc_list_apply(filtered_list, inverted_key, false);
	printf("%s\n", inverted_key->value);
	printf("\n");
	string_proc_list_apply(filtered_list, filtered_key, true);
	printf("%s\n", filtered_key->value);
	string_proc_list_apply(filtered_list, filtered_key, false);
	printf("%s\n", filtered_key->value);
	printf("\n");

	string_proc_key_destroy(filtered_key);
	string_proc_list_destroy(filtered_list);

	string_proc_key_destroy(inverted_key);
	string_proc_list_destroy(inverted_list);

	string_proc_key_destroy(key);
	string_proc_list_destroy(list);
}

//TODO:debe implementar
/**
*	crea una lista con 0, 1, 5 nodos respectivamente e imprime su longitud 
*/
void test_list_length(){
	printf("Probando largo lista\n============\n");
	// printf("---------------------- \nCorriendo test_list_length...\n");
	string_proc_list *list = string_proc_list_create(LIST_NAME);
	// printf("Longitud: %i (debe ser 0)\n", string_proc_list_length(list));
	assert(string_proc_list_length(list) == 0);
	
	string_proc_list_add_node(list, NODE_REV_FUNCTION_F, NODE_REV_FUNCTION_G, NODE_REV_TYPE);
	// printf("Longitud: %i (debe ser 1)\n", string_proc_list_length(list));
	assert(string_proc_list_length(list) == 1);

	string_proc_list_add_node(list, ANOTHER_NODE_REV_FUNCTION_F, ANOTHER_NODE_REV_FUNCTION_G, ANOTHER_NODE_REV_TYPE);
	string_proc_list_add_node(list, NODE_REV_FUNCTION_F, NODE_REV_FUNCTION_G, NODE_REV_TYPE);
	string_proc_list_add_node(list, ANOTHER_NODE_REV_FUNCTION_F, ANOTHER_NODE_REV_FUNCTION_G, ANOTHER_NODE_REV_TYPE);
	string_proc_list_add_node(list, NODE_REV_FUNCTION_F, NODE_REV_FUNCTION_G, NODE_REV_TYPE);
	// printf("Longitud: %i (debe ser 5)\n", string_proc_list_length(list));
	assert(string_proc_list_length(list) == 5);

	string_proc_list_destroy(list);
	// printf("OK!\n");
}

//TODO:debe implementar
/**
*	para todos los casos imprimir los estados de la lista
*	crea una lista vacía y le agrega y quita un elemento al comienzo
*	crea una lista con cinco nodos irreversibles y:
*		agrega y quita al comienzo un nodo reversible
*		agrega y quita al final un nodo reversible
*		intenta agregar y quitar un nodo reversible fuera de rango
*		agrega y quita un nodo reversible en la posición 2
*/
void test_list_add_remove_node(){
	printf("Probando agregar y quitar nodo\n============\n");
	// printf("---------------------- \nCorriendo test_list_add_remove_node...\n");
	
	// printf("Lista inicial: ");
	string_proc_list *list = string_proc_list_create(LIST_NAME);
	string_proc_list_print(list, stdout);
	
	// printf("Agrego un nodo: ");
	string_proc_list_add_node_at(list, NODE_REV_FUNCTION_F, NODE_REV_FUNCTION_G, NODE_REV_TYPE, 0);
	string_proc_list_print(list, stdout);
	assert(list->first != NULL);
	assert(list->first == list->last);
	assert(list->first->f == NODE_REV_FUNCTION_F);
	assert(list->first->g == NODE_REV_FUNCTION_G);
	assert(list->first->type == NODE_REV_TYPE);
	assert(list->first->next == NULL);
	assert(list->first->previous == NULL);

	// printf("Elimino el nodo: ");
	string_proc_list_remove_node_at(list, 0);
	string_proc_list_print(list, stdout);
	assert(list->first == NULL);
	assert(list->last == NULL);

	// printf("Agrego 5 nodos irreversibles: ");
	string_proc_list_add_node(list, NODE_IRREV_FUNCTION_F, NODE_IRREV_FUNCTION_G, NODE_IRREV_TYPE);
	string_proc_list_add_node(list, ANOTHER_NODE_IRREV_FUNCTION_F, ANOTHER_NODE_IRREV_FUNCTION_G, ANOTHER_NODE_IRREV_TYPE);
	string_proc_list_add_node(list, NODE_IRREV_FUNCTION_F, NODE_IRREV_FUNCTION_G, NODE_IRREV_TYPE);
	string_proc_list_add_node(list, ANOTHER_NODE_IRREV_FUNCTION_F, ANOTHER_NODE_IRREV_FUNCTION_G, ANOTHER_NODE_IRREV_TYPE);
	string_proc_list_add_node(list, NODE_IRREV_FUNCTION_F, NODE_IRREV_FUNCTION_G, NODE_IRREV_TYPE);
	string_proc_list_print(list, stdout);

	// printf("Agrego nodo reversible al ppio: ");
	string_proc_list_add_node_at(list, NODE_REV_FUNCTION_F, NODE_REV_FUNCTION_G, NODE_REV_TYPE,0);
	string_proc_list_print(list, stdout);
	assert(string_proc_list_length(list) == 6);
	assert(list->first->f == NODE_REV_FUNCTION_F);
	assert(list->first->g == NODE_REV_FUNCTION_G);
	assert(list->first->type == NODE_REV_TYPE);
	assert(list->first->next != NULL);
	assert(list->first->next->f == NODE_IRREV_FUNCTION_F);
	assert(list->first->next->previous == list->first);
	assert(list->first->previous == NULL);

	// printf("Elimino el nodo reversible: ");
	string_proc_list_remove_node_at(list, 0);
	string_proc_list_print(list, stdout);
	assert(list->first->f == NODE_IRREV_FUNCTION_F);
	assert(string_proc_list_length(list) == 5);

	// printf("Agrego nodo irreversible al final: ");
	string_proc_list_add_node_at(list, ANOTHER_NODE_IRREV_FUNCTION_F, ANOTHER_NODE_IRREV_FUNCTION_G, ANOTHER_NODE_IRREV_TYPE, 5);
	string_proc_list_print(list, stdout);
	assert(string_proc_list_length(list) == 6);
	assert(list->last->f == ANOTHER_NODE_IRREV_FUNCTION_F);
	assert(list->last->g == ANOTHER_NODE_IRREV_FUNCTION_G);
	assert(list->last->type == ANOTHER_NODE_IRREV_TYPE);
	assert(list->last->previous != NULL);
	assert(list->last->previous->f == NODE_IRREV_FUNCTION_F);
	assert(list->last->previous->next == list->last);
	assert(list->last->next == NULL);

	// printf("Lo elimino: ");
	string_proc_list_remove_node_at(list, 5);
	string_proc_list_print(list, stdout);
	assert(list->last->f == NODE_IRREV_FUNCTION_F);
	assert(string_proc_list_length(list) == 5);

	// printf("Intento eliminar nodos fuera de rango: ");
	uint32_t length = string_proc_list_length(list);
	bool successRmv1 = string_proc_list_remove_node_at(list, length);
	bool successRmv2 = string_proc_list_remove_node_at(list, length + 5);
	string_proc_list_print(list, stdout);
	assert(!successRmv1 && !successRmv2);
	assert(string_proc_list_length(list) == length);

	// printf("Intento agregar nodos fuera de rango: ");
	bool successAdd1 = string_proc_list_add_node_at(list, NODE_REV_FUNCTION_F, NODE_REV_FUNCTION_G, NODE_REV_TYPE, length + 1);
	bool successAdd2 = string_proc_list_add_node_at(list, NODE_REV_FUNCTION_F, NODE_REV_FUNCTION_G, NODE_REV_TYPE, length + 5);
	string_proc_list_print(list, stdout);
	assert(!successAdd1 && !successAdd2);
	assert(string_proc_list_length(list) == length);

	string_proc_list_destroy(list);
	// printf("OK!\n");
}


//TODO:debe implementar
/**
*	crea una lista con cinco dos nodos irreversibles, uno reversible y uno irreversible (en ese orden), imprimirla, conseguir la copia de orden inverso 
*	(string_proc_list_invert_order) e imprimir la copia
*/
void test_list_invert_order(){
	printf("Probando invertir el orden de la lista\n============\n");
	// printf("---------------------- \nCorriendo test_list_invert_order...\n");
	
	// printf("Lista inicial: ");
	string_proc_list *list = string_proc_list_create(LIST_NAME);
	string_proc_list_add_node(list, NODE_IRREV_FUNCTION_F, NODE_IRREV_FUNCTION_G, NODE_IRREV_TYPE);
	string_proc_list_add_node(list, ANOTHER_NODE_IRREV_FUNCTION_F, ANOTHER_NODE_IRREV_FUNCTION_G, ANOTHER_NODE_IRREV_TYPE);
	string_proc_list_add_node(list, NODE_IRREV_FUNCTION_F, NODE_IRREV_FUNCTION_G, NODE_IRREV_TYPE);
	string_proc_list_add_node(list, NODE_IRREV_FUNCTION_F, NODE_IRREV_FUNCTION_G, NODE_IRREV_TYPE);
	string_proc_list_add_node(list, ANOTHER_NODE_IRREV_FUNCTION_F, ANOTHER_NODE_IRREV_FUNCTION_G, ANOTHER_NODE_IRREV_TYPE);
	string_proc_list_add_node(list, NODE_REV_FUNCTION_F, NODE_REV_FUNCTION_G, NODE_REV_TYPE);
	string_proc_list_add_node(list, ANOTHER_NODE_IRREV_FUNCTION_F, ANOTHER_NODE_IRREV_FUNCTION_G, ANOTHER_NODE_IRREV_TYPE);	
	string_proc_list_print(list, stdout);

	// printf("Lista invertida: ");
	string_proc_list *copy = string_proc_list_invert_order(list);
	string_proc_list_print(copy, stdout);
	uint32_t listLength = string_proc_list_length(list);
	uint32_t copyLength = string_proc_list_length(copy);
	assert(str_cmp(copy->name, list->name) == 0);
	assert(copyLength == listLength);
	assert(copy->first != NULL);
	assert(copy->last != NULL);	

	// chequeo que los nodos coinciden (en orden inverso)
	string_proc_node *actualCopy = copy->first;
	string_proc_node *actualList = list->last;
	for (size_t i = 0; i < listLength; i++){
		assert(actualCopy != NULL);
		assert(actualList != NULL);
		assert(actualCopy->f == actualList->f);
		assert(actualCopy->g == actualList->g);
		assert(actualCopy->type == actualList->type);
		
		actualCopy = actualCopy->next;
		actualList = actualList->previous;
	}

	string_proc_list_destroy(list);
	string_proc_list_destroy(copy);
	// printf("OK!\n");
}

//TODO:debe implementar
/**
*	crea una lista con cinco dos nodos irreversibles, uno reversible y uno irreversible (en ese orden), imprimirla, conseguir la copia de orden inverso 
*	(string_proc_list_invert_order) y hace la llamada a string_proc_list_apply_print_trace
*/
void test_list_apply_print_trace(){
	printf("Probando apply print trace\n============\n");
	// printf("---------------------- \nCorriendo test_list_apply_print_trace...\n");
	
	// printf("Lista inicial: ");
	string_proc_list *list = string_proc_list_create(LIST_NAME);
	string_proc_list_add_node(list, NODE_IRREV_FUNCTION_F, NODE_IRREV_FUNCTION_G, NODE_IRREV_TYPE);
	string_proc_list_add_node(list, ANOTHER_NODE_IRREV_FUNCTION_F, ANOTHER_NODE_IRREV_FUNCTION_G, ANOTHER_NODE_IRREV_TYPE);
	string_proc_list_add_node(list, NODE_IRREV_FUNCTION_F, NODE_IRREV_FUNCTION_G, NODE_IRREV_TYPE);
	string_proc_list_add_node(list, NODE_IRREV_FUNCTION_F, NODE_IRREV_FUNCTION_G, NODE_IRREV_TYPE);
	string_proc_list_add_node(list, ANOTHER_NODE_IRREV_FUNCTION_F, ANOTHER_NODE_IRREV_FUNCTION_G, ANOTHER_NODE_IRREV_TYPE);
	string_proc_list_add_node(list, NODE_REV_FUNCTION_F, NODE_REV_FUNCTION_G, NODE_REV_TYPE);
	string_proc_list_add_node(list, ANOTHER_NODE_IRREV_FUNCTION_F, ANOTHER_NODE_IRREV_FUNCTION_G, ANOTHER_NODE_IRREV_TYPE);	
	string_proc_list_print(list, stdout);

	string_proc_list *invertedList = string_proc_list_invert_order(list);
	string_proc_key *key = string_proc_key_create(KEY_NAME);
	string_proc_list_apply_print_trace(invertedList, key, ENCODE, stdout);

	string_proc_key_destroy(key);
	string_proc_list_destroy(list);
	string_proc_list_destroy(invertedList);
	// printf("OK!\n");
}

//TODO:debe implementar
/**
*	probar las funciones saturate_2_odd, unsaturate_2_odd, shift_position_prime, unshift_position_prime
*	sobre el string "hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar"
*/
void test_odd_prime(){
	printf("Probando operaciones sobre posiciones impares y primas\n============\n");
	// printf("---------------------- \nCorriendo test_odd_prime...\n");
	
	char* value = "hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar";

	// printf("Evalúo transformaciones sobre '%s'...\n", value);

	string_proc_key *key1 = string_proc_key_create(value);
	saturate_2_odd(key1);
	// printf(">>> saturate_2_odd: %s\n", key1->value);

	string_proc_key *key2 = string_proc_key_create(value);
	unsaturate_2_odd(key2);
	// printf(">>> unsaturate_2_odd: %s\n", key2->value);
	
	string_proc_key *key3 = string_proc_key_create(value);
	shift_position_prime(key3);
	// printf(">>> shift_position_prime: %s\n", key3->value);

	string_proc_key *key4 = string_proc_key_create(value);
	unshift_position_prime(key4);
	// printf(">>> unshift_position_prime: %s\n", key4->value);

	string_proc_key_destroy(key1);
	string_proc_key_destroy(key2);
	string_proc_key_destroy(key3);
	string_proc_key_destroy(key4);
	// printf("OK!\n");
}


/**
*	Corre los test a se escritos por lxs alumnxs	
*/
void run_tests(){

	//tests principales
	test_create_destroy_list();

	test_create_destroy_node();

	test_create_destroy_key();

	test_print_list();

	test_shift_2();
	
	test_shift_position();

	test_saturate_2();

	test_saturate_position();

	test_combo_reversible();

	test_combo_irreversible();

	//tests utilidades
	test_list_length();
	
	test_list_add_remove_node();

	test_list_invert_order();

	test_list_apply_print_trace();

	test_odd_prime();
}

int main (void){
	run_tests();
	return 0;    
}

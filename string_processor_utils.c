#include <stdbool.h>
#include <stdio.h>
#include "string_processor.h"
#include "string_processor_utils.h"
#include <inttypes.h>

#define MAX_ASCII_CHAR 127


//TODO: debe implementar
/**
*	Debe devolver el largo de la lista pasada por parámetro
*/
uint32_t string_proc_list_length(string_proc_list* list){ 
    string_proc_node* actual = list->first;
    if (actual == NULL) return 0;
    int count = 0;
    while (actual != NULL) {
        actual = actual->next;
        count++;
    }
    return count;
}

//TODO: debe implementar
/**
*	Debe insertar el nodo con los parámetros correspondientes en la posición indicada por index desplazando en una
*	posición hacia adelante los nodos sucesivos en caso de ser necesario, la estructura de la lista debe ser
*	actualizada de forma acorde
*	si index es igual al largo de la lista debe insertarlo al final de la misma
*	si index es mayor al largo de la lista no debe insertar el nodo
*	debe devolver true si el nodo pudo ser insertado en la lista, false en caso contrario
*/
bool string_proc_list_add_node_at(string_proc_list* list, string_proc_func f, string_proc_func g, string_proc_func_type type, uint32_t index){
    if (index > string_proc_list_length(list)) return false;
    
    string_proc_node *newNode = string_proc_node_create(f, g, type);    

    // busco el nodo en index specificado
    string_proc_node *nodeAtIndex = list->first;
    for (size_t i = 0; i < index; i++){
        nodeAtIndex = nodeAtIndex->next;
    }

    // engancho al nuevo nodo en la lista y actualizo first/last
    if (nodeAtIndex == NULL) {
        // el nodo será necesariamente el último de la lista.
        string_proc_node *prior = list->last;

        // engancho al anterior
        if (prior != NULL) {
            newNode->previous = prior;
            prior->next = newNode;
        } else {
            list->first = newNode;
        }
        list->last = newNode;
    } else {
        string_proc_node *prior = nodeAtIndex->previous;
        
        // engancho al siguiente
        newNode->next = nodeAtIndex;
        nodeAtIndex->previous = newNode;

        // engancho al anterior
        if (prior != NULL) {
            newNode->previous = prior;
            prior->next = newNode;
        } else {
            list->first = newNode;
        }
    }
    return true; 
}

//TODO: debe implementar
/**
*	Debe eliminar el nodo que se encuentra en la posición indicada por index de ser posible
*	la lista debe ser actualizada de forma acorde y debe devolver true si pudo eliminar el nodo o false en caso contrario
*/
bool string_proc_list_remove_node_at(string_proc_list* list, uint32_t index){
    if (string_proc_list_length(list) <= index) return false;
    
    // busco el nodo en index especificado (si existe)
    string_proc_node *nodeAtIndex = list->first;
    for (size_t i = 0; i < index; i++){
        nodeAtIndex = nodeAtIndex->next;    
    }

    // desengancho al nodo de la lista y lo borro
    if (list->last == nodeAtIndex) {
        if (list->first != nodeAtIndex) {
            string_proc_node *prior = nodeAtIndex->previous;
            prior->next = NULL;
            list->last = prior;
        } else {
            list->first = NULL;
            list->last = NULL;
        }
    } else {
        if (list->first != nodeAtIndex) {
            string_proc_node *prior = nodeAtIndex->previous;
            string_proc_node *posterior = nodeAtIndex->next;
            prior->next = posterior;
            posterior->previous = prior;
        } else {
            string_proc_node *posterior = nodeAtIndex->next;
            posterior->previous = NULL;
            list->first = posterior;
        }
    }
    string_proc_node_destroy(nodeAtIndex);

    return true;
}

//TODO: debe implementar
/**
*	Debe devolver una copia de la lista pasada por parámetro copiando los nodos en el orden inverso
*/
string_proc_list* string_proc_list_invert_order(string_proc_list* list){
    string_proc_list *copy = string_proc_list_create(list->name);
    
    // recorro la lista de atras para adelante, agregando los nodos de adelante para atrás en la copia
    string_proc_node *actual = list->last;
    while(actual != NULL) {
        string_proc_list_add_node(copy, actual->f, actual->g, actual->type);
        actual = actual->previous;
    }

    return copy; 
}

//TODO: debe implementar
/**
*	Hace una llamada sucesiva a los nodos de la lista pasada por parámetro siguiendo la misma lógica
*	que string_proc_list_apply pero comienza imprimiendo una línea 
*	"Encoding key 'valor_de_la_clave' through list nombre_de_la_list\n"
* 	y luego por cada aplicación de una función f o g escribe 
*	"Applying function at [direccion_de_funcion] to get 'valor_de_la_clave'\n"
*/
void string_proc_list_apply_print_trace(string_proc_list* list, string_proc_key* key, bool encode, FILE* file){
    fprintf(file, "Decoding key '%s' through list %s\n", key->value, list->name);
    if (encode) {
        // recorro nodos aplicando f desde first hacia adelante
        string_proc_node *actual = list->first;
        while(actual != NULL) {
            fprintf(file, "Applying function at [0x%" PRIXPTR "] ", (uintptr_t) actual->f);
            actual->f(key);
            fprintf(file, "to get '%s'\n", key->value);
            actual = actual->next;
        }
    } else {
        // recorro nodos aplicando g desde last hacia atrás
        string_proc_node *actual = list->last;
        while(actual != NULL) {
            fprintf(file, "Applying function at [0x%" PRIXPTR "] ", (uintptr_t) actual->g);
            actual->g(key);
            fprintf(file, "to get '%s'\n", key->value);
            actual = actual->previous;
        }
    }
}

//TODO: debe implementar
/**
*	Debe desplazar en dos posiciones hacia adelante el valor de cada caracter de la clave pasada por parámetro
*	si el mismo se encuentra en una posición impar, resolviendo los excesos de representación por saturación
*/
void saturate_2_odd(string_proc_key* key){
    char* value = key->value;
    uint32_t length = key->length;
    for(size_t i = 1; i < key->length; i+=2) {
        unsigned char transformed = value[i] + 2;
        value[i] = saturate_int(transformed);
    }
}

//TODO: debe implementar
/**
*	Debe desplazar en dos posiciones hacia atrás el valor de cada caracter de la clave pasada por parámetro
*	si el mismo se encuentra en una posición impar, resolviendo los excesos de representación por saturación
*/
void unsaturate_2_odd(string_proc_key* key){
    char* value = key->value;
    uint32_t length = key->length;
    for(size_t i = 1; i < key->length; i+=2) {
        char transformed = value[i] - 2;
        value[i] = saturate_int(transformed);
    }
}

int32_t isPrime(int32_t num){
    if (num < 2) return false;
    for (int32_t d = 2; d < num; d = d + 1) {
	    if (num % d == 0) return 0;
    }
    return 1;
}

//TODO: debe implementar
/**
*	Debe desplazar en tantas posiciones como sea la posición hacia adelante del valor de cada caracter de la clave pasada por parámetro
*	si el mismo se encuentra en una posición que sea un número primo, resolviendo los excesos de representación con wrap around
*/
void shift_position_prime(string_proc_key* key){
    char* value = key->value;
    uint32_t length = key->length;

    for(size_t i = 0; i < key->length; i++) {
        if (!isPrime(i)) continue;
        char transformed = value[i] + i;
        value[i] = wrap_around_int(transformed);
    }
}


//TODO: debe implementar
/**
*	Debe desplazar en tantas posiciones como sea la posición hacia atrás del valor de cada caracter de la clave pasada por parámetro
*	si el mismo se encuentra en una posición que sea un número primo, resolviendo los excesos de representación con wrap around
*/
void unshift_position_prime(string_proc_key* key){
    char* value = key->value;
    uint32_t length = key->length;

    for(size_t i = 0; i < key->length; i++) {
        if (!isPrime(i)) continue;
        char transformed = value[i] - i;
        value[i] = wrap_around_int(transformed);
    }
}

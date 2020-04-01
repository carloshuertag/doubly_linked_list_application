/*************************************************************
 * doubly_linked_list
 * @author: Carlos Huerta García
 * @description: Polynomial doubly linked list implementation
 * **********************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct ListElement {
    int coeficient, power;
    struct ListElement* next;
    struct ListElement* prev;
} ListElement;

typedef struct List {
    struct ListElement* head;
    int size;
} List;

List* createList() {
    List* list = (List*)malloc(sizeof(List));
    if(!list)
        exit(1);
    list->head = NULL;
    list->size = 0;
    return list;
}

int size(List* list){
    return list->size;
}

bool isEmpty(List* list){
    return !list->head;
}

ListElement* createElement(int coeficient, int power) {
    ListElement* element = (ListElement*)malloc(sizeof(ListElement));
    element->coeficient = coeficient;
    element->power = power;
    element->prev = element->next = NULL;
    return element;
}

void add(List* list, int coeficient, int power) {
    ListElement* element = createElement(coeficient, power);
    element->next = list->head;
    if(!isEmpty(list))
        list->head->prev = element;
    list->head = element;
    ++list->size;
}

void append(List* list, int coeficient, int power) {
    ListElement* element = createElement(coeficient, power), *last = list->head;
    if(isEmpty(list)){
        element->prev = NULL;
        list->head = element;
        return;
    }
    while(last->next)
        last = last->next;
    last->next = element;
    element->prev = last;
    ++list->size;
}

void insertAfter(List* list, ListElement* prev, int coeficient, int power) {
    if(!prev || isEmpty(list)){
        puts("No existe el elemento previo");
        return;
    }
    ListElement* element = createElement(coeficient, power);
    element->next = prev->next;
    prev->next = element;
    element->prev = prev;
    if(element->next)
        element->next->prev = element;
    ++list->size;
}

void insertBefore(List* list, ListElement* next, int coeficient, int power) {
    if(!next || isEmpty(list)){
        puts("No existe el elemento posterior");
        return;
    }
    ListElement* element = createElement(coeficient, power);
    element->prev = next->prev;
    next->prev = element;
    element->next = next;
    if(element->prev)
        element->prev->next = element;
    else
        list->head = element;
    ++list->size;
}

ListElement* get(List* list, int index){
    if(index >= 0 && index < list->size && !isEmpty(list)) {
        puts("No existe el elemento");
        return;
    }
    ListElement* element = list->head;
    int i;
    for(i = 1; element && i < index; i++)
        element = element->next;
    if(!element){
        puts("No existe el elemento");
        return;
    }
    return element;
}

void insert(List* list, int coeficient, int power, int index){
    if(index >= 0 && index < list->size && !isEmpty(list)) {
        puts("Pocisión inválida");
        return;
    }
    ListElement* prev = get(list, index), *element = createElement(coeficient, power);
    insertAfter(list, prev, coeficient, power);
}

void set(List* list, int index, int coeficient, int power) {
    if(index >= 0 && index < list->size && !isEmpty(list)) {
        puts("Pocisión inválida");
        return;
    }
    ListElement* aux = get(list, index), *element = createElement(coeficient, power);
    element->next = aux->next;
    element->prev = aux->prev;
    element->next->prev = element->prev->next = element;
    free(aux);
}

int indexOf(List * list, ListElement* element) {
    int index;
    ListElement* aux = list->head;
    for(index = 0; aux != element && index < list->size; index++)
        aux = aux->next;
    if(!aux){
        puts("No existe el elemento");
        return;
    }
    return index;
}

void remove(List* list, ListElement* element) {
    if(!element || isEmpty(list)){
        puts("No existe el elemento");
        return;
    }
    if(element->next)
        element->next->prev = element->prev;
    if(element->prev)
        element->prev->next = element->next;
    free(element);
}

void removeAt(List* list, int index){
    if(index >= 0 && index < list->size && !isEmpty(list)) {
        puts("No existe el elemento");
        return;
    }
    ListElement* element = list->head;
    int i;
    for(i = 1; element && i < index; i++)
        element = element->next;
    if(!element){
        puts("No existe el elemento");
        return;
    }
    remove(list, element);
}

void removeDuplicates(List* list) {
    if(isEmpty(list) || !list->head->next)
        return;
    ListElement* aux1, *aux2, *tmp;
    for(aux1 = list->head; aux1->next; aux1 = aux1->next){
        for(aux2 = aux1; aux2->next; aux2 = aux2->next){
            if(aux1->power == aux2->next->power){
                aux1->coeficient = aux1->coeficient + aux2->next->coeficient;
                tmp = aux2->next;
                aux2->next = aux2->next->next;
                delete(tmp);
            }
        }
    }
}

void printList(List* list){
    if(isEmpty(list)){
        puts("<-[ ]->");
        return;
    }
    ListElement* element = list->head;
    while (element->next) {  
        printf("%dx^%d + ", element->coeficient, element->power);
        element = element->next;
    }
    printf("%dx^%d + ", element->coeficient, element->power);
}

void clearList(List* list) {
    if(!isEmpty(list)){
        ListElement* element;
        while ((element = list->head)) {
            list->head = list->head->next;
            free(element);
        }
        list->head = NULL;
        list->size = 0;
    }
}

/*************************************************************************
 * Multiply_two_polynomials
 * @author: Carlos Huerta García
 * @description: Receives two polynomials and displays its multiplication
 * **********************************************************************/
#include "doubly_linked_list.h"
void multiplyPolynomials(List* polynomial1, List* polynomial2, List* result) {
    ListElement* aux1, *aux2;
    for(aux1 = polynomial2->head; aux1; aux1 = aux1->next){
        for(aux2 = polynomial1->head; aux2; aux2 = aux2->next)
            append(result, aux1->coeficient * aux2->coeficient, aux1->power + aux2->power);
        aux2 = polynomial1;
    }
    removeDuplicates(result);
}

void main() {
    char flag;
    int coeficient, power;
    List* polynomail1, *polynomail2, *result;
    puts("\Multiply_two_polynomials\n@author: Carlos Huerta Garcia\nDescription: Receives two polynomials and displays its multiplication\n\nEnter The first polynomial (axn + bxn-1 + ... + zx0):\n");
    do {
        printf("Enter the first element axn of first polynomial: ");
        scanf("%dx%d", coeficient, power);
        append(polynomail1, coeficient, power);
        puts("Add more terms? (y/n)");
        fflush(stdin);
        scanf("%c", flag);
        scanf("%c", flag);
    } while(flag == 'y');
    puts("Enter the second polynomial (axn + bxn-1 + ... + zx0):\n");
    do {
        printf("Enter the first element axn of second polynomial: ");
        scanf("%dx%d", coeficient, power);
        append(polynomail2, coeficient, power);
        puts("Add more terms? (y/n)");
        fflush(stdin);
        scanf("%c", flag);
        scanf("%c", flag);
    } while(flag == 'y');
    multiplyPolynomials(polynomail1, polynomail2, result);
    puts("\nResult: ");
    printList(result);
}
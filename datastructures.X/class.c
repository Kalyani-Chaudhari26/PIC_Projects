// CONFIG
#pragma config FOSC = HS    // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
#include <stdio.h>
#include <stdlib.h>

void display();

struct node {
    int data;
    struct node *next;
    struct node *prev;
} *head, *old, *p, *n;

void main() {
    int i, j, k, l, m;

    printf("Enter the number of nodes:\n");
    scanf("%d", &m);

    // Creating the first node
    head = (struct node *)malloc(sizeof(struct node));
    printf("Enter the data:\n");
    scanf("%d", &head->data);
    head->next = NULL;
    old = head;

    // Creating remaining nodes
    for (i = 1; i < m; i++) {
        n = (struct node *)malloc(sizeof(struct node));
        printf("Enter the data:\n");
        scanf("%d", &n->data);
        n->next = NULL;
        old->next = n;
        old = n;
    }
//
 printf("Before change display\n");
//   
    display();
//printf("reverse\n");
    reverse_display()
}
////insert at beginig
///n=(struct node)malloc(sizeof(struct node));
//  printf("enter the data\n");
//scanf("%d",&n->data);
//n->next = NULL;
//n->next = head;
//head = n;*/
//  printf("enter the data\n");
//   scanf("%d",&head->data);
//head->next=NULL;
//head->prev=NULL;
//old = head;
//
//for(i=1;i<m;i++)
//{
//    n=(struct node*)malloc(sizeof(struct node));
//    printf("enter the data\n");
//    scanf("%d",&n->data);
//    n->next = NULL;
//    n->prev = NULL;
//    old->next = n;
//    old = n;
//}
//
//printf("before change display\n");
//    printf("After change display\n");
//    display();
//}
//
//void display() {
//    p = head;
//    while (p != NULL) {
//        printf("%d\n", p->data);
//        p = p->next;
//    }
//}
//// Deletion at middle
//printf("Enter the position\n");
//scanf("%d", &m);
//
//p = head;
//for (i = 1; i < m; i++) {
//    old = p;
//    p = p->next;
//}
//
//old->next = p->next;
//free(p);
////insert at begin
//printf("enter the position\n");
//scanf("%d",&m);
//p=head;
//for(i=1;i<m;i++)
//{
//    p=p->next;
//}
//
//n=(struct node*)malloc(sizeof(struct node));
//printf("enter the data\n");
//scanf("%d",&n->data);
//n->next = NULL;
//n->prev = NULL;
//n->next=p;
//n->prev = p->prev;
//p->prev = n;
//old = n->prev;
//old->next=n;
//
//printf("after change display\n");
//display();
//}
//insert at middle
printf("enter the postition\n");
scanf("%d", &m);
n = (struct node*)malloc(sizeof(struct node));
printf("enter the data\n");
scanf("%d", &n->data);
n->next = NULL;
p = head;
for(i = 1; i < (m - 1); i++)
{
    p = p->next;
}
old = p->next;
p->next = n;
void reverse_display()
{
    p = head;
    while(p->next != NULL)
    {
        p = p->next;
    }
    while(p != NULL)
    {
        printf("%d\n", p->data);
        p = p->prev;
    }
}

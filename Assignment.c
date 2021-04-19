#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Employee {
    int id;
    char name[100];
    float salary;
} Employee;

typedef struct Node {
    Employee *data;
    Node *next;
    Node *prev;
} Node;

Node *head = NULL;
Node *last = NULL;

const int   SELECT_EXIT   = 6;
const char *COLOR_DEFAULT = "\033[0;37m";
const char *COLOR_ERROR   = "\033[0;31m";
const char *COLOR_SUCCESS = "\033[0;32m";

// util methods
void setColorToPrint(const char color[]) {
    printf(color);
}

int  hasEmployee() {
    return head == NULL ? -1 : 1;
};

void printEmployee(Employee *emp) {
    setColorToPrint(COLOR_SUCCESS);
    printf("\n");
    printf("%s %d", "ID:", emp->id);
    printf(" %s %s", "NAME:", emp->name);
    printf(" %s %f", "SALARY:", emp->salary);
    printf("\n");
    setColorToPrint(COLOR_DEFAULT);
};

void notify(char message[], const char color[]) {
    setColorToPrint(color);
    printf("\n");
    printf("%s",message);
    printf("\n");
    setColorToPrint(COLOR_DEFAULT);
}

// main methods
void addEmpl(Employee *empl) {
    printf("input id: ");
    scanf("%d", &empl->id);
    printf("input name: ");
    scanf("%s", &empl->name);
    printf("input salary: ");
    scanf("%f", &empl->salary);

    Node *node = (Node*)malloc(sizeof(Node));
    node->data = empl;
    node->next = NULL;
    node->prev = NULL;

    if (head == NULL && last == NULL) {
        head = node;
    } else {
        node->prev = last;
        last->next = node;
    }

    last = node;
    notify( "ADD SUCCESSFULLY", COLOR_SUCCESS );

};

void deleteEmpl(int id) {
    Node *node = head;

    if (hasEmployee() == -1) {
        notify( "Your list is empty!", COLOR_ERROR );
        return;
    }

    int found = -1;
    while (node != NULL) {
        if (node->data->id == id) {
           
            found = 1;
            Node *prevNode = node->prev; 
            Node *nextNode = node->next;
            
            if (prevNode == NULL) {
                notify("PRINT", COLOR_SUCCESS);
                head = head->next;
                if (head != NULL)
                    head->prev = NULL;
                break;
            }

            if (nextNode == NULL) {
                last = last->prev;
                if (last != NULL)
                    last->next = NULL;
                break;
            }

            prevNode->next = nextNode;
            nextNode->prev = prevNode;

            node = NULL;
            
            break;
        }

        node = node->next;
    }

    if (found == -1)
        notify( "NOT FOUND EMPLOYEE", COLOR_SUCCESS );    
    else 
        notify( "DELETE SUCCESSFULLY", COLOR_SUCCESS );
}

void searchByIdOrName(int id, char name[]) {
    struct Node *node = head;

    if (hasEmployee() == -1) {
        notify("Your list is empty!", COLOR_ERROR);
        return;
    }

    int found = -1;
    while (node != NULL)
    {

        if (node->data->id == id || strcmp(node->data->name, name) == 0)
        {
            notify( "FOUND A EMPLOYEE", COLOR_SUCCESS);
            printEmployee(node->data);
            found = 1;
        }

        node = node->next;
    }

    if (found == -1) {
        notify( "this employee is not exist!", COLOR_ERROR);
        return;
    }
}

void printList() {
    Node *node = head;
    
    if (hasEmployee() == -1) {
        notify("Your list is empty!", COLOR_ERROR);
        return;
    }

    while (node != NULL) {
        printEmployee(node->data);
        node = node->next;
    }
};

int  menu() {
    printf("\n1. Add employee");
    printf("\n2. Search by name");
    printf("\n3. Search by ID");
    printf("\n4. Delete employee");
    printf("\n5. Print all of employees");
    printf("\n6: Exit.");
    printf("\nSelect one of the methods above: ");
    int select;
    scanf("%d", &select);
    return select;
};

// exe method
int  main() {
    const int EXIT = 6;
    int select = 0;
    
    do {
        select = menu();

        switch (select) {
            case 1: {
                Employee *empl = (Employee*) malloc( sizeof(Employee) );
                addEmpl(empl);
                break; }
            case 2: {
                char name[100];
                printf("input name: ");
                scanf("%s", &name);
                searchByIdOrName(-1, name);
                break; }
            case 3: {   
                int id;
                printf("input ID: ");
                scanf("%d", &id);
                searchByIdOrName(id, "");
                break; }
            case 4: {
                int id;
                printf("input ID: ");
                scanf("%d", &id);
                deleteEmpl(id);
                break; }
            case 5: {
                printList();
                break; }
            default:
                select = EXIT;
        }
    } while (select != EXIT);

    return 0;
}
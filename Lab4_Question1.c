// Fig. 12.3: fig12_03.c
// Inserting and deleting nodes in a list

/*   Lablinklist.c

	This is a modified version of the linklist. code discussed in class
	
	it returns 3 warnings and the students is expected to fix each warning one at a time 
	run the program and explain why it , may, run not as expected
		
	this not only test the student understanding of the code but also 
	how to quite rigorously test code.

*/

#include <stdio.h>
#include <stdlib.h>

// self-referential structure                       
struct listNode {
    char data; // each listNode contains a character
    struct listNode *nextPtr; // pointer to next node
};

typedef struct listNode ListNode; // synonym for struct listNode
//typedef ListNode* ListNode*; // synonym for ListNode*

// prototypes
void insert(ListNode* *sPtr, char value);
char delete(ListNode* *sPtr, char value);
int isEmpty(ListNode* sPtr);
void printList(ListNode* currentPtr);
void instructions(void);

int main(void)
{
    ListNode* startPtr = NULL; // initially there are no nodes
    char item; // char entered by user

    instructions(); // display the menu
    printf("%s", "? ");
    unsigned int choice; // user's choice
    scanf("%u", &choice);

    // loop while user does not choose 3
    while (choice != 3) {

        switch (choice) {
            case 1:
                printf("%s", "Enter a character: ");
                scanf("\n%c", &item);
                insert(&startPtr, item); // insert item in list
                printList(startPtr);
                break;
            case 2: // delete an element
                // if list is not empty
                if (!isEmpty(startPtr)) {
                    printf("%s", "Enter character to be deleted: ");
                    scanf("\n%c", &item);

                    // if character is found, remove it
                    if (delete(&startPtr, item)) { // remove item
                        printf("%c deleted.\n", item);
                        printList(startPtr);
                    }
                    else {
                        printf("%c not found.\n\n", item);
                    }
                }
                else {
                    puts("List is empty.\n");
                }

                break;
            default:
                puts("Invalid choice.\n");
                instructions();
                break;
        } // end switch

        printf("%s", "? ");
        scanf("%u", &choice);
    }

    puts("End of run.");
}

// display program instructions to user
void instructions(void)
{
    puts("Enter your choice:\n"
         "   1 to insert an element into the list.\n"
         "   2 to delete an element from the list.\n"
         "   3 to end.");
}

// insert a new value into the list in sorted order
void insert(ListNode* *sPtr, char value)
{

    ListNode* newPtr = malloc(sizeof(ListNode)); // create new node

    //Node created
    if (newPtr != NULL) { // is space available
        newPtr->data = value; // place value in node
        newPtr->nextPtr = NULL; // node does not link to another node

        // create structure pointer
        ListNode* previousPtr = NULL;
        //create structure pointer that points to the contents of sPtr, the first node
        //error found
        ListNode* currentPtr = *sPtr;
        // loop to find the correct location in the list
        while (currentPtr != NULL && value > currentPtr->data) {
            previousPtr = currentPtr; // walk to ...
            currentPtr = currentPtr->nextPtr; // ... next node
        }

        // insert new node at beginning of list
        if (previousPtr == NULL) {
            //set the new Nodes pointer to the contents of sPtr
            newPtr->nextPtr = *sPtr;
            //point sPtr to newPtr
            *sPtr = newPtr;
        }
        else { // insert new node between previousPtr and currentPtr
            // set the previousNodes pointer to point to newNode
            previousPtr->nextPtr = newPtr;
            //point newNode's pointer to the currentPtr
            newPtr->nextPtr = currentPtr;
        }
    }
    else {
        printf("%c not inserted. No memory available.\n", value);
    }
}

// delete a list element
char delete(ListNode* *sPtr, char value)
{
    // delete first node if a match is found
    if (value == (*sPtr)->data) {
        // create a tempNode that points to the first node
        ListNode* tempPtr = *sPtr; // hold onto node being removed
        // point sPtr to what the first node was pointing to
        *sPtr = (*sPtr)->nextPtr; // de-thread the node
        free(tempPtr); // free the de-threaded node
        return value;
    }
    else {
        ListNode* previousPtr = *sPtr;
        ListNode* currentPtr = (*sPtr)->nextPtr;

        // loop to find the correct location in the list
        while (currentPtr != NULL && currentPtr->data != value) {
            previousPtr = currentPtr; // walk to ...
            currentPtr = currentPtr->nextPtr; // ... next node
        }

        // delete node at currentPtr
        if (currentPtr != NULL) {
            ListNode* tempPtr = currentPtr;
            previousPtr->nextPtr = currentPtr->nextPtr;
            free(tempPtr);
            return value;
        }
    }

    return '\0';
}

// return 1 if the list is empty, 0 otherwise
int isEmpty(ListNode* sPtr)
{
    return sPtr == NULL;
}

// print the list
void printList(ListNode* currentPtr)
{
    // if list is empty
    if (isEmpty(currentPtr)) {
        puts("List is empty.\n");
    }
    else {
        puts("The list is:");

        // while not the end of the list
        while (currentPtr != NULL) {
            printf("%c --> ", currentPtr->data);
            currentPtr = currentPtr->nextPtr;
        }

        puts("NULL\n");
    }
}




/**************************************************************************
 * (C) Copyright 1992-2015 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 *************************************************************************/

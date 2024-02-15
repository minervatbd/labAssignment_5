#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	char letter;
	struct node* next;
} node;

// Returns number of nodes in the linkedList.
int length(node* head)
{
	int counter = 0;
	node* temp = head;

	// count until it gets to a null pointer
	while (temp != NULL) {
		counter++;
		temp = temp->next;
	}

	return counter;
}

// parses the string in the linkedList
//  if the linked list is head -> |a|->|b|->|c|
//  then toCString function wil return "abc"
char* toCString(node* head)
{
	// get length of the linked list for allocation purposes
	int len = length(head);

	node* temp = head;

	if (len != 0) {
		char* str = (char*)malloc(sizeof(char)*(len + 1));

		if (str == NULL) {
			return;
		}
		
		int x = 0;
		for (x = 0; x < len; x++) {
			str[x] = temp->letter;
			temp = temp->next; // assuming length was returned correctly, this loop should stop right when temp is assigned as NULL
		}
		str[x] = '\0'; // add null character at the end

		return str;
	}

}

// inserts character to the linkedlist
// f the linked list is head -> |a|->|b|->|c|
// then insertChar(&head, 'x') will update the linked list as foolows:
// head -> |a|->|b|->|c|->|x|
void insertChar(node** pHead, char c)
{
	// allocate a node
	node* newNode = (node*) malloc(sizeof(node));

	// make sure it was successfully allocated
    if (newNode == NULL) {
        return;
	}

    newNode->letter = c;
    newNode->next = NULL;

	node* temp = *pHead;

	// if we are given an empty linked list
	if (temp == NULL) {
		*pHead = newNode;
	}
	// if the linked list isnt empty
	else {
		// loop that adds newnode to the last place in the linked list
		int active = 1;
		while (active) {

			if (temp->next == NULL) {
				active--;
				temp->next = newNode;
			}
			else {
				temp = temp->next;
			}
		}

	}

    return;
}

// deletes all nodes in the linkedList.
void deleteList(node** pHead)
{
	node* temp = *pHead;

    while (temp != NULL)
    {
        *pHead = temp->next;
        free(temp);
        temp = *pHead;
    }

    *pHead = NULL;
}

int main(void)
{
	int i, strLen, numInputs;
	node* head = NULL;
	char* str;
	char c;
	FILE* inFile = fopen("input.txt","r");

	fscanf(inFile, " %d\n", &numInputs);
	
	while (numInputs-- > 0)
	{
		fscanf(inFile, " %d\n", &strLen);
		for (i = 0; i < strLen; i++)
		{
			fscanf(inFile," %c", &c);
			insertChar(&head, c);
		}

		str = toCString(head);
		printf("String is : %s\n", str);

		free(str);
		deleteList(&head);

		if (head != NULL)
		{
			printf("deleteList is not correct!");
			break;
		}
	}

	fclose(inFile);
}
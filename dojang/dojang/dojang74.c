/*#include<stdio.h>
#include<stdlib.h>
#pragma warning (disable:4996)

struct NODE {
	struct NODE* next;
	int data;
};

void addFirst(struct NODE* target, int data) {
	if (target == NULL) return;
	struct NODE* newNode = malloc(sizeof(struct NODE));
	if (newNode == NULL) return;
	newNode->next = target->next;
	newNode->data = data;
	target->next = newNode;
}

void removeFirst(struct NODE* target) {
	if (target == NULL) return;
	struct NODE* removeNODE = target->next;
	if (removeNODE == NULL) return;
	target->next = removeNODE->next;
	free(removeNODE);
}

struct NODE *headFirst( ) {
	struct NODE *head= malloc(sizeof(struct NODE));
	head->next = NULL;
	}

struct NODE* freeList(struct NODE *head) {
	struct NODE* curr = head->next;
	while (curr) {
		struct NODE* next = curr->next;
		free(curr);
		curr = next;
	}
	free(head);
}


struct NODE* findNode(struct NODE* node, int data)
{
	if (node == NULL) return NULL;
	struct NODE* curr = node->next;
	while (curr) {
		if (curr->data == data)
			return curr;
		curr = curr->next;
	}
	return NULL;

}

int main() {
	struct NODE* head= headFirst();

	addFirst(head, 10);
	addFirst(head, 20);
	addFirst(head, 30);
	
	removeFirst(head);

	struct NODE* curr = head->next;
	
	struct NODE* found = findNode(head, 10);
	printf("%d\n", found->data);

	while (curr) {
		printf("%d\n", curr->data);
		curr = curr->next;
	}
	
	freeList(head);
	
	return 0;
}
*/




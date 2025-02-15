/******************************************************************************
* arquivo: ArthurChimchekDiogoGuimaraes.c 31/05/2017
* autor: Arthur F. S. Chimchek e Diogo A. F. Guimar�es
* curso: Bacharelado em Sistemas de Informa��o
*******************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<stdbool.h>
#include<time.h>

typedef struct nodeQueue {
	int value;
	struct nodeQueue *next;
}node;

node *startPage, *page, *lastPage;

int popFront(node ** firstNode);
int getItem(node **);
int getQueueSize(node **firstNode);

bool queueHasValue(node **firstNode, int value);
void pushBack(node ** lastNode, int newValue);
void printQueue(node **firstNode);
void execute(int fileNumber, int totalPages);

void main() {
	clock_t start = clock();
	
	execute(1, 4);
	execute(2, 4);
	execute(3, 64);
	execute(3, 256);
	execute(3, 1024);
	execute(3, 2048);
	execute(4, 64);
	execute(4, 256);
	execute(4, 1024);
	execute(4, 2048);

	clock_t end = clock();
	double seconds = (double)(end - start)/CLOCKS_PER_SEC;
	printf("Total time: %f", seconds);
	scanf("");
}

void execute(int fileNumber, int totalPages) {
	clock_t startTime = clock();
	
	char fileName[15];
	sprintf(fileName, "tests/file%d.txt", fileNumber);
	
	int value, pageFaults, i;
	char req[10];
	node *currentNode, *firstNode;
	FILE *file;

	value = NULL;
	pageFaults = 0;

	file = fopen(fileName, "r");
	page = malloc(sizeof(struct nodeQueue));
	startPage = page;
	lastPage = page;
	startPage->value = value;
	fgets(req, 9, file);         			/* Le o arquivo */
	value = atoi(req);						/* Converte o string lido para inteiro */
	//printf("\nValor lido: %d", value);
	startPage->value = value;
	startPage->next = NULL;

	while (!feof(file))
	{
		fgets(req, 9, file);				/* Le o arquivo */
		if (!feof(file))					/* Verifica se � fim de arquivo */
		{
			value = atoi(req);
			//printf("\nValor lido: %d", value);

			page = malloc(sizeof(node)); 		/* Aloca nova p�gina na mem�ria  */
			page->value = value;

			lastPage->next = page;						/* Inclui a p�gina na estrutura */
			lastPage = page;
			page->next = NULL;
		}
	}
	page = startPage;

	
	
	currentNode = (node *)malloc(sizeof(node));;
	currentNode->value = page->value;
	currentNode->next = NULL;
	firstNode = (node*)currentNode;

	int queueSize = 1;
	while (page != NULL)
	{
		if (!queueHasValue(&firstNode, page->value)) {
			if (queueSize == totalPages) {
				//printf("\n\n%d\n\n", getQueueSize(&firstNode));
				popFront(&firstNode);
				pageFaults++;
				queueSize--;
			}
			pushBack(&currentNode, page->value);
			queueSize++;
		}
		//printf("\nValor pedido: %d", page->value);
		//printQueue(&firstNode);
		page = page->next;
	}
	
	clock_t endTime = clock();
	double timeTaken = (double)(endTime - startTime)/CLOCKS_PER_SEC;

	printf("%5d paginas, %7d requisicoes: FIFO: %5d Page Faults", totalPages, getQueueSize(&startPage), pageFaults);
	printf(". Time: %f\n", timeTaken);
}

bool queueHasValue(node **firstNode, int value) {
	node *temp;
	if (!firstNode == NULL) {
		node * firstNodeB = (*firstNode);
		temp = (node *)malloc(sizeof(node));
		temp = firstNodeB;
		while (temp != NULL) {
			if (temp->value == value)
				return true;
			temp = temp->next;
		}
	}
	return false;
}

void pushBack(node ** lastNode, int newValue) {
	node *newLastNode;
	if (lastNode == NULL) {
		newLastNode = (node *)malloc(sizeof(node));
		newLastNode = (*lastNode);
		newLastNode->value = newValue;
		newLastNode->next = NULL;
	}
	else {
		newLastNode = (node *)malloc(sizeof(node));
		newLastNode->value = newValue;
		newLastNode->next = NULL;
		(*lastNode)->next = newLastNode;
		(*lastNode) = newLastNode;
	}
}

int popFront(node ** firstNode) {
	if (firstNode == NULL || (*firstNode) == NULL)
		return;
	node *newFirstNode = (*firstNode)->next;
	int ret = (*firstNode)->value;
	(*firstNode) = newFirstNode;
	return ret;
}

int getQueueSize(node **firstNode) {
	if (firstNode == NULL || (*firstNode) == NULL)
		return 0;
	node *temp = (node *)malloc(sizeof(node));
	int count = 1;
	temp = (*firstNode)->next;
	while (temp != NULL)
	{
		temp = temp->next;
		count++;
	}
	return count;
}

void printQueue(node **firstNode) {
	node *temp;
	if (firstNode == NULL) {
		printf("\n\n --- Lista vazia !!!");
	}
	else {
		printf("\n\n --- ");
		node * firstNodeB = (*firstNode);
		temp = (node *)malloc(sizeof(node));
		temp = firstNodeB;
		while (temp != NULL) {
			printf("%d ", temp->value);
			temp = temp->next;
		}
		printf("\n");
	}
}

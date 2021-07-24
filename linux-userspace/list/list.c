#include "list.h"

PNODE pHead = NULL;

PNODE list_create_head(void)
{
	pHead = malloc(sizeof(NODE));
	
	if (pHead == NULL) {
		printf("%s, %d malloc failed!\n",__func__,__LINE__);
		exit(-1);
	}
	
	pHead->data = NULL;
	pHead->pNext = NULL;
	return pHead;
}

PNODE list_create_node(void data)
{
	PNODE pTmp;
	PNODE pNode;
	int i = 0;
	
	if (pHead == NULL) {
		printf("%s, %d pHead == NULL, please use list_create_head() first\n",__func__,__LINE__);
		exit(-1);
	}
	
	pNode = malloc(sizeof(NODE));
	if (pNode == NULL) {
		printf("%s, %d malloc failed!\n",__func__,__LINE__);
		exit(-1);
	}
	
	while (pHead->pNext != NULL) {
		pTmp = pHead->pNext++;
	}
	
	return pNode;
}

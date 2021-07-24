#ifndef __LIST_H__
#define __LIST_H__


typedef struct Node
{
    void data ;
	struct Node *pNext;
}NODE, *PNODE;

PNODE create_list_head(void);


#endif
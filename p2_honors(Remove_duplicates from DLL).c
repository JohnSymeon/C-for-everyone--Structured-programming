/*
This program creates a doubly linked list composed of nodes with random positive integer values,
and then implements the bubble sort algorithm with recursion to sort the list
from the smallest element to the largest. Then, it removes all duplicates by checking if adjacent
nodes have the same value.
~Ioannis Symeonidis
*/
#include <stdio.h>     
#include <stdlib.h> 
#include <time.h>
#define N 50//random numbers range

typedef struct node{ //Our basic node
	int data;
	struct node* next;
	struct node* prev;//previous node pointer
}Node;

typedef Node* List;  //typedefs to improve readability
typedef Node* Node_ptr; //
typedef Node* Tail; //

void Generate_List(List*,Tail*);//Used to generate the random list of 200 elements
void Create_Node(List*,Tail*,int);//Creates a node on the heap and sets it as head or the end of the list
void Sort_List(List*,Tail*,int);//Sorts the list from smallest to largest element, re-setting the tail
void Remove_Dup(List*,Tail*); //Removes all duplicates and re-sets the tail
void Print_List(List * list);//prints the list

int main(void)
{
	List mylist = NULL;
	Tail mytail = NULL;//end of the list sentinel
	Generate_List(&mylist,&mytail);
	puts("\nBefore Sorting");
	Print_List(&mylist);
	puts("\n\n\nAfter Sorting");
	Sort_List(&mylist,&mytail,200); //Sort
	Print_List(&mylist);
	Remove_Dup(&mylist,&mytail);//Remove duplicates
	puts("\n\n\nAfter Removing Duplicates");
	Print_List(&mylist);
}

void Remove_Dup(List* head, Tail* tail)
{
	Node_ptr temp = (*head);
	temp = temp->next;
	while(temp->next!=NULL)
	{
		if((temp->prev)->data==temp->data)
		{
			(temp->prev)->next = temp->next;//if we have same data, set the next of the previous as the current next
			(temp->next)->prev = temp->prev;//and se the current next's previous as the current previous
			Node_ptr to_be_freed = temp;
			temp= temp->next;//go to the next node
			free(to_be_freed);//and delete the duplicate from memory
		}
		else
			temp= temp->next;
	}
	if((temp->prev)->data==temp->data)//if the last node is a duplicate set the next of the prvious as NULL
		{
			*tail = temp->prev; //set the end setinel
			(temp->prev)->next = NULL;
			free(temp);//and delete the last node from memory
		}
	else
		*tail = temp; //else set the end sentinel at the current end
}
void Generate_List(List* myList,Tail* myTail)
{
	srand(time(0));
	int element;
	int i;
	for(i=0;i<200;i++) //Create as many nodes for as many elements are needed
	{
		element = rand()%N; //randomly generate an integer
		Create_Node(myList,myTail,element);
	}
}
void Create_Node(List* head,Tail* tail,int d)
{
	Node_ptr new_node= malloc(sizeof(Node));//initialise the new node on the heap
	new_node->data = d;
	new_node->next = NULL;
	new_node->prev = NULL;
	if((*head)==NULL) //check if the list is empty
	{
		(*head) = new_node;
		(*tail) = new_node;
	}
		
	else //else append the new node at the end
	{
		Node_ptr temp = (*head);
		while(temp->next!=NULL)
		{
			temp= temp->next;
		}
		temp->next = new_node;
		new_node->prev = temp;//set the previous node pointer
		(*tail) = new_node;
	}
}
void Sort_List(List* list,Tail* tail,int size)
{
	Node_ptr temp = (*list);
	List temp_head = (*list);//save the head of the list
	int i=0;
	if(size==0)//if the function has ran for N times, stop the recursion and rewind the tail of the list
	{
		while(temp->next!=NULL)
			temp=temp->next;
		(*tail) = temp;
		return;
	} 
		
	for(i=0;i<size-1;i++) 
	{
		//If an element is bigger than its next, swap the values.
		//Then move to the next pair, up until i reaches size-1.
		//Every time the function runs, the biggest value bubbles
		//at the front of the current active part of the list.
		//This occurs up until the active part becomes as small as one element.
		if( ( temp->data ) > ( (temp->next)->data )  )
			{
				int k = temp->data;
				(temp->data) = ( (temp->next)->data );
				(temp->next)->data = k;
			}
		temp = temp->next;
	}
	Sort_List(&temp_head,tail,size-1);
	
}
void Print_List(List * list)
{
	Node_ptr temp = (*list);
	int counter=0;
	//print all nodes up untl temp points to NULL
	while(temp!=NULL)
	{
		if(counter%5==0) //change lines every 5 nodes to improve readability
			puts("\n");
		printf("(%2d)-->", temp->data);
		temp= temp->next;
		counter++;
	}
}

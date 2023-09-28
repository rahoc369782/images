/*

Author : Rahul Darekar
Date : 03-08-2023
Desc : Implementation of linkedlist using c structures and pointers

*/

/*

* Adding node in list
* Deleting node in list
* Adding in center of list
 
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/syscall.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#define PRINT 'p'
#define INSERT 'i'
#define FIND 'f'
#define DELETE 'd'
#define EXIT 'e'

#define TRACE { printf("Linked list is initiated...\nAt moment %s %s \n",__DATE__ , __TIME__); }
#define DEL_TRACE { printf("Deleting nodes test initiated...\nAt moment %s %s \n",__DATE__ , __TIME__); }
#define TEST_PER 1



// Struct data is independent of linked list operations. It only handle data in flexible way.
struct n_data {
	int age; // 4 bytes
	char* n;
};
typedef struct n_data list_node_data;


/*

node struct is actuall node of linked list which hold pointer to next node of list as well as pointer to n_data struct.
Struct which represent node of linked list.

*/
typedef struct node list_node;

struct node {
	list_node_data *node_data;
	struct node *next;
};


struct list {
	struct node* h; // Head of LIST;
	struct node* t; // Tail of LIST;
	int  list_len; // Initially declare as 0;
};  

struct list* _list; // Declare global list pointer


void print_list() {
	// Print nodes of list through
	list_node* current_node;
	current_node = _list -> h;
	printf("\n-----------------------\n");
	while(current_node != NULL) {
		// Traverse the list
		printf("node %d -> " , current_node -> node_data -> age);
		current_node = current_node -> next;
	}
	printf("\n-----------------------\n\n");
}

list_node* search_node(void) {
	int n; // Overwriting this memory each time
	printf("Enter node value you want to search : ");
	scanf("%d",&n);
	fflush(stdin);
	
	list_node* curr = _list -> h;
	printf("Main list addr %p",curr);
	while(curr != NULL && n != curr -> node_data -> age) {
		// while n not matches with age and curr is there loop through it.
		curr = curr -> next;
	}
	printf("Found node value is %p",curr);
	return curr;
}

void add_node(list_node *node) {
	// Operation will execute on list location (pointer);
	char pos = 't';
	
	#if TEST_PER == 0
	printf("Where you want to add start or end? default to (start) : ");
	scanf("%c",&pos);
	#endif
	if(_list -> h == NULL) {
		// Head node of List
		_list -> h = node;
		_list -> t = node;
		_list -> list_len++;
	} else {
		if(pos == 's') {
			node -> next = _list -> h;
			_list -> h = node;
			_list -> list_len++;
		} else {
			_list ->t -> next = node;
			_list -> t = node;
			_list -> list_len++;
		}
	}
}

void delete_node(void) {
	int n;
	printf("Enter node value you want to delete : ");
	scanf("%d",&n);
	list_node* curr = _list -> h; // starting pointer of list
	list_node* pre = NULL;
	while(curr != NULL) {
		if(n == curr -> node_data -> age) {
			
			// found the node to be delete by value
			// attaching addr of next node pointer to previous node next poiter
			
			if(pre == NULL) {
				// first node of list is matched and need to delete
				_list -> h = curr -> next;
			} else {
				pre -> next = curr -> next;
				free(curr -> node_data);
				free(curr);
			}
			_list -> list_len--;
			break;
		}
		pre = curr;
		curr = curr -> next;
	}
}

// For performance purpose

void delete_node_test(int n) {
	list_node* curr = _list -> h; // starting pointer of list
	list_node* pre = NULL;
	while(curr != NULL) {
		if(n == curr -> node_data -> age) {
			
			// found the node to be delete by value
			// attaching addr of next node pointer to previous node next poiter
			
			if(pre == NULL) {
				// first node of list is matched and need to delete
				_list -> h = curr -> next;
			} else {
				pre -> next = curr -> next;
				// free(curr -> node_data);
				// free(curr);
			}
			_list -> list_len--;
			break;
		}
		pre = curr;
		curr = curr -> next;
	}
}



list_node* create_list_node(list_node_data *n) {
	/* 
	   Initiate new node in list 
	   With use of malloc 
	*/
	list_node *node = malloc(sizeof(list_node)); // 16 bytes
	node -> node_data = n;
	node -> next = NULL;
	return node;
}

void add_node_process(void) {
	int i_age; // Overwriting this memory each time
	printf("Enter node value you want to create : ");
	scanf("%d",&i_age);
	getchar();
	list_node_data *n = malloc(sizeof(list_node_data));
	n -> age = i_age;
	n -> n = NULL;
	list_node *node = create_list_node(n); // Return pointer to newly created list node 
	add_node(node);
}


// For test purpose of add node in list

void add_node_process_test(int i_age) {
	// int i_age;
	list_node_data *n = malloc(sizeof(list_node_data)); // 16 bytes
	n -> age = i_age;
	n -> n = NULL;
	list_node *node = create_list_node(n); // Return pointer to newly created list node 
	add_node(node);
}


int main() {
	_list = malloc(sizeof(*_list));
	_list -> h = NULL;
	_list -> t = NULL;
	_list -> list_len = 0;
	TRACE
	
	#if TEST_PER
	clock_t t , d;
    t = clock();
	for(int i = 0;i < 100000000; i++) {
		add_node_process_test(i);
	};
	t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
	printf("Time took %f seconds to execute \n", time_taken);
	
	#endif
	 // return 0;
	while (1) {
		char cmd;
		printf("\nType operatio to perform : ");
		scanf("%c",&cmd);
		fflush(stdin);
		switch(cmd) {
			case PRINT:
					printf("Main list is printed below...\n");
					print_list();
					break;
			case INSERT:
					add_node_process();
					printf("Node added successfully.\n");
					break;
		    case FIND:
					search_node();
					printf("Node Found successfully.\n");
					break;
			case DELETE:
					delete_node();
					printf("Node delete successfully.\n");
					break;
			case EXIT:
					printf("Programe exited successfully.\n");
					exit(0);
			default:
					printf("Command not found please check h for help.\n");
					break;
		};
		
		printf("Length of list is %d\n" , _list -> list_len );
	}
	
	return 0;
}

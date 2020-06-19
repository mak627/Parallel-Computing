#include <iostream>
#include <thread>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct node{
	int value;
	node *next;
};

class singly_linked_list{
		struct node *head,*tail;
	public:
		singly_linked_list(){
			head = NULL;
			tail = NULL;	
		}
		void insert_node(int new_val);
		void delete_node();
		void show_list();
};

//new node is inserted at the beginning of the SLL
void singly_linked_list::insert_node(int new_val){
	struct node *new_node = new node;
	new_node->value = new_val;
	if(head==NULL){
		new_node->next = NULL;
		head = new_node;
		tail = head;
		new_node = NULL;
	}
	else{
		new_node->next = head;
		head = new_node;
		new_node = NULL;	
	}
}

//deletion happens at the beginning of the SLL
void singly_linked_list::delete_node(){
	struct node *temp = new node;
	temp = head;
	head = head->next;
	delete temp;
}

//showing the singly linked list
void singly_linked_list::show_list(){
	struct node *temp = new node;
	temp = head;
	while(temp != NULL){
		cout << temp->value << " ";
		temp = temp->next;	
	}
	cout << endl;
}

int main(){
	
	auto start = high_resolution_clock::now();
	
	singly_linked_list sll1;	
	//Sequential Execution of two functions
	//sll1.insert_node(1);
	//sll1.insert_node(2);
	//sll1.insert_node(3);
	//sll1.delete_node();

	//Parallel Execution of two functions using threads
	//*****thread safety remains to be implemented*****
	thread t1(&singly_linked_list::insert_node,&sll1,1);
	thread t2(&singly_linked_list::insert_node,&sll1,2);
	thread t3(&singly_linked_list::insert_node,&sll1,3);
	thread t4(&singly_linked_list::delete_node,&sll1);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	sll1.show_list();
	
	auto stop = high_resolution_clock::now();
	auto time_diff = stop - start;
	cout << "Tot_Exec_Time:" << duration<double,micro> (time_diff).count() << "us" << endl;

	return 0;
}

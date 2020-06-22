#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;
using namespace std::chrono;
std::mutex mtx;
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
		bool search_node(int val);
		void show_list();
};

//new node is inserted at the beginning of the SLL
void singly_linked_list::insert_node(int new_val){
	struct node *new_node = new node;
	new_node->value = new_val;
	if(head==NULL){
		new_node->next = NULL;
		mtx.lock();
		head = new_node;
		tail = head;
		mtx.unlock();
		new_node = NULL;
	}
	else{
		new_node->next = head;
		mtx.lock();
		head = new_node;
		mtx.unlock();
		new_node = NULL;	
	}
}

//deletion happens at the beginning of the SLL
void singly_linked_list::delete_node(){
	struct node *temp = new node;
	temp = head;
	mtx.lock();
	head = head->next;
	mtx.unlock();
	delete temp;
}

//searching for a node with given value
bool singly_linked_list::search_node(int val){
	struct node *temp = head;
	while(temp!= NULL){
		cout << temp->value << endl;
		if(temp->value == val){ // node is found
			cout << "Node Found" << endl;
			return true; 
		}
		mtx.lock();
		temp = temp->next;
		mtx.unlock();	
	}
	cout << "Node Not Found" << endl;
	return false;
}

//showing the singly linked list
void singly_linked_list::show_list(){
	struct node *temp = new node;
	temp = head;
	mtx.lock();
	while(temp != NULL){
		cout << temp->value << " ";
		temp = temp->next;	
	}
	mtx.unlock();
	cout << endl;
}

int main(){
	
	auto start = high_resolution_clock::now();
	int search_val = 3;
	singly_linked_list sll1;	
	
	//Sequential Execution of three functions
	/*sll1.insert_node(1);
	sll1.insert_node(2);
	sll1.insert_node(3);
	sll1.search_node(head,search_val);
	sll1.delete_node();
	sll1.show_list();*/

	//Parallel Execution of two functions using threads
	thread t1(&singly_linked_list::insert_node,&sll1,1);
	thread t2(&singly_linked_list::insert_node,&sll1,2);
	thread t3(&singly_linked_list::insert_node,&sll1,3);
	thread t4(&singly_linked_list::search_node,&sll1,search_val);
	thread t5(&singly_linked_list::delete_node,&sll1);
	thread t6(&singly_linked_list::show_list,&sll1);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	
	auto stop = high_resolution_clock::now();
	auto time_diff = stop - start;
	cout << "Tot_Exec_Time:" << duration<double,micro> (time_diff).count() << "us" << endl;

	return 0;
}

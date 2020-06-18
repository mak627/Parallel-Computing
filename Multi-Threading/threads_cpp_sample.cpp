#include <iostream>
#include <thread>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct node{
	int value;
	node *next;
};

struct node *head = NULL;

void insert_node(int new_val){
	struct node* new_node = new node;
	new_node->value = new_val;
	new_node->next = head;
	head = new_node;
}

void delete_node(){
	struct node* temp = new node;
	temp = head;
	head = head->next;
	delete temp;
}

int main(){
	uint x=0, y=10000000;
	auto start = high_resolution_clock::now();
	//Parallel Execution of two functions using threads
	thread t1(findSum1,x,y);
	thread t2(findSum2,x,y);
	t1.join();
	t2.join();
	//Sequential Execution of two functions
	//findSum1(x,y);
	//findSum2(x,y);
	auto stop = high_resolution_clock::now();
	auto time_diff = stop - start;

	cout << "Sum1: " << sum1 << endl;
	cout << "Sum2: " << sum2 << endl;
	cout << "Tot_Exec_Time:" << duration<double,milli> (time_diff).count() << "ms" << endl;

	return 0;
}

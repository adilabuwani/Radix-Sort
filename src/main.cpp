//============================================================================
// Name        : RadixSort.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

class listNode{
public:
	int data;
	listNode* next;

	listNode(int d){
		this->data=d;
		this->next=NULL;
	}//end constructor

	//friends of these classes
	friend class linkedListStack;
	friend class linkedListQuene;
	friend class RadixSort;

}; //class listNode

class linkedListStack{

public:
	listNode* top;
	linkedListStack(){
		this->top=NULL;  //stack doesnot need a dummy node
	}

	linkedListStack(const linkedListStack* s){

		this->top=s->top;
	}

	void push(listNode* newNode){  //end push
		if(this->top==NULL){
			this->top=newNode; //if top is null, set to top
		}else{
			newNode->next=top;
			top=newNode;
		}
	}//end push

	listNode* pop(){

		if(top==NULL){
		return NULL;
		}
		listNode* temp;
		temp=top;        //set temp to top
		top=top->next;  //move top to next
		return temp;    //return the top
	}//end pop

	bool isEmpty(){
		return (this->top==NULL);
	}

	listNode* peak(){
		return top;
	}

	void printStack(linkedListStack* theStack, ofstream& outFile){

		linkedListStack* temp=theStack;

		outFile<<"Below is the output of the stack"<<endl;
		if(temp->top==NULL){
			outFile<<"Top -> NULL";

		}else{

		while(temp->top->next!=NULL){
			outFile<<"("<<temp->top->data<<", "<<temp->top->next->data<<")->";
			temp->top=temp->top->next;

		}//end while


		outFile<<"("<<temp->top->data<<", "<<"NULL) -> NULL";
		}

	}

};//end class

class linkedListQuene{

public:
	listNode* head;
	listNode* tail;

	linkedListQuene(){
		listNode* dummy;
		dummy= new listNode(-1); //listnode with a dummy -1 data
		this->head=dummy;
		this->tail=dummy;
	}//end linkedListQueue

void addTail(listNode* node){

	node->next=NULL;
	tail->next=node;
	tail=node;


}//end addTail

listNode* deleteFront(){
	listNode* temp;
	if(this->head->next==NULL){
		temp=NULL;
	}else{
    temp=head->next;
   this->head->next=this->head->next->next;
   if(head->next==NULL){
	   this->tail=head;
   }
   }//end else

   return temp;
}
bool isEmpty(){
	return(this->head->data==-1&&this->tail->data==-1); //is empty if the dummy are both -1
}//end isEmpty

void printQueue(int index, ofstream& outFile){

listNode* temp;
temp=this->head->next;
listNode* tempTail;
tempTail=this->tail;

outFile<<"Front ("<<index<<")->";

while(temp->next!=NULL){
	outFile<<"("<<temp->data<<", "<<temp->next->data<<")->";
	temp=temp->next;
}//end while
//last element
outFile<<"("<<temp->data<<", "<<"NULL) -> NULL"<<endl;

outFile<<"Tail ("<<index<<")->";

	outFile<<"("<<tempTail->data<<", "<<"NULL) -> NULL"<<endl;


}//end printQueue

void printQueueSorted(int index, ofstream& outFile){

	listNode* temp;
	temp=this->head->next;

	while(temp->next!=NULL){
		outFile<<temp->data<<", ";
		temp=temp->next;    //move temp to next
	}//end while
	//last element
	outFile<<temp->data<<endl;
}

friend class RadixSort;

};

class RadixSort{
public:
	int tableSize;
	linkedListQuene* hashTable[2][10];
    int data;
    int currentTable;   //for 0 or 1
    int previousTable;  //for 0 or 1
    int maxDigits;      //the LENGTH of the largest integer in the data
    int currentDigit;   //which digit we are currently looking at in sorting
    linkedListStack* theStack;
    int largestNum;


    RadixSort(){
    	this->tableSize=10;
    	this->largestNum=0;
    	this->previousTable=0;
    	this->currentTable=0;
    	this->maxDigits=0;
    	this->data=0;
    	this->currentDigit=0;
    	this->tableSize=10;
    	for (int r=0; r<2; r++){
    		for (int c=0; c<10; c++){
    			this->hashTable[r][c] = new linkedListQuene();
    			}
    	}

    	this->theStack= new linkedListStack();
    }//end constructor

    void loadStack(ifstream& inFile, ofstream& outFile){
    	linkedListStack* myStack;
    	myStack= new linkedListStack();  //top pointing to null
    	int largestNum=0;
    	int data;

    	if(inFile.is_open()){

    	while(inFile>>data){

    		if(data>=largestNum){
    			largestNum=data;
    		}//end if
    		//step3
    		listNode* myNode;
			myNode=new listNode(data);
			//push the data to the top
			myStack->push(myNode);
			this->theStack->push(myNode);
    	}//end while-repeat until eof baby

    	 myStack->printStack(myStack, outFile);  //printout myStack

    	 this->largestNum=largestNum;         //get the largestnum


    	}//end inFileis open

    }//loadStack

int getMaxDigits(int largestNum){
return ceil(log10(largestNum));
} //DonaldTRUMP cant figure this out!!

void printTable(int currentTable, ofstream& outfile){
		for (int i=0; i<10; i++){
			if (!this->hashTable[currentTable][i]->isEmpty()){  //the current index is not empty
				this->hashTable[currentTable][i]->printQueue(i, outfile);
			}
		}
	}//end printTable

void printTableSorted(int currentTable, ofstream& outfile){
		for (int i=0; i<10; i++){
			if (!this->hashTable[currentTable][i]->isEmpty()){  //the current index is not empty
				this->hashTable[currentTable][i]->printQueueSorted(i, outfile);
			}
		}
}//end printTable

void dumpStack(ofstream& outFile2){
	//move each digit from top of stack to to hashTable 0
	               while(!this->theStack->isEmpty()){
	            	   listNode* temp=this->theStack->pop();
	            	   int tempData=temp->data;
	            	   int digit=getDigit(tempData);               //returns the digit
	            	   int hashIndex=digit;

	                this->hashTable[this->currentTable][hashIndex]->addTail(temp); //add data to tail
	               } //repeat step 1 until not empty
	               this->printTable(this->currentTable, outFile2);
}
void radixSort(ofstream& outFile1, ofstream& outFile2){

//create hastTable
	createHashTable();
	//get maxDigits
	this->maxDigits=getMaxDigits(this->largestNum); //length of maxNum
    this->currentTable=0;
    this->dumpStack(outFile2);  //first iteration-currentDigit=1;
    this->currentDigit++;    //move currentDigit to next as one iteration is complete
    this->previousTable=0;  //prevTable
    this->currentTable=1;    //currentTable is now 1
    int currentQueue = 0;  //begin from first quque

    //move all the nodes from currentTable to currenttable



   while(this->currentDigit<=this->maxDigits){  //1<3

	   while(currentQueue<10){
		   while(! this->hashTable[this->previousTable][currentQueue]->isEmpty()){
			   listNode* node;
			   node=this->hashTable[this->previousTable][currentQueue]->deleteFront();
			   int digit=this->getDigit(node->data);
			   int hashIndex=digit;
			   this->hashTable[this->currentTable][hashIndex]->addTail(node);
		   }
		   currentQueue++;
	   }

	   if(this->currentDigit!=this->maxDigits){
		   this->printTable(this->currentTable, outFile2);
	   }//end if

	   int temp=this->currentTable;
	   this->currentTable=this->previousTable;
	   this->previousTable=temp;
	   currentQueue=0;
	   this->currentDigit++;

      }//end while

   //print sorted Data to outFile1
   this->printTableSorted(this->previousTable, outFile1);

}//end radixSort


int getDigit(int cd){
	  int digit=cd;
	for(int i=0;i<currentDigit; i++) {
		digit=digit/10;
	}
return digit % 10;
}

int hashIndex(int digit){
	return digit;
}

void createHashTable(){
	for (int r=0; r<2; r++){
	    for (int c=0; c<10; c++){
	    	this->hashTable[r][c] = new linkedListQuene();
	    	}
	    }
}//end createHashTable

};

int main(int argc, char**argv) {

	//step1
     ifstream inFile1;
     inFile1.open(argv[1]);
     ofstream outFile1;
     ofstream outFile2;
     outFile1.open(argv[2]);
     outFile2.open(argv[3]);

     //step2
     RadixSort* theRadixSort= new RadixSort();
     theRadixSort->loadStack(inFile1, outFile2);
     outFile2<<endl<<endl; //newLine
     theRadixSort->radixSort(outFile1, outFile2);

     //close all files
     inFile1.close();
     outFile1.close();
     outFile2.close();
	return 0;
}

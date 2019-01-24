# Radix-Sort

Algorithm steps for computing:
Algorithm steps in Main(…)

Step 1: inFile  open the input file 
	outFile1  open the out file 1
outFile2  open the out file 2

Step 2: loadStack (inFile, Top) // see algorithm below

Step 3: RadixSort (Top) // see algorithm below

Step 4: Output sorted data to outFile1

listNode  loadStack (inFile)

Step 1:	Top  create a new stack and let Top points to it
	 largestNum  0
  
Step 2: data  read a data from inFile
	If data > largestNum
	      largestNum  data // find the biggest positive number

Step 3: newNode <-- create a new listNode for the data
push (Top, newNode)  push newNode onto the top of the stack

step 4: repeat step 2 to step 3 until inFile is empty

step 5: call printStack (Top) // Print *** Below is the constructed stack ***
				// then the stack, see format in the above.

dumpStack ( *listNode Top, currentDigit, currentTable)

Step 1: // move each listNode from stack to hashTable[0]
- node  pop from the Top
- digit  getDigit (node, currentDigit) 
// get the currentDigit of the data in the node, make sure it returns a single digit 

- hashIndex  digit
- addTail (hashTable[currentTable][hashIndex], node) 
   // add the node at the tail of the queue at hashTable[currentTable][hashIndex]

Step 2: repeat step 1 until stack is empty

Step 3:  printTable (hashTable[currentTable]) // call printQueue to print none-empty queues in hashTable.

 
RadixSort (*listNode Top)

step 0: create hashTable[2][tableSize] 
// create each linked list queue array, the head and tail point to a dummy node.

maxDigits getMaxDigits (largestNum) // determine the length of largestNum 

Step 1: currentDigit  0 // the first digit/position from the right of the data.
  currentTable  0

Step 2: dumpStack ( *listNode Top, currentDigit, currentTable) 
// see the algorithm in the above

Step 3: - currentDigit++
- previousTable  0
- currentTable  1
- currentQueue  0

Step 4: // moving nodes from previous table to current table

node  deleteHead from the currentQueue in 
			hashTable[previousTable][currentQueue]

 digit  getDigit (node, currentDigit) 
// get the digit from the currentDigit of the data in the node

hashIndex  hashIndex (digit) 

addTail (hashTable[currentTable][hashIndex])
// add the node at the tail of the queue at hashTable[currentTable][hashIndex]

step 5:  repeat steps 4 until the currentQueue is empty
        
Step 6: currentQueue ++ // process the next queue in the previous hashTable

Step 7: repeat step 4  to step 6  until currentQueue >= tableSize - 1 

Step 8: printTable((hashTable[currentTable]) 

Step 9: temp  currentTable
currentTable  previousTable
previousTable temp
currentQueue  0

Step 10: repeat step 4 to step 9 while currentDigit  <  maxDigits

Step 11: printTable (hashTable[currentTable]) // print to outFile2
//call printQueue to print none-empty queues in hashTable.

Step 12: Close all files

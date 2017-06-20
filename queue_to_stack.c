/*Challenge 2 */

#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

typedef struct {
	int size;
	int top;
	char *array;
} Stack;

Stack *stackCreate() {
	/*allocate memmory for stack struct and for the array, 
	  can create a desired sized stack by giving input arg int size and assign it to stack -> size*/

	Stack *stack = malloc(sizeof(Stack));
	
	stack -> size = SIZE;
	stack -> top = stack -> size - 1;
	stack -> array = (char *) malloc(sizeof(char) * stack -> size);
	
	return stack;
}

void stackDestroy(Stack *stack) {
	/*free the stack and null the reference to it*/

	free(stack -> array);
	stack = NULL;
	free(stack);	
}

int stackIsEmpty(Stack *stack) {
	/*if stack is empty (no data inside) return 1 otherwise return 0*/

	if(stack -> size - 1 == (stack -> top)) {
		return 1;
	}
	return 0;
}

int stackIsFull(Stack *stack) {
	/*check whether the stack is full. if true return 1 otherwise 0*/

	if(stack -> top == 0) {
		return 1;
	}
	return 0;
}

int stackPush(Stack *stack, char data) {
	/*push the data element input with arg data. if the push success will return 0 otherwise -1*/

	if(!stackIsFull(stack)) {		
		(stack -> array)[stack -> top] = data;		
		stack -> top --;
		
		return 0;
	}
	return -1;	
}

int stackPop(Stack *stack, char *data) {
	/*pass the pop value to the input arg *data of the function if the pop is success
	  function will return 0 otherwise -1 anda data will be null*/

	if (!stackIsEmpty(stack)) {
		*data = (stack -> array)[stack -> top + 1];
		(stack -> array)[stack -> top + 1] = '\0';
		stack -> top ++;

		return 0;
	}
	
	*data = '\0';
	return -1;
}

char stackPeek(Stack *stack) {
	/*return the copy of the top element of the stack. if there is no element to return will return null*/
	
	if (stackIsEmpty(stack)) {
		return '\0';
	} else if (stackIsFull(stack)) {
		return (stack -> array)[stack -> top + 1];
	} else {
		return (stack -> array)[stack -> top];
	}
}

typedef struct {
	Stack *stack1;
	Stack *stack2;
} Queue;

Queue *queueCreate() {
	Queue *queue = malloc(sizeof(Queue));

	queue -> stack1 = stackCreate();
	queue -> stack2 = stackCreate();

	return queue;
}

void queueDestroy(Queue *queue) {
	stackDestroy(queue -> stack1);
	stackDestroy(queue -> stack2);
}

int queueIsEmpty(Queue *queue) {
	if (stackIsEmpty(queue -> stack1) && stackIsEmpty(queue -> stack2)) {
		return 1;
	}

	return 0;
}

int queueIsFull(Queue *queue) {
	return stackIsFull(queue -> stack1); 
}

int enqueue(Queue *queue, char data) {
	if (!queueIsFull(queue)) {
		/*push all data to stack 1 only*/
		stackPush(queue -> stack1, data);

		return 0;
	}

	return -1;
}

int dequeue(Queue *queue, char *data) {
	if (!queueIsEmpty(queue)) {
		while (!stackIsEmpty(queue -> stack1)) {
			char c;

			/*pop fron one stack and fill to other stack to get the last one first*/
			stackPop(queue -> stack1, &c);
			stackPush(queue -> stack2, c);
		}

		stackPop(queue -> stack2, data);

		return 0;
	}

	*data = '\0';
	return -1;	
}

char queuePeek(Queue *queue) {
	return stackPeek(queue -> stack1);
}

int queueToStack(Queue *queue, Stack *stack) {
	/*add queue data to a stack and push stack data again to wanted stack*/

	Stack *temp_stack = stackCreate();

	while (!queueIsEmpty(queue)) {
		char c;
		dequeue(queue, &c);
		stackPush(temp_stack, c);
	}

	while (!stackIsEmpty(temp_stack)) {
		char c;
		stackPop(temp_stack, &c);
		stackPush(stack, c);
	}

	if (queueIsEmpty(queue)) {
		return 0;
	}

	return -1;
}

int main() {
	Queue *queue1 = queueCreate();
	Stack *stack1 = stackCreate();

	enqueue(queue1, 'a');
	enqueue(queue1, 'b');
	enqueue(queue1, 'c');
	enqueue(queue1, 'd');

	queueToStack(queue1, stack1);

	char c;

	stackPop(stack1, &c); printf("pop data = %c\n", c);
	stackPop(stack1, &c); printf("pop data = %c\n", c);

	queueDestroy(queue1);
	stackDestroy(stack1);
		
	return 0;	
}
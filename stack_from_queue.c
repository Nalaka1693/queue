/*Challenge 3 */

#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

typedef struct {
	int size;
	int s_size;
	int top;
	char *array;
} Stack;

Stack *stackCreate() {
	/*allocate memmory for stack struct and for the array, 
	  can create a desired sized stack by giving input arg int size and assign it to stack -> size*/

	Stack *stack = malloc(sizeof(Stack));
	
	stack -> size = SIZE;
	stack -> s_size = 0;
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
		//printf("stack push top = %d\n", stack -> top);
		(stack -> array)[stack -> top] = data;
		stack -> s_size ++;		
		stack -> top --;
		
		return 0;
	}
	return -1;	
}

int stackPop(Stack *stack, char *data) {
	/*pass the pop value to the input arg *data of the function if the pop is success
	  function will return 0 otherwise -1 anda data will be null*/

	if (!stackIsEmpty(stack)) {
		//printf("stack pop top = %d\n", stack -> top);

		*data = (stack -> array)[stack -> top + 1];
		stack -> s_size --;		
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct {
	int q_size;
	Stack *stack1;
	Stack *stack2;
} Queue;

Queue *queueCreate() {
	Queue *queue = malloc(sizeof(Queue));

	queue -> q_size = 0;
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
		queue -> q_size ++;

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
		queue -> q_size --;

		return 0;
	}

	*data = '\0';
	return -1;	
}

char queuePeek(Queue *queue) {
	return stackPeek(queue -> stack1);
}

int queueToStack(Queue *queue, Stack *stack) {
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct {
	Queue *queue1;
	Queue *queue2;
} StackFromQueue;

StackFromQueue *stackFromQueueCreate() {
	StackFromQueue *stackFromQueue = malloc(sizeof(StackFromQueue));

	stackFromQueue -> queue1 = queueCreate();
	stackFromQueue -> queue2 = queueCreate();

	return stackFromQueue;
}

void stackFromQueueDestroy(StackFromQueue *stackFromQueue) {
	queueDestroy(stackFromQueue -> queue1);
	queueDestroy(stackFromQueue -> queue2);
}

int stackFromQueueIsEmpty(StackFromQueue *stackFromQueue) {
	if (queueIsEmpty(stackFromQueue -> queue1)) {
		return 1;
	}

	return 0; 
}

int stackFromQueueIsFull(StackFromQueue *stackFromQueue) {
	if (queueIsFull(stackFromQueue -> queue1)) {
		return 1;
	}

	return 0;
}

int stackFromQueuePush(StackFromQueue *stackFromQueue, char data) {
	if (!stackFromQueueIsFull(stackFromQueue)) {
		enqueue(stackFromQueue -> queue1, data);
	}
	
	return 0;
}

int stackFromQueuePop(StackFromQueue *stackFromQueue, char *data) {
	if (!stackFromQueueIsEmpty(stackFromQueue)) {

		while ((stackFromQueue -> queue1) -> q_size != 1) {
			/*dequeue from q1 untill it left only one element and fill the q2 with others, then dequeue the left element and return*/

			char c;
			dequeue(stackFromQueue -> queue1, &c);
			enqueue(stackFromQueue -> queue2, c);
		}

		char out;
		dequeue(stackFromQueue -> queue1, &out);
		*data = out;

		Queue *tempQueue;

		/*change references to two ques so that avoid fill back again*/
		tempQueue = stackFromQueue -> queue1;
		stackFromQueue -> queue1 = stackFromQueue -> queue2;
		stackFromQueue -> queue2 = tempQueue;

		return 0;
	}
	
	*data = '\0';
	return -1;
}

char stackFromQueuePeek(StackFromQueue *stackFromQueue) {
	return queuePeek(stackFromQueue -> queue1);
}

int main() {
	StackFromQueue *stackFromQueue = stackFromQueueCreate();

	printf("\nPush values\n");
	printf("Push = %c\n", 'a');
	printf("Push = %c\n", 'b');
	printf("Push = %c\n", 'c');
	printf("Push = %c\n", 'd');

	stackFromQueuePush(stackFromQueue, 'a');
	stackFromQueuePush(stackFromQueue, 'b');
	stackFromQueuePush(stackFromQueue, 'c');
	stackFromQueuePush(stackFromQueue, 'd');

	char c;

	printf("\nPop values\n");
	stackFromQueuePop(stackFromQueue, &c); printf("Pop = %c\n", c);
	stackFromQueuePop(stackFromQueue, &c); printf("Pop = %c\n", c);
	stackFromQueuePop(stackFromQueue, &c); printf("Pop = %c\n", c);
	stackFromQueuePop(stackFromQueue, &c); printf("Pop = %c\n", c);

	stackFromQueueDestroy(stackFromQueue);
		
	return 0;	
}
#include "queue.h"

int main(void) {
	Queue qq;
	Queue_T q;

	int val1, val2, val3, val4, val5;
	val1 = 1;
	val2 = 2;
	val3 = 3;
	val4 = 4;
	val5 = 5;

	q = &qq;
	Queue_init(q);
	Queue_enqueue(q, (void *)&val1);
	Queue_enqueue(q, (void *)&val2);
	Queue_enqueue(q, (void *)&val3);
	Queue_enqueue(q, (void *)&val4);
	Queue_enqueue(q, (void *)&val5);
	
	ASSERT(*(int *)Queue_dequeue(q) == 1);
	ASSERT(*(int *)Queue_dequeue(q) == 2);
	ASSERT(*(int *)Queue_dequeue(q) == 3);
	ASSERT(*(int *)Queue_dequeue(q) == 4);
	ASSERT(*(int *)Queue_dequeue(q) == 5);
	return 0;
}

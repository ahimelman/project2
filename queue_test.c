#include "queue.h"

int main(void) {
	Queue qq;
	Queue_T q;

	int i, val1, val2, val3, val4, val5;
	val1 = 1;
	val2 = 2;
	val3 = 3;
	val4 = 4;
	val5 = 5;

	q = &qq;
	Queue_init(q);
	
	ASSERT(Queue_is_empty(q));	

	for (i = 0; i < 4; i++) {
		Queue_enqueue(q, (void *)&val1);	
		ASSERT(q->size == 1);
		Queue_enqueue(q, (void *)&val2);
		ASSERT(q->size == 2);
		Queue_enqueue(q, (void *)&val3);
		ASSERT(q->size == 3);
		Queue_enqueue(q, (void *)&val4);
		ASSERT(q->size == 4);
		Queue_enqueue(q, (void *)&val5);
		ASSERT(q->size == 5);
		
		ASSERT(*(int *)Queue_dequeue(q) == 1);
		ASSERT(q->size == 4);
		ASSERT(*(int *)Queue_dequeue(q) == 2);
		ASSERT(q->size == 3);
		ASSERT(*(int *)Queue_dequeue(q) == 3);
                ASSERT(q->size == 2);
	        ASSERT(*(int *)Queue_dequeue(q) == 4);
		ASSERT(q->size == 1);
		ASSERT(*(int *)Queue_dequeue(q) == 5);
		ASSERT(q->size == 0);
	
		ASSERT(Queue_is_empty(q));	
	}

	Queue_enqueue(q, (void *)&val1);
	ASSERT(*(int *)Queue_dequeue(q) == 1);

	ASSERT(Queue_is_empty(q));	
	
	return 0;
}

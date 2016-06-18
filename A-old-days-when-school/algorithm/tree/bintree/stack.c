#include "stack.h"
#include "list.h"

int stack_push(Stack *stack, const void *data)
{
	return list_insert_next(stack, NULL, data);
}

int stack_pop(Stack *stack)
{
	return list_remove_next(stack, NULL, NULL);
}

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// The stack definition.
// A stack has a fixed maximal size.
struct uint_stack
{
  unsigned int size;
	unsigned int* values;
	unsigned int nb_elements;
};

typedef struct uint_stack uint_stack_t;

// Create a new stack of size nb.
// Return NULL if the creation didn't succeed (for a lack of memory)
uint_stack_t* uint_stack_create(size_t nb)
{
  // Allocate the new table of values
	unsigned int* values = malloc(sizeof(unsigned int)*nb);
	
	// Did the allocation succeed ?
	if (values == NULL)
	{
		// Error of allocation (lack of memory)
		return NULL;
	}
		
	// Allocate the new stack
	uint_stack_t* stack = malloc(sizeof(uint_stack_t));
		
	// Did the stack allocation succeed ?
	if(stack == NULL)
	{
		free(values);
		return NULL;
	}
		
	// Everything is OK	
	// Init the table of values
	for (unsigned int i = 0; i < nb; ++i)
	{
		values[i] = 0;
	}
	
	stack -> size = nb;
	stack -> values = values;
	stack -> nb_elements = 0;
	
	return stack;
}

// Free the memory used by a stack.
// After this call, the free'd stack can no longer be used.
void uint_stack_destroy(uint_stack_t* stack)
{
  free(stack->values);
	free(stack);
}

// Copy src into dst.
// Return -1 if src is too big to be copied into dst, 0 otherwise.
/* int uint_stack_copy(uint_stack_t* src, uint_stack_t* dst)
{
  // Is the stack src too big to be copied into dst ?
	if(src->size > dst->size)
	{
		return -1;
	}
	
	else
	{
		// All values in dst are deleted
		dst->values = NULL;
		dst->nb_elements = 0;
		
		// Values of src copied in dst
		for(unsigned int i=0; i<src->size; ++i)
		{
			dst->values[i] = src->values[i];
		}
		
		// Update of the new nb_elements for the stack dst
		dst->nb_elements = src->nb_elements;
		
		// Everything is OK
		return 0;
	}
} */

// Swap the content of two stacks.
/* void uint_stack_swap(uint_stack_t* stack1, uint_stack_t* stack2)
{
  // TO DO
} */

// Push a value.
// If the stack is full, it's not modified.
// Return 0 if the stack wasn't full, -1 otherwise.
int uint_stack_push(uint_stack_t* stack, unsigned int element)
{
  // Is the stack full ?
	if(stack->nb_elements == stack->size)
	{
		return -1;
	}
	
	else
	{
		stack->values[stack->nb_elements] = element;
		stack->nb_elements++; 
		
		// Everything is OK
		return 0;
	}
}

// Pop a value.
// If the stack is empty, it's not modified.
// Return 0 if the stack wasn't empty, -1 otherwise.
int uint_stack_pop(uint_stack_t* stack, unsigned int* element)
{
  // Is the stack empty ?
	if(stack->nb_elements == 0)
	{
		return -1;
	}
	
	else
	{
		stack->nb_elements--;
		*element = stack->values[stack->nb_elements];
		
		// Everything is OK
		return 0; 
	}
}

// Return the size of a stack.
// This is the actual number of stored elements, not the maximal size.
size_t uint_stack_size(uint_stack_t* stack)
{
  return stack->nb_elements;
}

/* ------------------------------------------------------- */

// Keep the number of failed tests.
size_t nb_failures = 0;

// Check if the given test has passed or not.
#define CHECK( test_passed )                 \
{                                            \
  if (!((test_passed)))                      \
  {                                          \
    ++nb_failures;                           \
    printf("Failure line %u \n", __LINE__);  \
  }                                          \
}

/* ------------------------------------------------------- */

int main(int argc, char** argv)
{
  // Check the uniqueness of created stacks.
  {
    uint_stack_t* stack1 = uint_stack_create(5);
    uint_stack_t* stack2 = uint_stack_create(5);
    
    CHECK((stack1 != stack2));
    
    uint_stack_destroy(stack1);
    uint_stack_destroy(stack2);
  
	} 
  // Check a simple push()/pop().
  {
    uint_stack_t* stack = uint_stack_create(5);
    CHECK(uint_stack_size(stack) == 0);

    uint_stack_push(stack, 42);
    CHECK(uint_stack_size(stack) == 1);

    unsigned int value;
    uint_stack_pop(stack, &value);
    CHECK(uint_stack_size(stack) == 0);
    CHECK(value == 42);

    uint_stack_destroy(stack);
  }

  // Test with a stack of size 1.
  {
    uint_stack_t* stack = uint_stack_create(1);

    uint_stack_push(stack, 101);
    CHECK(uint_stack_size(stack) == 1);

    unsigned int value;
    CHECK(uint_stack_pop(stack, &value) == 0);
    CHECK(value == 101);
    CHECK(uint_stack_size(stack) == 0);
    uint_stack_destroy(stack);    
  }

  // Check multiple push()/pop().
  {
    uint_stack_t* stack = uint_stack_create(10);

    size_t i = 0;
    for (i = 0; i < 10; ++i)
    {
      CHECK(uint_stack_push(stack, i) == 0);
    }
    CHECK(uint_stack_size(stack) == 10);

    for (i = 10; i > 0; --i)
    {
      unsigned int value;
      CHECK(uint_stack_pop(stack, &value) == 0);
      CHECK(value == (i-1));
    }
    CHECK(uint_stack_size(stack) == 0);

    uint_stack_destroy(stack);
  }

  // Check that push() doesn't modify a full stack.
  {
    uint_stack_t* stack = uint_stack_create(10);

    size_t i = 0;
    for (i = 0; i < 10; ++i)
    {
      uint_stack_push(stack, i);
    }
    CHECK(uint_stack_size(stack) == 10);

    for (i = 0; i < 10; ++i)
    {
      CHECK(uint_stack_push(stack, i) == -1);
      CHECK(uint_stack_size(stack) == 10);
    }

    uint_stack_destroy(stack);
  }

  // Test swap().
  /* {
    unsigned int value;

    uint_stack_t* stack1 = uint_stack_create(5);
    uint_stack_t* stack2 = uint_stack_create(5);
    
    uint_stack_push(stack1, 0);
    uint_stack_push(stack1, 2);
    CHECK(uint_stack_size(stack1) == 2);
    
    uint_stack_push(stack2, 3);
    CHECK(uint_stack_size(stack2) == 1);

    uint_stack_swap(stack1, stack2);

    CHECK(uint_stack_size(stack1) == 1);
    CHECK(uint_stack_pop(stack1, &value) == 0);
    CHECK(value == 3);

    CHECK(uint_stack_size(stack2) == 2);
    CHECK(uint_stack_pop(stack2, &value) == 0);
    CHECK(value == 2);
    CHECK(uint_stack_pop(stack2, &value) == 0);
    CHECK(value == 0);

    uint_stack_destroy(stack1);
    uint_stack_destroy(stack2);
  } */

  // Test copy().
  /* {
    unsigned int value;

    uint_stack_t* stack1 = uint_stack_create(5);
    uint_stack_t* stack2 = uint_stack_create(3);

    uint_stack_push(stack1, 0);
    uint_stack_push(stack1, 2);
    CHECK(uint_stack_size(stack1) == 2);
    
    uint_stack_push(stack2, 3);
    CHECK(uint_stack_size(stack2) == 1);

    uint_stack_copy(stack2, stack1);

    CHECK(uint_stack_size(stack1) == 1);
    CHECK(uint_stack_pop(stack1, &value) == 0);
    CHECK(value == 3);

    CHECK(uint_stack_size(stack2) == 1);
    CHECK(uint_stack_pop(stack2, &value) == 0);
    CHECK(value == 3);

    uint_stack_destroy(stack1);
    uint_stack_destroy(stack2);
  } */

	// Number of failures.
  printf("%lu failure(s)\n", nb_failures);
  
  return EXIT_SUCCESS;
}

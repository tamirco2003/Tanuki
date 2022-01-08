#include <stddef.h>

typedef struct _list_t {
	unsigned int length;
    unsigned int capacity;
	size_t obj_size;
	void* array;
} List_t;

List_t List_CreateList(size_t obj_size);
void List_Push(void* value);
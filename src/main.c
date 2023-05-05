#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct Node {
	void *data;
	uintptr_t n_xor_p;
};

struct List {
	struct Node* head;
	struct Node* tail;
	size_t data_size;
};

struct Node* get_node(void* data) {
	struct Node* node = malloc(sizeof(struct Node));

	node->data = data;
	node->n_xor_p = 0;

	return node;
}

struct List* init_gen_linked_list(size_t data_size) {
	struct List* list = malloc(sizeof(struct List));

	list->head = NULL;
	list->tail = NULL;
	list->data_size = data_size;

	return list;
}

/* [.] <-> [.] <-> [.]
 *  a       b       c 
 *  b      a^c      b
 */

/* After popping
 *
 *  [.] <-> [.]
 *   b       c 
 *   c       b
 */

void pop(struct List* list) {
	if (list->head == NULL) {
		return;
	}

	if (!list->head->n_xor_p) {
		free(list->head);

		list->head = NULL;
		list->tail = NULL;

		return;
	}

	struct Node* a = list->head;
	struct Node* b = (struct Node*) a->n_xor_p;

	b->n_xor_p = (uintptr_t) a ^ b->n_xor_p;
	list->head = b;

	free(a);
}

/*  [.] <-> [.]
 *   b       c 
 *   c       b
 */

/* After pushing
 *
 *  [.] <-> [.] <-> [.]
 *   x       b       c 
 *   b      x^c      b
 */

void prepend(struct List* list, void* data) {
	struct Node* node = get_node(data);

	if (list->head == NULL) {
		list->head = node;
		list->tail = node;
		return;
	}

	list->head->n_xor_p ^= (uintptr_t) node;
	node->n_xor_p = (uintptr_t) list->head;
	list->head = node;
}

void print_list(struct Node* t, void (*print)(void*)) {
	if (t == NULL) {
		printf("[]\n");
		return;
	}

	uintptr_t prev = 0;

	printf("[ ");

	while (t) {
		print(t->data);
		printf(" ");

		uintptr_t prev_t = (uintptr_t) t;
		t = (struct Node*) (prev ^ t->n_xor_p);
		prev = prev_t;
	}

	printf("]\n");
}

void print_int(void* integer) {
	printf("%d", *((int*) integer));
}

void print_string(void* string) {
	printf("%s", (char*) string);
}

int main(void) {
	struct List* numbers = init_gen_linked_list(sizeof(int));
	struct List* names = init_gen_linked_list(sizeof(char*));
	int nums[] = {1, 2, 3};

	char* viewers[] = {
		"daneelsan",
		"Zeeshan",
		"James",
		"Julestelliot",
		"Mohammad",
	};

	for (int i = 0; i < sizeof(viewers) / sizeof(char*); i++) {
		prepend(names, viewers[i]);
	}

	for (int i = 0; i < sizeof(nums) / sizeof(int); i++) {
		prepend(numbers, &nums[i]);
	}

	print_list(numbers->head, print_int);

	pop(numbers);
	pop(names);

	struct List* empty = init_gen_linked_list(sizeof(int));

	print_list(numbers->head, print_int);
	print_list(names->head, print_string);
	print_list(empty->head, print_int);
	print_list(names->tail, print_string);
}

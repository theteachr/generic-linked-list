#include <stdio.h>
#include <stdlib.h>

struct Node {
	void *data;
	struct Node* next;
};

struct GenLinkedList {
	struct Node* head;
	size_t data_size;
};

struct Node* get_node(void* data) {
	struct Node* node = malloc(sizeof(struct Node));

	node->data = data;
	node->next = NULL;

	return node;
}

struct GenLinkedList* init_gen_linked_list(size_t data_size) {
	struct GenLinkedList* list = malloc(sizeof(struct GenLinkedList));

	list->head = get_node(NULL);
	list->data_size = data_size;

	return list;
}

void pop(struct GenLinkedList* list) {
	if (list->head->next == NULL) {
		return;
	}

	struct Node* node = list->head->next;
	list->head->next = node->next;

	free(node);
}

void prepend(struct GenLinkedList* list, void* data) {
	struct Node* node = get_node(data);

	node->next = list->head->next;
	list->head->next = node;
}

void print_list(struct GenLinkedList* list, void (*print)(void*)) {
	if (list->head->next == NULL) {
		printf("[]\n");
		return;
	}

	struct Node* t = list->head->next;

	printf("[");

	while (t->next) {
		print(t->data);
		printf(", ");
		t = t->next;
	}

	print(t->data);
	printf("]\n");
}

void print_int(void* integer) {
	printf("%d", *((int*) integer));
}

void print_string(void* string) {
	printf("%s", (char*) string);
}

int main(void) {
	struct GenLinkedList* numbers = init_gen_linked_list(sizeof(int));
	struct GenLinkedList* names = init_gen_linked_list(sizeof(char*));
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

	pop(numbers);
	pop(names);

	print_list(numbers, print_int);
	print_list(names, print_string);
	print_list(init_gen_linked_list(sizeof(int)), print_int);
}

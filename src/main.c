#include <stdint.h>
#include <stdio.h>

struct node {
	struct node* prev;
	struct node* next;
	uint8_t data;
};

int main() {
	const char* data = "ABCDEFGGGABS";
	
	uint8_t freq_array[256] = { 0 };
	uint8_t freq_next_ptr_array[256] = { 0 };

	uint8_t next_ptr_array[256] = { 0 };
	uint8_t prev_ptr_array[256] = { 0 };

	uint8_t sorted_array_size = 0;

	uint8_t root = 0;
	
	for (int i =  0; data[i] != '\0'; i++) {
		if (freq_array[data[i]] == 0) {
			sorted_array_size += 1;
		}

		// if (i == 0) {
		// 	root = data[i];
		// 	next_ptr_array[data[i]] = data[i];
		// } else {
		// 	uint8_t next = root;

		// 	// while (freq_array[data[i]] >= freq_array[next]) {
		// 	// 	next = next_ptr_array[next];
		// 	// }

		// 	// next_ptr_array[data[i]] = next;
		// }

		// prev_ptr_array[data[i]] = freq_next_ptr_array[freq_array[data[i]]];
		// next_ptr_array[data[i]] = next_ptr_array[freq_next_ptr_array[freq_array[data[i]]]];
		// freq_next_ptr_array[freq_array[data[i]]] = 

		// if (freq_array[data[i]] == 0) {
		// 	next_ptr_array[data[i]] = root;
		// 	prev_ptr_array[root] = data[i];
		// 	root = data[i];
		// } else {
		// 	if (freq_array[data[i]] >= freq_array[next_ptr_array[data[i]]]) {
		// 		uint8_t p_a = prev_ptr_array[data[i]];
		// 		uint8_t p_b = data[i];
		// 		uint8_t p_c = next_ptr_array[data[i]];
		// 		uint8_t p_d = next_ptr_array[next_ptr_array[data[i]]];

		// 		if (freq_array[p_c]) {
		// 			prev_ptr_array[p_b] = p_c;
		// 			prev_ptr_array[p_c] = p_a;
		// 			prev_ptr_array[p_d] = p_b;
					
		// 			next_ptr_array[p_a] = p_c;
		// 			next_ptr_array[p_b] = p_d;
		// 			next_ptr_array[p_c] = p_b;

		// 			printf("%c - %c - %c - %c\n", p_a, p_b, p_c, p_d);
	
		// 			if (data[i] == root) {
		// 				root = p_c;
		// 			}
		// 		}
		// 	}
		// }

		// uint8_t next = root;
		// for (int i = 0; i < sorted_array_size; i++) {
		// 	if (i != 0)
		// 		printf(" -> ");
		// 	printf("%c", next);
		// 	next = next_ptr_array[next];
		// }
		// printf("\n");

		freq_array[data[i]] += 1;
	}
	
	printf("sorted array size - %i\n", sorted_array_size);
	printf("smallest - %c\n", root);
	
	for (int i = 0; i < 256; i++) {
		if (freq_array[i]) {
			printf("%c - %i - %c - %c\n", i, freq_array[i], prev_ptr_array[i], next_ptr_array[i]);
		}
	}
	// uint8_t next = root;
	// for (int i = 0; i < sorted_array_size; i++) {
	// 	if (i != 0)
	// 		printf(" -> ");
	// 	printf("%c", next);
	// 	next = next_ptr_array[next];
	// }
	// printf("\n");
}
#include <stdint.h>
#include <stdio.h>

#define create_element(data, code, freq) ()

struct node {
	uint16_t tag;
	uint16_t data;
	uint16_t freq;
};

void swap_u16(uint16_t* a, uint16_t* b) {
	uint16_t tmp = *a;
	*a = *b;
	*b = tmp;
}

void swap_node(struct node* a, struct node* b) {
	swap_u16(&a->data, &b->data);
	swap_u16(&a->freq, &b->freq);
	swap_u16(&a->tag, &b->tag);
}

void print_bin(int val) {
	static int index = 0;
	static uint8_t array[256];
	
	if (val == 0) {
		printf("%i", val);

		return;
	}

	while (val) {
		array[index++] = val & 1;
		val = val >> 1;
	}

	for (int i = 0; i < index; i++) {
		printf("%i", array[index - i - 1]);
	}

	index = 0;
}

void traverse(const struct node* root, uint16_t* result_array, uint16_t* result_array_idx, int index, int level, int id) {
	if (index >= 0) {
		if (root[index].tag) {
			traverse(root, result_array, result_array_idx, root[index].data & 255, level + 1, (id << 1) | 1);

			for (int i = 0; i < level; i++) {
				printf("\t");
			}

			// printf("%i", root[index].freq);

			printf("%i", root[index].freq);
			printf(" [");
			// print_bin(root[index].tag);
			print_bin(id);
			printf("]");
			// printf(" (");
			// print_bin(id);
			// printf(")");
			printf("\n");

			traverse(root, result_array, result_array_idx, root[index].data >> 8, level + 1, id << 1);
		} else {
			for (int i = 0; i < level; i++) {
				printf("\t");
			}

			printf("| %c - %i", root[index].data, root[index].freq);

			result_array[(*result_array_idx)++] = (id << 8) | root[index].data;

			printf(" [");
			// print_bin(root[index].tag);
			print_bin(id);
			printf("]");
			
			printf("\n");
		}

	}
}

int main() {
	const char* data = "ABCDEFGGGABS";
	
	uint16_t idx_array[256] = { 0 };

	struct node condensed_array[2 * 256 - 1] = { 0 };

	uint8_t condensed_array_idx = 0;

	for (int i =  0; data[i] != '\0'; i++) {
		if (condensed_array[idx_array[data[i]]].data != data[i]) {
			condensed_array[condensed_array_idx].data = data[i];
			condensed_array[condensed_array_idx].tag = 0;

			idx_array[data[i]] = condensed_array_idx++;
		}

		condensed_array[idx_array[data[i]]].freq++;
	}

	printf("---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- \n");
	
	printf("sorted array size - %i\n", condensed_array_idx);

	for (int i = 0; i < condensed_array_idx; i++) {
		for (int j = i + 1; j < condensed_array_idx; j++) {
			if (condensed_array[j].freq <= condensed_array[i].freq) {
				swap_node(&condensed_array[j], &condensed_array[i]);
			}
		}

		if (i & 1) {
			condensed_array[condensed_array_idx].data = ((i - 1) << 8) | i;
			condensed_array[condensed_array_idx].freq = condensed_array[i - 1].freq + condensed_array[i].freq;
			condensed_array[condensed_array_idx].tag = condensed_array[i - 1].tag + condensed_array[i].tag + 1;
			condensed_array_idx++;
		}
	}

	printf("---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- \n");

	printf("tree array size - %i\n", condensed_array_idx);

	printf("---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- \n");

	for (int i = 0; i < condensed_array_idx; i++) {
		printf("%i: ", i);
		if (condensed_array[i].tag) {
			printf("%i - %i : %i\n", condensed_array[i].data >> 8, condensed_array[i].data & 255, condensed_array[i].freq);
		} else {
			printf("%c : %i\n", condensed_array[i].data, condensed_array[i].freq);
		}
	}

	printf("---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- \n");

	uint16_t result_array[512];
	uint16_t result_array_idx = 0;

	traverse(condensed_array, result_array, &result_array_idx, condensed_array_idx - 1, 0, 1);

	printf("---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- \n");

	for (int i = 0; i < result_array_idx; i++) {
		if (result_array[i]) {
			printf("%c - ", result_array[i] & 255);
			print_bin(result_array[i] >> 8);
			printf("\n");
		}
	}
	
	print_bin(255 * 255);
	
	printf("\n---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- \n");
}
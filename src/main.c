#include <stdint.h>
#include <stdio.h>

struct node {
	uint16_t leaf;
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
	swap_u16(&a->leaf, &b->leaf);
	swap_u16(&a->tag, &b->tag);
}

// void traversal(struct node* array, uint8_t index) {
// 	// if (index > 1) {
// 	// 	printf("\t%i\n", array[array[index - 1].data >> 8].freq);
// 	// 	traversal(array, index - 1);
// 	// 	printf("\t%i\n", array[array[index - 1].data & 255].freq);
// 	// }
// }

void traverse(struct node* root, int index, int level) {
	if (index >= 0) {

		if (root[index].leaf == 0) {
			traverse(root, root[index].data & 255, level + 1);

			for (int i = 0; i < level; i++) {
				printf("\t");
			}

			printf("%i\n", root[index].freq);

			traverse(root, root[index].data >> 8, level + 1);
		} else {
			for (int i = 0; i < level; i++) {
				printf("\t");
			}
			
			printf("%c - %i\n", root[index].data, root[index].freq);
		}

	}
}

int main() {
	const char* data = "ABCDEFGGGABS";
	
	uint8_t idx_array[256] = { 0 };
	
	struct node condensed_array[256] = { 0 };
	
	uint8_t condensed_array_idx = 0;

	for (int i =  0; data[i] != '\0'; i++) {
		if (condensed_array[idx_array[data[i]]].data != data[i]) {
			condensed_array[condensed_array_idx].data = data[i];
			condensed_array[condensed_array_idx].leaf = 1;
			condensed_array[condensed_array_idx].tag = 0;

			idx_array[data[i]] = condensed_array_idx++;
		}

		condensed_array[idx_array[data[i]]].freq++;
	}
	
	// for (int i = 0; i < condensed_array_idx; i++)	{
	// 	printf("%c = %i\n", condensed_array[i].data, condensed_array[i].freq);
	// }
	
	printf("sorted array size - %i\n", condensed_array_idx);


	for (int i = 0; i < condensed_array_idx; i++) {
		for (int j = i + 1; j < condensed_array_idx; j++) {
			if (condensed_array[j].freq <= condensed_array[i].freq) {
				swap_node(&condensed_array[j], &condensed_array[i]);
			}
		}

		if (i & 1) {
			condensed_array[condensed_array_idx].leaf = 0;
			condensed_array[condensed_array_idx].data = ((i - 1) << 8) | i;
			condensed_array[condensed_array_idx].freq = condensed_array[i - 1].freq + condensed_array[i].freq;
			condensed_array[condensed_array_idx].tag = condensed_array[i - 1].tag + condensed_array[i].tag + 1;
			condensed_array_idx++;
		}
	}

	// uint8_t non_leaf_idx = 0;

	// for (uint8_t i = 1; i < condensed_array_idx - 1; i += 2) {
	// 	if (condensed_array[i].freq <= condensed_array[condensed_array_idx - 1].freq || i == 1) {
	// 		condensed_array[condensed_array_idx].leaf = 0;
	// 		condensed_array[condensed_array_idx].data = ((i - 1) << 8) | i;
	// 		condensed_array[condensed_array_idx].freq = condensed_array[i - 1].freq + condensed_array[i].freq;
	// 		condensed_array_idx += 1;
	// 	} else {
	// 		condensed_array[condensed_array_idx].leaf = 0;
	// 		condensed_array[condensed_array_idx].data = ((i - 1) << 8) | (condensed_array_idx - 1);
	// 		condensed_array[condensed_array_idx].freq = condensed_array[i - 1].freq + condensed_array[condensed_array_idx - 1].freq;
	// 		condensed_array_idx += 1;
	// 	}
	// }

	// condensed_array[condensed_array_idx].leaf = 0;
	// condensed_array[condensed_array_idx].data = ((condensed_array_idx - 2) << 8) | (condensed_array_idx - 1);
	// condensed_array[condensed_array_idx].freq = condensed_array[condensed_array_idx - 2].freq + condensed_array[condensed_array_idx - 1].freq;
	// condensed_array_idx++;

	for (int i = 0; i < condensed_array_idx; i++)	{
		if (condensed_array[i].leaf == 1) {
			printf("\t%i\t %c     = %i\n", i, condensed_array[i].data, condensed_array[i].freq);
		} else {
			printf("\t%i\t %i - %i: %i = %i\n", i, (condensed_array[i].data >> 8) & 255, condensed_array[i].data & 255, condensed_array[i].tag, condensed_array[i].freq);
		}
	}

	printf("tree array size - %i\n", condensed_array_idx);

	traverse(condensed_array, condensed_array_idx - 1, 0);
	// struct node root = 
}
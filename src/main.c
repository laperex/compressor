#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// to print data as char
// remove when using raw bytes ( non char based data )
#define PRINT_AS_CHAR

// change depending on data length
#define DATA_SIZE (12)


#ifdef PRINT_AS_CHAR
	#define NODE_PRINT "%c"
#else
	#define NODE_PRINT "%i"
#endif

#define FREQ_BIT ((256 * 256) - 1)

void swap_u32(uint32_t* a, uint32_t* b) {
	uint32_t tmp = *a;
	*a = *b;
	*b = tmp;
}

void print_bin(int val, uint32_t def) {
	static int index = 0;
	static uint8_t array[256];

	while (val || def != 0) {
		array[index++] = val & 1;
		val = val >> 1;
		
		if (def != 0) {
			def--;
		}
	}

	for (int i = 0; i < index; i++) {
		printf("%i", array[index - i - 1]);
	}

	index = 0;
}

void traverse(const uint32_t* root, uint16_t* result_array, int index, int level, int id) {
	if (index >= 0) {
		if ((root[index] >> 16) & 1) {
			// printf("%i", root[index] >> 17);
			traverse(root, result_array, (root[index] >> 17) + 1, level + 1, (id << 1) | 1);

			for (int i = 0; i < level; i++) {
				printf("\t");
			}

			// printf("%i", root[index].freq);

			printf("%i", root[index] & FREQ_BIT);
			printf(" [");
			// print_bin(root[index].tag, 0);
			print_bin(id, 0);
			printf("]");
			// printf(" (");
			// print_bin(id, 0);
			// printf(")");
			printf("\n");

			traverse(root, result_array, (root[index] >> 17), level + 1, id << 1);
		} else {
			for (int i = 0; i < level; i++) {
				printf("\t");
			}

			printf("| " NODE_PRINT " - %i", root[index] >> 17, root[index] & FREQ_BIT);

			result_array[root[index] >> 17] = id;

			printf(" [");
			// print_bin(root[index].tag, 0);
			print_bin(id, 0);
			printf("]");

			printf("\n");
		}
	}
}


uint32_t init_tree_array(uint8_t* data, uint16_t* tree_index_array, uint32_t* tree_array, uint32_t* tree_array_idx) {
	uint32_t i;

	for (i =  0; i < DATA_SIZE; i++) {
		if ((tree_array[tree_index_array[data[i]]] >> 17) != data[i]) {
			tree_array[*tree_array_idx] = (data[i] << 17);

			tree_index_array[data[i]] = (*tree_array_idx)++;
		}

		tree_array[tree_index_array[data[i]]]++;
	}
	
	return i;
}

void create_tree_nodes(uint32_t* tree_array, uint32_t* tree_array_idx) {
	// typical selection sort algorithm
	// tree nodes are inserted during the runtime of the loop to increase performance

	// O((N * (N - 1)) / 2) performance
	// where N is the total size of the array including the tree nodes and tree leafs at the end of the loop
	// N = 2n - 1 where n is the total count of leaf nodes
	
	for (int i = 0; i < *tree_array_idx; i++) {
		for (int j = i + 1; j < *tree_array_idx; j++) {
			if ((tree_array[j] & FREQ_BIT) <= (tree_array[i] & FREQ_BIT)) {
				swap_u32(&tree_array[j], &tree_array[i]);
			}
		}

		if (i & 1) {
			tree_array[(*tree_array_idx)++] = ((i - 1) << 17) | (1 << 16) | ((tree_array[i - 1] & FREQ_BIT) + (tree_array[i] & FREQ_BIT));
		}
	}
}

int main() {
	uint8_t data[DATA_SIZE] = "ABCDEFGGGABS";
	
	// for (uint32_t i = 0; i < DATA_SIZE; i++) {
	// 	data[i] = i % 64;
	// }

	uint16_t id_array[256] = { 0 };
	
	uint16_t tree_index_array[256] = { 0 };
	uint32_t tree_array[2 * 256 - 1] = { 0 };
	uint32_t tree_array_idx = 0;
	
	// creates a contiguous array, mapping each unique byte to their frequency count.
	// initialize the tree array with the tree leafs sorted in ascending order of their frequency
	uint32_t data_size = init_tree_array(data, tree_index_array, tree_array, &tree_array_idx);
	
	uint32_t leaf_count = tree_array_idx;

	// create tree nodes
	create_tree_nodes(tree_array, &tree_array_idx);

	printf("---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- \n");
	
	printf("huffman tree: array view\n\n");
	printf("huffman tree array size: %i\n", tree_array_idx);
	printf("huffman tree leaf count: %i\n\n", leaf_count);

	for (int i = 0; i < tree_array_idx; i++) {
		printf("%i: ", i);
		if ((tree_array[i] >> 16) & 1) {
			printf("%i - %i : %i\n", tree_array[i] >> 17, (tree_array[i] >> 17) + 1, tree_array[i] & FREQ_BIT);
		} else {
			printf("(%c) : %i\n", tree_array[i] >> 17, tree_array[i] & FREQ_BIT);
		}
	}

	// printf("---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- \n");
	printf("\n");

	for (int i = 0; i < tree_array_idx; i++) {
		printf("%i,", tree_array[i]);
	}
	printf("\n");

	printf("---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- \n");

	printf("huffman tree: tree view\n\n");

	// recursively travese the tree array and determine the huffman code
	// id_array - stores the huffman code, each unique byte acts as index to this array
	traverse(tree_array, id_array, tree_array_idx - 1, 0, 1);

	printf("---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- \n");
	
	printf("huffman code\n\n");

	for (int i = 0; i < 256; i++) {
		if (id_array[i]) {
			printf("(" NODE_PRINT ") - ", i);
			if (id_array[i] > 511) {
				printf(" [T] ");
			}
			print_bin(id_array[i], 0);
			printf("\n");
		}
	}

	printf("---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- \n");
	
	//* ----------------------| COMPRESSION | 

	uint64_t i_bit = 0;
	uint8_t store_array[DATA_SIZE] = { 0 };

	// convert the bytes in the given data to huffman codes of varying sizes
	for (uint32_t index = 0; index < DATA_SIZE; index++) {
		for (uint32_t j = 0; j < 20; j++) {
			if (id_array[data[index]] >> j == 1) {
				for (uint8_t k = 0; k < j; k++) {
					store_array[i_bit >> 3] |= ((id_array[data[index]] >> (j - k - 1)) & 1) << (8 - (i_bit % 8) - 1);
					i_bit += 1;
				}
			}
		}
	}

	printf("compressed data\n\n");
	for (int i = 0; i < (i_bit >> 3); i++) {
		print_bin(store_array[i], 8);
	}
	printf("\n");

	printf("---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- \n");

	printf("uncompressed data\n\n");
	for (int i = 0; i < DATA_SIZE; i++) {
		print_bin(data[i], 8);
	}
	printf("\n");


	//* ----------------------| DECOMPRESSION | 

	uint64_t pos = tree_array_idx - 1;
	uint8_t final_result[DATA_SIZE] = { 0 };
	uint32_t final_result_index = 0;

	for (int i = 0; i < i_bit; i++) {
		if ((tree_array[pos] >> 16) & 1) {
			pos = (tree_array[pos] >> 17) + ((store_array[i >> 3] >> ((8 - (i % 8)) - 1)) & 1);

			if (((tree_array[pos] >> 16) & 1) == 0) {
				final_result[final_result_index++] = tree_array[pos] >> 17;
				pos = tree_array_idx - 1;
			}
		}
	}
	
	for (int i = 0; i < data_size; i++) {
		if (data[i] != final_result[i] || (final_result_index != data_size)) {
			printf("---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- \n");
			printf("MATCH INCORRECT!\n");
			printf("---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- \n");

			return 1;
		}
	}
	
	printf("---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- \n");
	
	float ratio = (1 - ((float)(i_bit >> 3) / (float)(data_size))) * 100;
	printf("data_size = %i\n", data_size);
	printf("comp_size = %lu\n", (i_bit >> 3));
	printf("compression ratio = %.2f%\n", ratio);
	printf("---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- \n");

	// uint32_t stack[256 / 2] = { 0 };
	// uint32_t stack_ptr = 0;
	// uint32_t curr_pos = tree_array_idx - 1;
	// u_int64_t id = 0;
	
	// while (1) {
	// 	if ((tree_array[curr_pos] >> 16) & 1) {
	// 		stack[stack_ptr++] = (tree_array[curr_pos] >> 16) | 1;
	// 	} else {
	// 		curr_pos = stack[--stack_ptr] >> 1;
	// 	}
	// }

	// for (int i = 0; i < 256; i++) {
	// 	if (id_array[i]) {
	// 		printf("(%i) - ", i);
	// 		if (id_array[i] > 511) {
	// 			printf(" [T] ");
	// 		}
	// 		print_bin(id_array[i], 0);
	// 		printf("\n");
	// 	}
	// }

	// printf("---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- \n");
}

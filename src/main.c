#include <stdint.h>
#include <stdio.h>

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

			printf("| %i - %i", root[index] >> 17, root[index] & FREQ_BIT);

			result_array[root[index] >> 17] = id;

			printf(" [");
			// print_bin(root[index].tag, 0);
			print_bin(id, 0);
			printf("]");

			printf("\n");
		}
	}
}

#define DATA_SIZE (1000)

int main() {
	uint8_t data[DATA_SIZE] = "2e1284e1243                       q";
	
	for (uint32_t i = 0; i < DATA_SIZE; i++) {
		data[i] = (i + 1) % 256;
	}

	uint32_t data_size = 0;
	
	uint16_t idx_array[256] = { 0 };

	uint32_t condensed_array[2 * 256 - 1] = { 0 };

	uint32_t condensed_array_idx = 0;

	for (int i =  0; i < DATA_SIZE; i++) {
		if ((condensed_array[idx_array[data[i]]] >> 17) != data[i]) {
			condensed_array[condensed_array_idx] = (data[i] << 17);

			idx_array[data[i]] = condensed_array_idx++;
		}

		condensed_array[idx_array[data[i]]]++;

		data_size++;
	}

	printf("---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- \n");

	printf("sorted array size - %i\n", condensed_array_idx);
	
	// uint16_t leaf_count = condensed_array_idx;

	for (int i = 0; i < condensed_array_idx; i++) {
		for (int j = i + 1; j < condensed_array_idx; j++) {
			// printf("i %i | j = %i\n", i, j);
			if ((condensed_array[j] & FREQ_BIT) <= (condensed_array[i] & FREQ_BIT)) {
				swap_u32(&condensed_array[j], &condensed_array[i]);
				// printf("i %i | j = %i\n", i, j);
			}
		}

		if (i & 1) {
			condensed_array[condensed_array_idx++] = ((i - 1) << 17) | (1 << 16) | ((condensed_array[i - 1] & FREQ_BIT) + (condensed_array[i] & FREQ_BIT));
		}
	}

	printf("---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- \n");

	printf("tree array size - %i\n", condensed_array_idx);

	printf("---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- \n");

	for (int i = 0; i < condensed_array_idx; i++) {
		printf("%i: ", i);
		if ((condensed_array[i] >> 16) & 1) {
			printf("%i - %i : %i\n", condensed_array[i] >> 17, (condensed_array[i] >> 17) + 1, condensed_array[i] & FREQ_BIT);
		} else {
			printf("(%i) : %i\n", condensed_array[i] >> 17, condensed_array[i] & FREQ_BIT);
		}
	}

	for (int i = 0; i < condensed_array_idx; i++) {
		printf("%i,", condensed_array[i]);
	}
	printf("\n");

	printf("---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- \n");

	uint16_t id_array[256] = { 0 };

	traverse(condensed_array, id_array, condensed_array_idx - 1, 0, 1);

	printf("---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- \n");

	for (int i = 0; i < 256; i++) {
		if (id_array[i]) {
			printf("(%i) - ", i);
			if (id_array[i] > 511) {
				printf(" [T] ");
			}
			print_bin(id_array[i], 0);
			printf("\n");
		}
	}

	printf("---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- \n");

	// uint32_t val = result_array[data[index]];

	// uint32_t v = 511;

	uint64_t bit_i = 0;
	uint8_t store_array[1000000] = { 0 };
	uint64_t len = 0;

	{

		for (uint32_t index = 0; index < DATA_SIZE; index++) {
			for (uint32_t j = 0; j < 20; j++) {
				if (id_array[data[index]] >> j == 1) {
					for (uint8_t k = 0; k < j; k++) {
						store_array[bit_i >> 3] |= ((id_array[data[index]] >> (j - k - 1)) & 1) << (8 - (bit_i % 8) - 1);
						bit_i += 1;
					}
				}
			}
		}

		for (int i = 0; i < (bit_i >> 3); i++) {
			print_bin(store_array[i], 8);
		}
		
		printf("\nsize = %lu\n", (bit_i - 1) >> 3);
		
		len = bit_i;
	}

	uint64_t pos = condensed_array_idx - 1;
	printf("%s\n", data);
	for (int i = 0; i < DATA_SIZE; i++) {
		print_bin(data[i], 8);
	}
	
	printf("\n");
	
	uint8_t final_result[100000] = { 0 };
	int final_result_index = 0;

	for (int i = 0; i < len; i++) {
		// printf("%i %i\n", pos, ((store_array[i >> 3] >> ((8 - (i % 8)) - 1)) & 1));

		if ((condensed_array[pos] >> 16) & 1) {
			pos = (condensed_array[pos] >> 17) + ((store_array[i >> 3] >> ((8 - (i % 8)) - 1)) & 1);

			if (((condensed_array[pos] >> 16) & 1) == 0) {
				final_result[final_result_index++] = condensed_array[pos] >> 17;
				pos = condensed_array_idx - 1;
			}
		}
		// printf("%i\n", (store_array[i >> 3] >> ((8 - (i % 8)) - 1)) & 1);
	}
	
	
	printf("---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- \n");
	
	// printf("%s\n", final_result);
	
	for (int i = 0; i < final_result_index; i++) {
		if (data[i] != final_result[i]) {
			printf("\nincorrect!");
			break;
		} else {
			printf("%c", final_result[i]);
		}
	}
	printf("\n");
	
	// printf("%i - %i\n", final_result_index, data_size);
	
	printf("---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- \n");
	
	float ratio = (1 - ((float)(bit_i >> 3) / (float)(data_size))) * 100;
	printf("data_size = %i\n", data_size);
	printf("comp_size = %lu\n", (bit_i >> 3));
	printf("compression ratio = %.2f%\n", ratio);
	printf("---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- \n");

}

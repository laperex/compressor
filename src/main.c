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

			printf("| %c - %i", root[index] >> 17, root[index] & FREQ_BIT);

			result_array[root[index] >> 17] = id;

			printf(" [");
			// print_bin(root[index].tag, 0);
			print_bin(id, 0);
			printf("]");

			printf("\n");
		}
	}
}

int main() {
	const char* data = "ABCD237y6428fhweahofurawheuitrhwioautryolsegnsliurngvfiuvbudsgrftyasfksbfdvsbkeufyba75yr2dkljfhjhafnjeh49376ygb8uehbg7esvtgry478w354ytnbyreuighbw735yvgthuisehnvghi7yt34w87ebtgh4u7weyftnh7wcyesngfcsbys745EFGGGABSsdjisaiodjafndsfnosdnofisdsfjkwheurgtihaifmsniaesulrtgoaiwulnefcsjdgfaesyrfvjnABCD237y642875yr2dkljfhjhafnjeh49376ygb8uehbg7esvtgry478w354ytnbyreuighbw735yvgthuisehnvghi7ytABCD237y642875yr2dkljfhjhafnjeh49376ygb8uehbg7esvtgry478w354ytnbyreuighbw735yvgthuisehnvghi7yt34w87ebtgh4u7weyftnh7wcyesngfcsbys745EFGGGABSsdjisaiodjafndsfnosdnofisdsfjkwheurgtihaifmsniaesulrtgoaiwulnefcsjdgfaesyrfvjnABCD237y642875yr2dkljfhjhafnjeh49376ygb8uehbg7esvtgry478w354ytnbyreuighbw735yvgthuisehnvghi7yt34w87ebtgh4u7weyftnh7wcyesngfcsbys745EFGGGABSsdjisaiodjafndsfnosdnofisdsfjkwheurgtihaifmsniaesulrtgoaiwulnefcsjdgfaesyrfvjn34w87ebtgh4u7weyftnh7wcyesngfcsbys745EFGGGABSsdjisaiodjafndsfnosdnofisdsfjkwheurgtihaifmsniaesulrtgoaiwulnefc            sjdgfaesyrfvjn dsjgfhawkygf  fetew     oidfiqueahrgtiouh212376242375245y213hrufwhekjdsnfib43yt73e4yt534hwruhfwjerf3845y2ABCD237y642875yr2dkljfhjhafnjeh49376ygb8uehbg7esvtgry478w354ytnbyreuighbw735yvgthuisehnvghi7yt34w87ebtgh4u7weyftnh7wcyesngfcsbys745EFGGGABSsdjisaiodjafndsfnosdnofisdsfjkwheurgtihaifmsniaesulrtgoaiwulnefcsjdgfaesyrfvjnABCD237y642875yr2dkljfhjhafnjeh49376ygb8uehbg7esvtgry478w354ytnbyreuighbw735yvgthuisehnvghi7ytABCD237y642875yr2dkljfhjhafnjeh49376ygb8uehbg7esvtgry478w354ytnbyreuighbw735yvgthuisehnvghi7yt34w87ebtgh4u7weyftnh7wcyesngfcsbys745EFGGGABSsdjisaiodjafndsfnosdnofisdsfjkwheurgtihaifmsniaesulrtgoaiwulnefcsjdgfaesyrfvjnABCD237y642875yr2dkljfhjhafnjeh49376ygb8uehbg7esvtgry478w354ytnbyreuighbw735yvgthuisehnvghi7yt34w87ebtgh4u7weyftnh7wcyesngfcsbys745EFGGGABSsdjisaiodjafndsfnosdnofisdsfjkwheurgtihaifmsniaesulrtgoaiwulnefcsjdgfaesyrfvjn34w87ebtgh4u7weyftnh7wcyesngfcsbys745EFGGGABSsdjisaiodjafndsfnosdnofisdsfjkwheurgtihaifmsniaesulrtgoaiwulnefc            sjdgfaesyrfvjn dsjgfhawkygf  fetew     oidfiqueahrgtiouh212376242375245y213hrufwhekjdsnfib43yt73e4yt534hwruhfwjerf3845y2ABCD237y642875yr2dkljfhjhafnjeh49376ygb8uehbg7esvtgry478w354ytnbyreuighbw735yvgthuisehnvghi7yt34w87ebtgh4u7weyftnh7wcyesngfcsbys745EFGGGABSsdjisaiodjafndsfnosdnofisdsfjkwheurgtihaifmsniaesulrtgoaiwulnefcsjdgfaesyrfvjnABCD237y642875yr2dkljfhjhafnjeh49376ygb8uehbg7esvtgry478w354ytnbyreuighbw735yvgthuisehnvghi7ytABCD237y642875yr2dkljfhjhafnjeh49376ygb8uehbg7esvtgry478w354ytnbyreuighbw735yvgthuisehnvghi7yt34w87ebtgh4u7weyftnh7wcyesngfcsbys745EFGGGABSsdjisaiodjafndsfnosdnofisdsfjkwheurgtihaifmsniaesulrtgoaiwulnefcsjdgfaesyrfvjnABCD237y642875yr2dkljfhjhafnjeh49376ygb8uehbg7esvtgry478w354ytnbyreuighbw735yvgthuisehnvghi7yt34w87ebtgh4u7weyftnh7wcyesngfcsbys745EFGGGABSsdjisaiodjafndsfnosdnofisdsfjkwheurgtihaifmsniaesulrtgoaiwulnefcsjdgfaesyrfvjn34w87ebtgh4u7weyftnh7wcyesngfcsbys745EFGGGABSsdjisaiodjafndsfnosdnofisdsfjkwheurgtihaifmsniaesulrtgoaiwulnefc            sjdgfaesyrfvjn dsjgfhawkygf  fetew     oidfiqueahrgtiouh212376242375245y213hrufwhekjdsnfib43yt73e4yt534hwruhfwjerf3845y2ABCD237y642875yr2dkljfhjhafnjeh49376ygb8uehbg7esvtgry478w354ytnbyreuighbw735yvgthuisehnvghi7yt34w87ebtgh4u7weyftnh7wcyesngfcsbys745EFGGGABSsdjisaiodjafndsfnosdnofisdsfjkwheurgtihaifmsniaesulrtgoaiwulnefcsjdgfaesyrfvjnABCD237y642875yr2dkljfhjhafnjeh49376ygb8uehbg7esvtgry478w354ytnbyreuighbw735yvgthuisehnvghi7ytABCD237y642875yr2dkljfhjhafnjeh49376ygb8uehbg7esvtgry478w354ytnbyreuighbw735yvgthuisehnvghi7yt34w87ebtgh4u7weyftnh7wcyesngfcsbys745EFGGGABSsdjisaiodjafndsfnosdnofisdsfjkwheurgtihaifmsniaesulrtgoaiwulnefcsjdgfaesyrfvjnABCD237y642875yr2dkljfhjhafnjeh49376ygb8uehbg7esvtgry478w354ytnbyreuighbw735yvgthuisehnvghi7yt34w87ebtgh4u7weyftnh7wcyesngfcsbys745EFGGGABSsdjisaiodjafndsfnosdnofisdsfjkwheurgtihaifmsniaesulrtgoaiwulnefcsjdgfaesyrfvjn34w87ebtgh4u7weyftnh7wcyesngfcsbys745EFGGGABSsdjisaiodjafndsfnosdnofisdsfjkwheurgtihaifmsniaesulrtgoaiwulnefc            sjdgfaesyrfvjn dsjgfhawkygf  fetew     oidfiqueahrgtiouh212376242375245y213hrufwhekjdsnfib43yt73e4yt534hwruhfwjerf3845y2ABCD237y642875yr2dkljfhjhafnjeh49376ygb8uehbg7esvtgry478w354ytnbyreuighbw735yvgthuisehnvghi7yt34w87ebtgh4u7weyftnh7wcyesngfcsbys745EFGGGABSsdjisaiodjafndsfnosdnofisdsfjkwheurgtihaifmsniaesulrtgoaiwulnefcsjdgfaesyrfvjnABCD237y642875yr2dkljfhjhafnjeh49376ygb8uehbg7esvtgry478w354ytnbyreuighbw735yvgthuisehnvghi7ytABCD237y642875yr2dkljfhjhafnjeh49376ygb8uehbg7esvtgry478w354ytnbyreuighbw735yvgthuisehnvghi7yt34w87ebtgh4u7weyftnh7wcyesngfcsbys745EFGGGABSsdjisaiodjafndsfnosdnofisdsfjkwheurgtihaifmsniaesulrtgoaiwulnefcsjdgfaesyrfvjnABCD237y642875yr2dkljfhjhafnjeh49376ygb8uehbg7esvtgry478w354ytnbyreuighbw735yvgthuisehnvghi7yt34w87ebtgh4u7weyftnh7wcyesngfcsbys745EFGGGABSsdjisaiodjafndsfnosdnofisdsfjkwheurgtihaifmsniaesulrtgoaiwulnefcsjdgfaesyrfvjn34w87ebtgh4u7weyftnh7wcyesngfcsbys745EFGGGABSsdjisaiodjafndsfnosdnofisdsfjkwheurgtihaifmsniaesulrtgoaiwulnefc            sjdgfaesyrfvjn dsjgfhawkygf  fetew     oidfiqueahrgtiouh212376242375245y213hrufwhekjdsnfib43yt73e4yt534hwruhfwjerf3845y2ABCD237y642875yr2dkljfhjhafnjeh49376ygb8uehbg7esvtgry478w354ytnbyreuighbw735yvgthuisehnvghi7yt34w87ebtgh4u7weyftnh7wcyesngfcsbys745EFGGGABSsdjisaiodjafndsfnosdnofisdsfjkwheurgtihaifmsniaesulrtgoaiwulnefcsjdgfaesyrfvjnABCD237y642875yr2dkljfhjhafnjeh49376ygb8uehbg7esvtgry478w354ytnbyreuighbw735yvgthuisehnvghi7ytABCD237y642875yr2dkljfhjhafnjeh49376ygb8uehbg7esvtgry478w354ytnbyreuighbw735yvgthuisehnvghi7yt34w87ebtgh4u7weyftnh7wcyesngfcsbys745EFGGGABSsdjisaiodjafndsfnosdnofisdsfjkwheurgtihaifmsniaesulrtgoaiwulnefcsjdgfaesyrfvjnABCD237y642875yr2dkljfhjhafnjeh49376ygb8uehbg7esvtgry478w354ytnbyreuighbw735yvgthuisehnvghi7yt34w87ebtgh4u7weyftnh7wcyesngfcsbys745EFGGGABSsdjisaiodjafndsfnosdnofisdsfjkwheurgtihaifmsniaesulrtgoaiwulnefcsjdgfaesyrfvjn34w87ebtgh4u7weyftnh7wcyesngfcsbys745EFGGGABSsdjisaiodjafndsfnosdnofisdsfjkwheurgtihaifmsniaesulrtgoaiwulnefc            sjdgfaesyrfvjn dsjgfhawkygf  fetew     oidfiqueahrgtiouh212376242375245y213hrufwhekjdsnfib43yt73e4yt534hwruhfwjerf3845y2ABCD237y642875yr2dkljfhjhafnjeh49376ygb8uehbg7esvtgry478w354ytnbyreuighbw735yvgthuisehnvghi7yt34w87ebtgh4u7weyftnh7wcyesngfcsbys745EFGGGABSsdjisaiodjafndsfnosdnofisdsfjkwheurgtihaifmsniaesulrtgoaiwulnefcsjdgfaesyrfvjnABCD237y642875yr2dkljfhjhafnjeh49376ygb8uehbg7esvtgry478w354ytnbyreuighbw735yvgthuisehnvghi7ytABCD237y642875yr2dkljfhjhafnjeh49376ygb8uehbg7esvtgry478w354ytnbyreuighbw735yvgthuisehnvghi7yt34w87ebtgh4u7weyftnh7wcyesngfcsbys745EFGGGABSsdjisaiodjafndsfnosdnofisdsfjkwheurgtihaifmsniaesulrtgoaiwulnefcsjdgfaesyrfvjnABCD237y642875yr2dkljfhjhafnjeh49376ygb8uehbg7esvtgry478w354ytnbyreuighbw735yvgthuisehnvghi7yt34w87ebtgh4u7weyftnh7wcyesngfcsbys745EFGGGABSsdjisaiodjafndsfnosdnofisdsfjkwheurgtihaifmsniaesulrtgoaiwulnefcsjdgfaesyrfvjn34w87ebtgh4u7weyftnh7wcyesngfcsbys745EFGGGABSsdjisaiodjafndsfnosdnofisdsfjkwheurgtihaifmsniaesulrtgoaiwulnefc            sjdgfaesyrfvjn dsjgfhawkygf  fetew     oidfiqueahrgtiouh212376242375245y213hrufwhekjdsnfib43yt73e4yt534hwruhfwjerf3845y2ABCD237y642875yr2dkljfhjhafnjeh49376ygb8uehbg7esvtgry478w354ytnbyreuighbw735yvgthuisehnvghi7yt34w87ebtgh4u7weyftnh7wcyesngfcsbys745EFGGGABSsdjisaiodjafndsfnosdnofisdsfjkwheurgtihaifmsniaesulrtgoaiwulnefcsjdgfaesyrfvjnABCD237y642875yr2dkljfhjhafnjeh49376ygb8uehbg7esvtgry478w354ytnbyreuighbw735yvgthuisehnvghi7ytABCD237y642875yr2dkljfhjhafnjeh49376ygb8uehbg7esvtgry478w354ytnbyreuighbw735yvgthuisehnvghi7yt34w87ebtgh4u7weyftnh7wcyesngfcsbys745EFGGGABSsdjisaiodjafndsfnosdnofisdsfjkwheurgtihaifmsniaesulrtgoaiwulnefcsjdgfaesyrfvjnABCD237y642875yr2dkljfhjhafnjeh49376ygb8uehbg7esvtgry478w354ytnbyreuighbw735yvgthuisehnvghi7yt34w87ebtgh4u7weyftnh7wcyesngfcsbys745EFGGGABSsdjisaiodjafndsfnosdnofisdsfjkwheurgtihaifmsniaesulrtgoaiwulnefcsjdgfaesyrfvjn34w87ebtgh4u7weyftnh7wcyesngfcsbys745EFGGGABSsdjisaiodjafndsfnosdnofisdsfjkwheurgtihaifmsniaesulrtgoaiwulnefc            sjdgfaesyrfvjn dsjgfhawkygf  fetew     oidfiqueahrgtiouh212376242375245y213hrufwhekjdsnfib43yt73e4yt534hwruhfwjerf3845y2ABCD237y642875yr2dkljfhjhafnjeh49376ygb8uehbg7esvtgry478w354ytnbyreuighbw735yvgthuisehnvghi7yt34w87ebtgh4u7weyftnh7wcyesngfcsbys745EFGGGABSsdjisaiodjafndsfnosdnofisdsfjkwheurgtihaifmsniaesulrtgoaiwulnefcsjdgfaesyrfvjnABCD237y642875yr2dkljfhjhafnjeh49376ygb8uehbg7esvtgry478w354ytnbyreuighbw735yvgthuisehnvghi7ytABCD237y642875yr2dkljfhjhafnjeh49376ygb8uehbg7esvtgry478w354ytnbyreuighbw735yvgthuisehnvghi7yt34w87ebtgh4u7weyftnh7wcyesngfcsbys745EFGGGABSsdjisaiodjafndsfnosdnofisdsfjkwheurgtihaifmsniaesulrtgoaiwulnefcsjdgfaesyrfvjnABCD237y642875yr2dkljfhjhafnjeh49376ygb8uehbg7esvtgry478w354ytnbyreuighbw735yvgthuisehnvghi7yt34w87ebtgh4u7weyftnh7wcyesngfcsbys745EFGGGABSsdjisaiodjafndsfnosdnofisdsfjkwheurgtihaifmsniaesulrtgoaiwulnefcsjdgfaesyrfvjn34w87ebtgh4u7weyftnh7wcyesngfcsbys745EFGGGABSsdjisaiodjafndsfnosdnofisdsfjkwheurgtihaifmsniaesulrtgoaiwulnefc            sjdgfaesyrfvjn dsjgfhawkygf  fetew     oidfiqueahrgtiouh212376242375245y213hrufwhekjdsnfib43yt73e4yt534hwruhfwjerf3845y2ABCD237y642875yr2dkljfhjhafnjeh49376ygb8uehbg7esvtgry478w354ytnbyreuighbw735yvgthuisehnvghi7yt34w87ebtgh4u7weyftnh7wcyesngfcsbys745EFGGGABSsdjisaiodjafndsfnosdnofisdsfjkwheurgtihaifmsniaesulrtgoaiwulnefcsjdgfaesyrfvjnABCD237y642875yr2dkljfhjhafnjeh49376ygb8uehbg7esvtgry478w354ytnbyreuighbw735yvgthuisehnvghi7ytABCD237y642875yr2dkljfhjhafnjeh49376ygb8uehbg7esvtgry478w354ytnbyreuighbw735yvgthuisehnvghi7yt34w87ebtgh4u7weyftnh7wcyesngfcsbys745EFGGGABSsdjisaiodjafndsfnosdnofisdsfjkwheurgtihaifmsniaesulrtgoaiwulnefcsjdgfaesyrfvjnABCD237y642875yr2dkljfhjhafnjeh49376ygb8uehbg7esvtgry478w354ytnbyreuighbw735yvgthuisehnvghi7yt34w87ebtgh4u7weyftnh7wcyesngfcsbys745EFGGGABSsdjisaiodjafndsfnosdnofisdsfjkwheurgtihaifmsniaesulrtgoaiwulnefcsjdgfaesyrfvjn34w87ebtgh4u7weyftnh7wcyesngfcsbys745EFGGGABSsdjisaiodjafndsfnosdnofisdsfjkwheurgtihaifmsniaesulrtgoaiwulnefc            sjdgfaesyrfvjn dsjgfhawkygf  fetew     oidfiqueahrgtiouh212376242375245y213hrufwhekjdsnfib43yt73e4yt534hwruhfwjerf3845y2";
	// const char* data = "ABCDEFGGGABSskfjdhdsfdsklgjdgsdfjskgmlksdm ds f kdsfmsekfdskfmmskdmg dsfndlskjgnskrnglsrg  eifhajlerioghjoi dfigsehjgroloiejrsoigjlaoehrglfousehlrgihseliu widhwer wr wf ewfete ewrwetr ewfiewoewklfj;eragioersgf;oewvnajew efiewjg;aeoirghjiradklafnljgnlouregudjsahfughlanfv"; // v
	uint32_t data_size = 0;
	
	uint16_t idx_array[256] = { 0 };

	uint32_t condensed_array[2 * 256 - 1] = { 0 };

	uint8_t condensed_array_idx = 0;

	for (int i =  0; data[i] != '\0'; i++) {
		if ((condensed_array[idx_array[data[i]]] >> 17) != data[i]) {
			condensed_array[condensed_array_idx] = (data[i] << 17);

			idx_array[data[i]] = condensed_array_idx++;
		}

		condensed_array[idx_array[data[i]]]++;

		data_size++;
	}

	printf("---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- \n");

	printf("sorted array size - %i\n", condensed_array_idx);
	
	uint16_t leaf_count = condensed_array_idx;

	for (int i = 0; i < condensed_array_idx; i++) {
		for (int j = i + 1; j < condensed_array_idx; j++) {
			// printf("i %i | j = %i\n", i, j);
			if ((condensed_array[j] & FREQ_BIT) <= (condensed_array[i] & FREQ_BIT)) {
				swap_u32(&condensed_array[j], &condensed_array[i]);
				printf("i %i | j = %i\n", i, j);
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
			printf("%c : %i\n", condensed_array[i] >> 17, condensed_array[i] & FREQ_BIT);
		}
	}

	// for (int i = 0; i < condensed_array_idx; i++) {
	// 	printf("%i", condensed_array[i]);
	// 	// print_bin(condensed_array[i], 26);
	// 	printf("\n");
	// }

	printf("---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- \n");

	uint16_t id_array[256] = { 0 };
	uint16_t result_array_idx = 0;
	
	uint32_t stack[2 * 256 - 1] = { 0 };
	uint16_t stack_ptr = 0;

	// uint16_t index = condensed_array_idx - 1;
	uint16_t encounter_leaf_count = 0;

	// while (encounter_leaf_count < leaf_count) {
	// 	if ((condensed_array[index] >> 16) & 1) {
	// 		stack[stack_ptr++] = index;

	// 		if (condensed_array[index]) {
				
	// 		}
	// 	} else {
	// 		printf("%i", condensed_array[index] & FREQ_BIT);
	// 		encounter_leaf_count++;
	// 		index = stack[--stack_ptr];
	// 	}
	// }

	traverse(condensed_array, id_array, condensed_array_idx - 1, 0, 1);

	printf("---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- \n");

	for (int i = 0; i < 256; i++) {
		if (id_array[i]) {
			printf("%c - ", i);
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

	uint32_t bit_i = 0;
	uint8_t store_array[8000] = { 0 };
	uint32_t len = 0;

	{

		for (uint32_t index = 0; data[index] != '\0'; index++) {
			for (uint32_t j = 0; j < 16; j++) {
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
		
		printf("\nsize = %i\n", (bit_i - 1) >> 3);
		
		len = bit_i;
	}

	uint32_t pos = condensed_array_idx - 1;
	printf("%s\n", data);
	
	char final_result[10000] = { 0 };
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
	
	float ratio = ((float)(bit_i >> 3) / (float)(data_size)) * 100;
	printf("compression ratio = %f%\n", ratio);
}

// 00101001100000000000000001
// 00100011000000000000000001
// 00100010100000000000000001
// 00100010000000000000000001
// 00100001100000000000000001
// 00000001010000000000000010
// 00000000010000000000000010
// 00100001000000000000000010
// 00100000100000000000000010
// 00000010010000000000000011
// 00100011100000000000000011
// 00000011010000000000000100
// 00000100010000000000000101
// 00000101010000000000000111
// 00000110010000000000001100

// verilog
// 00101001100000000000000001
// 00100011000000000000000001
// 00100010100000000000000001
// 00100010000000000000000001
// 00100001100000000000000001
// 00000001010000000000000010
// 00000000010000000000000010
// 00100001000000000000000010
// 00100000100000000000000010
// 00000010010000000000000011
// 00100011100000000000000011
// 00000011010000000000000100
// 00000100010000000000000101
// 00000101010000000000000111


// 0: S : 1
// 1: F : 1
// 2: E : 1
// 3: D : 1
// 4: C : 1
// 5: 2 - 3 : 2
// 6: 0 - 1 : 2
// 7: B : 2
// 8: A : 2
// 9: 4 - 5 : 3
// 10: G : 3
// 11: 6 - 7 : 4
// 12: 8 - 9 : 5
// 13: 10 - 11 : 7
// 14: 12 - 13 : 12

// 0: S : 1
// 1: F : 1
// 2: 0 - 1 : 0
// 3: E : 1
// 4: 2 - 3 : 0
// 5: D : 1
// 6: 4 - 5 : 0
// 7: C : 1
// 8: 6 - 7 : 0
// 9: B : 2
// 10: 8 - 9 : 0
// 11: A : 2
// 12: 10 - 11 : 0
// 13: G : 3
// 14: 12 - 13 : 0

// 0: S : 1
// 1: F : 1
// 2: E : 1
// 3: D : 1
// 4: C : 1
// 5: 2 - 3 : 2
// 6: 0 - 1 : 2
// 7: B : 2
// 8: A : 2
// 9: 4 - 5 : 3
// 10: G : 3
// 11: 6 - 7 : 4
// 12: 8 - 9 : 5
// 13: 10 - 11 : 7
// 14: 12 - 13 : 12

// B - 1111
// F - 11101
// S - 11100
// G - 110
// D - 10111
// E - 10110
// C - 1010
// A - 100

// B - 1111
// F - 11101
// S - 11100
// G - 110
// D - 10111
// E - 10110
// C - 1010
// A - 100
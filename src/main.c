#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct node {
	int8_t freq;
	uint8_t data;

	struct node* left;
	struct node* right;
};

struct node* insert(struct node* root, int8_t freq) {
	if (root == NULL) {
		root = (struct node*)malloc(sizeof(struct node));

		root->freq = freq;
		
		root->left = 0;
		root->right = 0;

		return root;
	}

	// 	if (root->left->freq < root->right->freq) {
	// 		root->left = insert(root->left, freq);
	// 	} else {
	// 		root->right = insert(root->right, freq);
	// 	}
	// }

	if (root->left == NULL && root->right == NULL) {
		if (freq < root->freq) {
			root->left = insert(root->left, freq);
			root->right = insert(root->right, root->freq);
		} else {
			root->left = insert(root->left, root->freq);
			root->right = insert(root->right, freq);
		}
	} else {
		if (root->left) {
			if (root->left->freq - freq < freq) {
				if (root->left->freq < root->right->freq) {
					root->left = insert(root->left, freq);
				} else {
					root->right = insert(root->right, freq);
				}
			}
		}
	}

	root->freq += freq;
	
}/

	return root;
}

void traverse(struct node* root, int level) {
	if (root != NULL) {

		traverse(root->right, level + 1);
		for (int i = 0; i < level; i++) {
			printf("\t");
		}

		printf("%i\n", root->freq);
		traverse(root->left, level + 1);
	}
}

int main(int count, char** args) {
	// FILE* fp = fopen("/home/laperex/Programming/C++/compressor/100KB.bin", "rb");
	// fseek(fp, 0, SEEK_END);
	// int sz = ftell(fp);
	// rewind(fp);

	// while (ftell(fp) < sz) {
	// 	fgets(data + ftell(fp), 100, fp);
	// }

	// uint8_t* data = (uint8_t*)"loremipsumdolorsitamisskrishnadevk-massecheussetsisinusaisinanviablestateofplatinumbollocksdownde";

	// struct node data_instance_count[256] = { 0 };

	// for (int i = 0; i < sizeof(data); i++) {
	// 	data_instance_count[data[i]].freq++;
	// }

	// printf("%i\n", data[0]);
	
	struct node* root = NULL;
	// root = (struct node*)malloc(sizeof(struct node));
	
	// root->freq = 1;
	
	// printf("%i\n", root->freq);
	
	root = insert(root, 1);
	root = insert(root, 2);
	root = insert(root, 2);
	root = insert(root, 2);
	// root = insert(root, 3);
	// root = insert(root, 1);

	// root = insert(root, 2);
	// root = insert(root, 3);
	// root = insert(root, 4);
	// root = insert(root, 3);
	// root = insert(root, 3);
	// traverse(root, 0);
	// root = insert(root, 2);
	traverse(root, 0);
	// root = insert(root, 2);
	// root = insert(root, 5);
	// root = insert(root, 2);
	// root = insert(root, 3);
	
	// printf("%i\n", root->freq);
}
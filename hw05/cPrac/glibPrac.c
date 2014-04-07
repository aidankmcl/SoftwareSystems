#include <glib.h>
#include <stdlib.h>
#include <stdio.h>

void parser(FILE *file, GHashTable *hash) {

	printf("The capital of Texas is %i\n", g_hash_table_lookup(hash, "Texas"));
	g_hash_table_insert(hash, "Woof", 2);

	char word[30];

	while (fscanf(file,"%s",word) != EOF) {
		int value = g_hash_table_lookup(hash, word);
		if (value == NULL) {
			puts("added!");
			printf("word: %s, value: %i\n\n",word,value);
			g_hash_table_insert(hash, word, 1);
		} else {
			puts("else happened");
			printf("word: %s, value: %i\n\n",word,value);
			int value = g_hash_table_lookup(hash, word);
			value++;
			g_hash_table_replace(hash, word, value);
		}
	}
}

int main() {
	FILE *file = fopen("metaKafka.txt","r");

	GHashTable* hash = g_hash_table_new(g_str_hash, g_str_equal);

	printf("There are %d keys in the hash\n", g_hash_table_size(hash));
	parser(file, hash);
	sleep(1);
	printf("How many times does is appear: %i\n", g_hash_table_lookup(hash, "is"));

	return 0;
}
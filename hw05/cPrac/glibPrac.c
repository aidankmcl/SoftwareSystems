#include <glib.h>
#include <stdlib.h>
#include <stdio.h>


void parser(FILE *file, GHashTable *hash) {
	char word[30];

	while (fscanf(file,"%s",word) != EOF) {
		int value = g_hash_table_lookup(hash, word);

		char *toAdd = malloc(30);
		strcpy(toAdd,word);

		if (value == NULL) {
			g_hash_table_insert(hash, toAdd, 1);
		} else {
			int value = g_hash_table_lookup(hash, toAdd);
			value++;
			g_hash_table_replace(hash, toAdd, value);
		}
	}
}

static void spit(gpointer key, gpointer value, gpointer userdata) {
    printf("word: %s, freq: %i\n",key,value);
}

int main() {
	FILE *file = fopen("metaKafka.txt","r");
	GHashTable* hash = g_hash_table_new(g_str_hash, g_str_equal);
	parser(file, hash);

	g_hash_table_foreach(hash, spit, NULL);
	return 0;
}
#include <glib.h>
#include <stdlib.h>
#include <stdio.h>

/* 

Written for Software Systems at Olin College
by Aidan McLaughlin

This program reads "Metamorphosis" by Kafka and counts the
frequency of each word by incrememnting a hash table value
each time a word is encountered and adds the word if it 
hasn't been encountered.

*/



/*
word_handler takes the book's text file and hash table as inputs.
fscanf reads word by word as delineated by whitespace and
the hash table is then checked for the word. 

If the word's already been entered, the frequency value is
incremented by one, if not it's added.
*/
void word_handler(FILE *file, GHashTable *hash) {
	// word to check for
	char word[30];

	while (fscanf(file,"%s",word) != EOF) {
		//value will be null if there's no key for the word
		int value = g_hash_table_lookup(hash, word);

		//must allocate space for the actual word to be
		//added.
		char *toAdd = malloc(30);
		strcpy(toAdd,word);

		//adding
		if (value == NULL) {
			g_hash_table_insert(hash, toAdd, 1);
		//updating
		} else {
			value++;
			g_hash_table_replace(hash, toAdd, value);
		}
	}
}


/* 
spit is called by g_hash_table_foreach and prints the word and 
its frequency. It takes in gpointers as per usage of GLib but 
they'll function as strings and ints here.

userdata is used if we need to return a value from each element
but we're just printing.
*/
static void spit(gpointer key, gpointer value, gpointer userdata) {
    printf("word: %s, freq: %i\n",key,value);
}


/*
main opens the textfile and creates a new hash table which
is then passed to the word_handler.

After the word_handler does its operations, we call foreach to
print each word and frequency.
*/
int main() {
	FILE *file = fopen("metaKafka.txt","r");
	GHashTable* hash = g_hash_table_new(g_str_hash, g_str_equal);
	word_handler(file, hash);

	g_hash_table_foreach(hash, spit, NULL);
	return 0;
}
#include <stdio.h>
#include <stdlib.h>

int checkVal(char *cname) {
	int val = 0;
	switch(cname[0]) {
	case 'K':
	case 'Q':
	case 'J':
		val = 10;
		break;
	case 'A':
		val = 11;
		break;
	case 'X':
		val = 0;
		break;
	default:
		val = atoi(cname);
		if ((val < 1) || (val > 10)) {
			puts("I don't understand!");
			break;
		}
	}
	return val;
}

int countMod(int value,int count) {
		/* Check if the value is 3 to 6 */
		if ((value > 2) && (value < 7)) {
			puts("Count has gone up");
			count++;
	/* Otherwise check if the card was 10, J, Q, or K */
		} else if (value == 10) {
			puts("Count has gone down");
			count--;
		}
	return count;
}

int main() {
	char card_name[3];
	int count = 0;
	int val = 0;
	while (val != -1) {
		puts("Enter the card name: ");
		scanf("%2s", card_name);

		val = checkVal(card_name);

		count = countMod(val, count);

		printf("Current count is %i\n", count);
	}
	return 0;
}
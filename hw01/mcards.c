/*
	mcards.c is a card counting program that's been 
	refactored into 3 functions instead of one main
	that does all the work.

	I worked with Charlene on this assignment.
*/


#include <stdio.h>
#include <stdlib.h>


/*
	checkVal looks at the character entered by the user
	and the rules are that of most card games.

	10 and face cards besides Ace are 10
	Ace is 11
	Cards < 10 are their own value

	Outside of those cases, nothing happens.
*/

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
		val = -1;
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


/*
	countMod updates the running card count by taking
	the value of a given card and determining whether
	the count should increase or decrease by 1, otherwise
	it stays the same.

	3 to 6 means count goes up by 1

	10 and face cards (- Ace) mean count decreases by 1

	Otherwise no change
*/

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


/*
	Main function, initializes variables and uses while
	loop to cycle through getting a card name, determining
	its value and then giving that value to the count
	modifying function, which returns an updated count.

*/

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
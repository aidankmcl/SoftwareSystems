#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

typedef struct {
    int numer;
    int denom;
} Rational;

// Returns a new Rational with the given numer and denom.
// If unable to allocate, prints an error message and exits.
Rational *make_rational(int numer, int denom) {
    // FILL THIS IN
    Rational *rational = malloc(sizeof(Rational));
    if (rational == NULL) {
        fprintf(stderr, "Malloc failed\n");
        exit(1);
    }

    rational->numer = numer;
    rational->denom = denom;
    
    return rational;
}

// Computes a floating-point approximation of a Rational.
double rational_to_double(Rational *rational) {
    // FILL THIS IN
    double ans = (double) rational->numer/rational->denom;
    return ans;
}

// Multiplies two rational numbers; returns a new Rational.
Rational *mult_rational(Rational *r1, Rational *r2) {
    // FILL THIS IN
    Rational *multRat = malloc(sizeof(Rational));
    if (multRat == NULL) {
        fprintf(stderr, "Malloc failed\n");
        exit(1);
    }

    multRat->numer = r1->numer * r2->numer;
    multRat->denom = r1->denom * r2->denom;

    return multRat;
}

// Frees a Rational.
void free_rational(Rational *rational) {
    free(rational);
}

// Prints a rational in fraction form.
void print_rational(Rational *rational) {
    printf("%d / %d\n", rational->numer, rational->denom);
}

int main(void)
{
    Rational *rational = make_rational(3, 7);
    print_rational(rational);

    double d = rational_to_double(rational);
    printf("%lf\n", d);

    Rational *square = mult_rational(rational, rational);
    print_rational(square);
	
    free_rational(rational);
    free_rational(square);

    return EXIT_SUCCESS;
}

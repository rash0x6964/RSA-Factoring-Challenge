#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#include <gmp.h>

void errorLog(char *errorMsg) {
	fprintf(stderr, "%s\n", errorMsg);
	exit(1);
}


void factorsNonPrimes(char *lineptr) {
	mpz_t number, holder;

	mpz_init_set_str(number, lineptr, 10);
	mpz_init_set_ui(holder, 0);
	free(lineptr);

	mpz_t i, mod, mul, zero;
	mpz_init(i);
	mpz_init(mod);
	mpz_init(mul);
	mpz_init_set_ui(zero, 0);


	for (mpz_set_ui(i, 2); mpz_cmp(i, number) < 0; mpz_add_ui(i, i, 1)) {

		mpz_mod(mod, number, i);
		if (mpz_cmp(mod, zero) == 0) {
			if (mpz_cmp(holder, zero) == 0)
				mpz_set(holder, i);

			mpz_mul(mul, i, holder);
			if (mpz_cmp(mul, number) == 0) {
				gmp_printf("%Zd=%Zd*%Zd\n", number, i, holder);
				break;
			}
		}
	}

	mpz_clear(number);
	mpz_clear(holder);
	mpz_clear(i);
	mpz_clear(mod);
	mpz_clear(mul);
}


void factorsPrimes(char *lineptr) {
	mpz_t number;

	mpz_init_set_str(number, lineptr, 10);
	free(lineptr);

	mpz_t i, j, mul, div;
	mpz_init(i);
	mpz_init(j);
	mpz_init(mul);
	mpz_init(div);


	for (mpz_set_ui(i, 2); mpz_cmp(i, number) < 0; mpz_add_ui(i, i, 1)) {
		mpz_div(div, number, i);
		for (mpz_set_ui(j, 2); mpz_cmp(j, div) < 0; mpz_add_ui(j, j, 1)) {
			gmp_printf("number: %Zd | div: %Zd | i: %Zd | j: %Zd\n", number, div, i, j);
			mpz_mul(mul, j, i);
			if (mpz_cmp(mul, number) == 0) {
				gmp_printf("%Zd=%Zd*%Zd\n", number, j, i);
				return;
			}
		}
	}

	mpz_clear(number);
	mpz_clear(mul);
	mpz_clear(i);
	mpz_clear(j);
}


int main(int argc, char **argv) {
	FILE* fptr;

	if (argc != 2) errorLog("Accept only one argument.");

	fptr = fopen(argv[1], "r");
	if (!fptr) errorLog("The file is not opened.");

	while (1) {

		char *lineptr = NULL;
		size_t n = 0;
		int len = getline(&lineptr, &n, fptr);
		if (len == -1) {
			free(lineptr);
			exit(1);
		}

		lineptr[len - 1] = 0;
		factorsPrimes(lineptr);

	}

	return 0;
}

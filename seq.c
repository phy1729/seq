/*
 * Original bash script by Geir Hauge
 * https://gitlab.com/geirha/shbot-initramfs/-/blob/master/skel/bin/seq
 */
/*
 * Copyright (c) 2021 Matthew Martin <phy1729@gmail.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <err.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const char *simple_nums[] = {
	"zero",
	"one",
	"two",
	"three",
	"four",
	"five",
	"six",
	"seven",
	"eight",
	"nine",
	"ten",
	"eleven",
	"twelve",
	"thirteen",
	"fourteen",
	"fifteen",
	"sixteen",
	"seventeen",
	"eighteen",
	"nineteen",
	"twenty",
};

const char *tens[] = {
	"",
	"ten",
	"twenty",
	"thirty",
	"forty",
	"fifty",
	"sixty",
	"seventy",
	"eighty",
	"ninety",
};

const char *units[] = {
	"",
	"thousand",
	"million",
	"billion",
	"trillion",
	"quadrillion",
	"quintillion",
	"fantazillion",
};

int64_t read_int(const char *, const char *);
void printnum(int64_t);

int
main(int argc, char* argv[]) {
	int64_t start=1, step=1, end=0;

	switch (argc) {
		case 1:
			errx(1, "Did you forget something?");
		case 2:
			end = read_int(argv[1], "end");
			break;
		case 3:
			start = read_int(argv[1], "start");
			end = read_int(argv[2], "end");
			break;
		case 4:
			start = read_int(argv[1], "start");
			step = read_int(argv[2], "step");
			end = read_int(argv[3], "end");
			break;
		default:
			errx(1, "Too much information!");
	}

	if (step > 0 && start <= end) {
		for (int64_t i = start; i <= end; i+= step) {
			printnum(i);
		}
	} else if (step < 0 && start >= end) {
		for (int64_t i = start; i >= end; i+= step) {
			printnum(i);
		}
	} else {
		errx(1, "Nice try");
	}

	return 0;
}

int64_t
read_int(const char *nptr, const char *name) {
	char *endptr;
	errno = 0;
	int64_t value = strtoll(nptr, &endptr, 10);
	if (nptr[0] == '\0' || *endptr == '\0') {
		errx(1, "%s is not a number: %s", name, nptr);
	}
	if (errno == ERANGE) {
		errx(1, "%s is too %s: %s", name, value > 0 ? "large" : "small", nptr);
	}
	return value;
}

void
printnum(int64_t num) {
	int64_t n, pow;
	int e;

	if (num < 0) {
		printf("minus ");
		num *= -1;
	}

	if (num == 0) {
		printf("%s\n", simple_nums[num]);
		return;
	}

	for (n = num, e = 0, pow = 1; n > 1000; n /= 1000, e++, pow *= 1000);

	for ( ; e >= 0; e--, pow /= 1000 ) {
		int part = num / pow;
		num -= part * pow;

		if (part == 0) {
			continue;
		}

		if (part >= 100) {
			printf("%s hundred", simple_nums[part/100]);
			part %= 100;
			if (part > 0) {
				printf(" and ");
			}
		}

		if (part > 0) {
			if (part < 20) {
				printf("%s", simple_nums[part]);
			} else if (part % 10 == 0) {
				printf("%s", tens[part/10]);
			} else {
				printf("%s-%s", tens[part/10], simple_nums[part%10]);
			}
		}

		if (e > 0) {
			printf(" %s%s", units[e], num ? " " : "");
		}
	}
	printf("\n");
}

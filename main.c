/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhshala <ayham.shalabi@learner.42.tech    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 14:59:58 by ayhshala          #+#    #+#             */
/*   Updated: 2026/09/22 16:05:00 by ayhshala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "ft_printf.h"

#define GREEN "\033[0;32m"
#define RED   "\033[0;31m"
#define BLUE  "\033[0;34m"
#define CYAN  "\033[0;36m"
#define RESET "\033[0m"

static int	g_total = 0;
static int	g_passed = 0;

static void	eval(int r1, int r2)
{
	g_total++;
	if (r1 == r2)
	{
		g_passed++;
		printf("   %s[PASS]%s count: std=%d | ft=%d\n\n", GREEN, RESET, r1, r2);
	}
	else
	{
		printf("   %s[FAIL]%s count diff: std=%d | ft=%d\n\n", RED, RESET, r1, r2);
	}
}

int	main(void)
{
	int		r1;
	int		r2;
	int		dummy = 42;
	void	*heap_ptr = malloc(16);

	printf("%s==================================================%s\n", CYAN, RESET);
	printf("%s          FT_PRINTF COMPREHENSIVE TESTER          %s\n", CYAN, RESET);
	printf("%s==================================================%s\n\n", CYAN, RESET);

	/* ------------------------------------------------------------------ */
	/* 1. PLAIN TEXT & EMPTY STRINGS                                      */
	/* ------------------------------------------------------------------ */
	printf("%s[1] PLAIN TEXT & EMPTY STRINGS%s\n", BLUE, RESET);
	r1 = printf("[std]: Simple string without format\n");
	r2 = ft_printf("[ft ]: Simple string without format\n");
	eval(r1, r2);

	r1 = printf("[std]: ");
	r1 += printf("");
	printf("\n");
	r2 = ft_printf("[ft ]: ");
	r2 += ft_printf("");
	ft_printf("\n");
	eval(r1, r2);

	/* ------------------------------------------------------------------ */
	/* 2. %c (CHAR) TESTS                                                 */
	/* ------------------------------------------------------------------ */
	printf("%s[2] %%c (CHAR) TESTS%s\n", BLUE, RESET);
	r1 = printf("[std]: Standard char: [%c]\n", 'a');
	r2 = ft_printf("[ft ]: Standard char: [%c]\n", 'a');
	eval(r1, r2);

	r1 = printf("[std]: Null byte char: [%c]\n", '\0');
	r2 = ft_printf("[ft ]: Null byte char: [%c]\n", '\0');
	eval(r1, r2);

	r1 = printf("[std]: Multiple chars: [%c] [%c] [%c]\n", '1', ' ', 'Z');
	r2 = ft_printf("[ft ]: Multiple chars: [%c] [%c] [%c]\n", '1', ' ', 'Z');
	eval(r1, r2);

	r1 = printf("[std]: Null char in-between: pre[%c]post\n", '\0');
	r2 = ft_printf("[ft ]: Null char in-between: pre[%c]post\n", '\0');
	eval(r1, r2);

	/* ------------------------------------------------------------------ */
	/* 3. %s (STRING) TESTS                                               */
	/* ------------------------------------------------------------------ */
	printf("%s[3] %%s (STRING) TESTS%s\n", BLUE, RESET);
	r1 = printf("[std]: Standard string: [%s]\n", "Hello 42!");
	r2 = ft_printf("[ft ]: Standard string: [%s]\n", "Hello 42!");
	eval(r1, r2);

	r1 = printf("[std]: Empty string: [%s]\n", "");
	r2 = ft_printf("[ft ]: Empty string: [%s]\n", "");
	eval(r1, r2);

	r1 = printf("[std]: NULL string pointer: [%s]\n", (char *)NULL);
	r2 = ft_printf("[ft ]: NULL string pointer: [%s]\n", (char *)NULL);
	eval(r1, r2);

	r1 = printf("[std]: Multiple strings: [%s] [%s] [%s]\n", "first", "", "third");
	r2 = ft_printf("[ft ]: Multiple strings: [%s] [%s] [%s]\n", "first", "", "third");
	eval(r1, r2);

	r1 = printf("[std]: String with special chars: [%s]\n", "tab:\t newline:\n quote:\"");
	r2 = ft_printf("[ft ]: String with special chars: [%s]\n", "tab:\t newline:\n quote:\"");
	eval(r1, r2);

	/* ------------------------------------------------------------------ */
	/* 4. %d and %i (SIGNED INTEGER) TESTS                                */
	/* ------------------------------------------------------------------ */
	printf("%s[4] %%d / %%i (SIGNED INTEGER) TESTS%s\n", BLUE, RESET);
	r1 = printf("[std]: Zero: [%d] [%i]\n", 0, 0);
	r2 = ft_printf("[ft ]: Zero: [%d] [%i]\n", 0, 0);
	eval(r1, r2);

	r1 = printf("[std]: Positive single digit: [%d] [%i]\n", 7, 7);
	r2 = ft_printf("[ft ]: Positive single digit: [%d] [%i]\n", 7, 7);
	eval(r1, r2);

	r1 = printf("[std]: Negative single digit: [%d] [%i]\n", -7, -7);
	r2 = ft_printf("[ft ]: Negative single digit: [%d] [%i]\n", -7, -7);
	eval(r1, r2);

	r1 = printf("[std]: Positive standard: [%d] [%i]\n", 42, 1337);
	r2 = ft_printf("[ft ]: Positive standard: [%d] [%i]\n", 42, 1337);
	eval(r1, r2);

	r1 = printf("[std]: Negative standard: [%d] [%i]\n", -42, -1337);
	r2 = ft_printf("[ft ]: Negative standard: [%d] [%i]\n", -42, -1337);
	eval(r1, r2);

	r1 = printf("[std]: INT_MAX: [%d] [%i]\n", INT_MAX, INT_MAX);
	r2 = ft_printf("[ft ]: INT_MAX: [%d] [%i]\n", INT_MAX, INT_MAX);
	eval(r1, r2);

	r1 = printf("[std]: INT_MIN: [%d] [%i]\n", INT_MIN, INT_MIN);
	r2 = ft_printf("[ft ]: INT_MIN: [%d] [%i]\n", INT_MIN, INT_MIN);
	eval(r1, r2);

	r1 = printf("[std]: INT_MIN + 1: [%d]\n", INT_MIN + 1);
	r2 = ft_printf("[ft ]: INT_MIN + 1: [%d]\n", INT_MIN + 1);
	eval(r1, r2);

	r1 = printf("[std]: INT_MAX - 1: [%d]\n", INT_MAX - 1);
	r2 = ft_printf("[ft ]: INT_MAX - 1: [%d]\n", INT_MAX - 1);
	eval(r1, r2);

	/* ------------------------------------------------------------------ */
	/* 5. %u (UNSIGNED INTEGER) TESTS                                     */
	/* ------------------------------------------------------------------ */
	printf("%s[5] %%u (UNSIGNED INTEGER) TESTS%s\n", BLUE, RESET);
	r1 = printf("[std]: Zero: [%u]\n", 0);
	r2 = ft_printf("[ft ]: Zero: [%u]\n", 0);
	eval(r1, r2);

	r1 = printf("[std]: Standard unsigned: [%u]\n", 4294);
	r2 = ft_printf("[ft ]: Standard unsigned: [%u]\n", 4294);
	eval(r1, r2);

	r1 = printf("[std]: UINT_MAX: [%u]\n", UINT_MAX);
	r2 = ft_printf("[ft ]: UINT_MAX: [%u]\n", UINT_MAX);
	eval(r1, r2);

	r1 = printf("[std]: Negative cast (-1): [%u]\n", (unsigned int)-1);
	r2 = ft_printf("[ft ]: Negative cast (-1): [%u]\n", (unsigned int)-1);
	eval(r1, r2);

	r1 = printf("[std]: Negative cast (-42): [%u]\n", (unsigned int)-42);
	r2 = ft_printf("[ft ]: Negative cast (-42): [%u]\n", (unsigned int)-42);
	eval(r1, r2);

	r1 = printf("[std]: INT_MIN as unsigned: [%u]\n", (unsigned int)INT_MIN);
	r2 = ft_printf("[ft ]: INT_MIN as unsigned: [%u]\n", (unsigned int)INT_MIN);
	eval(r1, r2);

	/* ------------------------------------------------------------------ */
	/* 6. %x and %X (HEXADECIMAL) TESTS                                   */
	/* ------------------------------------------------------------------ */
	printf("%s[6] %%x / %%X (HEXADECIMAL) TESTS%s\n", BLUE, RESET);
	r1 = printf("[std]: Zero: [%x] [%X]\n", 0, 0);
	r2 = ft_printf("[ft ]: Zero: [%x] [%X]\n", 0, 0);
	eval(r1, r2);

	r1 = printf("[std]: Letter transition (10 to 15): [%x] [%X]\n", 10, 15);
	r2 = ft_printf("[ft ]: Letter transition (10 to 15): [%x] [%X]\n", 10, 15);
	eval(r1, r2);

	r1 = printf("[std]: Base power 16: [%x] [%X]\n", 16, 16);
	r2 = ft_printf("[ft ]: Base power 16: [%x] [%X]\n", 16, 16);
	eval(r1, r2);

	r1 = printf("[std]: Byte limit 255: [%x] [%X]\n", 255, 255);
	r2 = ft_printf("[ft ]: Byte limit 255: [%x] [%X]\n", 255, 255);
	eval(r1, r2);

	r1 = printf("[std]: UINT_MAX: [%x] [%X]\n", UINT_MAX, UINT_MAX);
	r2 = ft_printf("[ft ]: UINT_MAX: [%x] [%X]\n", UINT_MAX, UINT_MAX);
	eval(r1, r2);

	r1 = printf("[std]: Negative (-1): [%x] [%X]\n", -1, -1);
	r2 = ft_printf("[ft ]: Negative (-1): [%x] [%X]\n", -1, -1);
	eval(r1, r2);

	r1 = printf("[std]: Complex pattern: [%x] [%X]\n", 0xabcdef, 0xABCDEF);
	r2 = ft_printf("[ft ]: Complex pattern: [%x] [%X]\n", 0xabcdef, 0xABCDEF);
	eval(r1, r2);

	/* ------------------------------------------------------------------ */
	/* 7. %p (POINTER) TESTS                                              */
	/* ------------------------------------------------------------------ */
	printf("%s[7] %%p (POINTER) TESTS%s\n", BLUE, RESET);
	r1 = printf("[std]: Stack pointer: [%p]\n", (void *)&dummy);
	r2 = ft_printf("[ft ]: Stack pointer: [%p]\n", (void *)&dummy);
	eval(r1, r2);

	r1 = printf("[std]: Heap pointer: [%p]\n", heap_ptr);
	r2 = ft_printf("[ft ]: Heap pointer: [%p]\n", heap_ptr);
	eval(r1, r2);

	r1 = printf("[std]: Function pointer: [%p]\n", (void *)&main);
	r2 = ft_printf("[ft ]: Function pointer: [%p]\n", (void *)&main);
	eval(r1, r2);

	r1 = printf("[std]: NULL pointer: [%p]\n", (void *)NULL);
	r2 = ft_printf("[ft ]: NULL pointer: [%p]\n", (void *)NULL);
	eval(r1, r2);

	r1 = printf("[std]: Small addresses: [%p] [%p]\n", (void *)1, (void *)16);
	r2 = ft_printf("[ft ]: Small addresses: [%p] [%p]\n", (void *)1, (void *)16);
	eval(r1, r2);

	r1 = printf("[std]: Max pointer address (-1): [%p]\n", (void *)-1);
	r2 = ft_printf("[ft ]: Max pointer address (-1): [%p]\n", (void *)-1);
	eval(r1, r2);

	/* ------------------------------------------------------------------ */
	/* 8. %% (PERCENT SIGN) TESTS                                         */
	/* ------------------------------------------------------------------ */
	printf("%s[8] %%%% (PERCENT SIGN) TESTS%s\n", BLUE, RESET);
	r1 = printf("[std]: Single percent: [%%]\n");
	r2 = ft_printf("[ft ]: Single percent: [%%]\n");
	eval(r1, r2);

	r1 = printf("[std]: Two escaped: [%%%%]\n");
	r2 = ft_printf("[ft ]: Two escaped: [%%%%]\n");
	eval(r1, r2);

	r1 = printf("[std]: Mixed with text: [100%% sure!]\n");
	r2 = ft_printf("[ft ]: Mixed with text: [100%% sure!]\n");
	eval(r1, r2);

	r1 = printf("[std]: Six consecutive: [%%%%%%]\n");
	r2 = ft_printf("[ft ]: Six consecutive: [%%%%%%]\n");
	eval(r1, r2);

	/* ------------------------------------------------------------------ */
	/* 9. COMPLEX COMBINATIONS & STRESS TESTS                             */
	/* ------------------------------------------------------------------ */
	printf("%s[9] COMPLEX COMBINATIONS & STRESS TESTS%s\n", BLUE, RESET);
	r1 = printf("[std]: All together: %c | %s | %p | %d | %i | %u | %x | %X | %%\n",
			'A', "42", (void *)&dummy, -42, 42, 4294967295U, 255, 255);
	r2 = ft_printf("[ft ]: All together: %c | %s | %p | %d | %i | %u | %x | %X | %%\n",
			'A', "42", (void *)&dummy, -42, 42, 4294967295U, 255, 255);
	eval(r1, r2);

	r1 = printf("[std]: Extreme combo: %s %d %p %u %x %%\n",
			(char *)NULL, INT_MIN, (void *)0, 0, 0);
	r2 = ft_printf("[ft ]: Extreme combo: %s %d %p %u %x %%\n",
			(char *)NULL, INT_MIN, (void *)0, 0, 0);
	eval(r1, r2);

	/* ------------------------------------------------------------------ */
	/* SUMMARY SCOREBOARD                                                 */
	/* ------------------------------------------------------------------ */
	printf("%s==================================================%s\n", CYAN, RESET);
	printf("%s                  TEST RESULTS                   %s\n", CYAN, RESET);
	printf("%s==================================================%s\n", CYAN, RESET);
	printf("Total Tests:   %d\n", g_total);
	printf("Passed:        %s%d%s\n", GREEN, g_passed, RESET);
	printf("Failed:        %s%d%s\n", (g_total == g_passed) ? GREEN : RED, g_total - g_passed, RESET);

	if (g_total == g_passed)
		printf("\n%s>>> CONGRATULATIONS! ALL TESTS PASSED (100%%) <<<%s\n\n", GREEN, RESET);
	else
		printf("\n%s>>> SOME TESTS FAILED! CHECK OUTPUT ABOVE. <<<%s\n\n", RED, RESET);

	free(heap_ptr);
	return (0);
}

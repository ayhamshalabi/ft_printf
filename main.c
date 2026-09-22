/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhshala <ayham.shalabi@learner.42.tech    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 14:59:58 by ayhshala          #+#    #+#             */
/*   Updated: 2026/09/22 16:00:00 by ayhshala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <limits.h>
#include "ft_printf.h"

static void	check_res(int std_ret, int ft_ret)
{
	if (std_ret == ft_ret)
		printf("   -> [MATCH] std count: %d | ft count: %d\n\n", std_ret, ft_ret);
	else
		printf("   -> [DIFF!] std count: %d | ft count: %d\n\n", std_ret, ft_ret);
}

int	main(void)
{
	int	r1;
	int	r2;
	int	dummy = 42;

	printf("==================== %%c (CHAR) ====================\n");
	r1 = printf("[std]: Standard char:      [%c]\n", 'A');
	r2 = ft_printf("[ft ]: Standard char:      [%c]\n", 'A');
	check_res(r1, r2);

	r1 = printf("[std]: Null byte char:     [%c]\n", '\0');
	r2 = ft_printf("[ft ]: Null byte char:     [%c]\n", '\0');
	check_res(r1, r2);

	r1 = printf("[std]: Special whitespace: [%c] [%c]\n", '\t', '\n');
	r2 = ft_printf("[ft ]: Special whitespace: [%c] [%c]\n", '\t', '\n');
	check_res(r1, r2);

	printf("==================== %%s (STRING) ==================\n");
	r1 = printf("[std]: Standard string:    [%s]\n", "Hello, World!");
	r2 = ft_printf("[ft ]: Standard string:    [%s]\n", "Hello, World!");
	check_res(r1, r2);

	r1 = printf("[std]: Empty string:       [%s]\n", "");
	r2 = ft_printf("[ft ]: Empty string:       [%s]\n", "");
	check_res(r1, r2);

	r1 = printf("[std]: NULL string:        [%s]\n", (char *)NULL);
	r2 = ft_printf("[ft ]: NULL string:        [%s]\n", (char *)NULL);
	check_res(r1, r2);

	printf("==================== %%d / %%i (SIGNED) =============\n");
	r1 = printf("[std]: Zero:               [%d] | [%i]\n", 0, 0);
	r2 = ft_printf("[ft ]: Zero:               [%d] | [%i]\n", 0, 0);
	check_res(r1, r2);

	r1 = printf("[std]: Positive:           [%d] | [%i]\n", 42, 42);
	r2 = ft_printf("[ft ]: Positive:           [%d] | [%i]\n", 42, 42);
	check_res(r1, r2);

	r1 = printf("[std]: Negative:           [%d] | [%i]\n", -42, -42);
	r2 = ft_printf("[ft ]: Negative:           [%d] | [%i]\n", -42, -42);
	check_res(r1, r2);

	r1 = printf("[std]: INT_MAX:            [%d] | [%i]\n", INT_MAX, INT_MAX);
	r2 = ft_printf("[ft ]: INT_MAX:            [%d] | [%i]\n", INT_MAX, INT_MAX);
	check_res(r1, r2);

	r1 = printf("[std]: INT_MIN:            [%d] | [%i]\n", INT_MIN, INT_MIN);
	r2 = ft_printf("[ft ]: INT_MIN:            [%d] | [%i]\n", INT_MIN, INT_MIN);
	check_res(r1, r2);

	printf("==================== %%u (UNSIGNED) ================\n");
	r1 = printf("[std]: Zero:               [%u]\n", 0);
	r2 = ft_printf("[ft ]: Zero:               [%u]\n", 0);
	check_res(r1, r2);

	r1 = printf("[std]: UINT_MAX:           [%u]\n", UINT_MAX);
	r2 = ft_printf("[ft ]: UINT_MAX:           [%u]\n", UINT_MAX);
	check_res(r1, r2);

	r1 = printf("[std]: Negative cast (-1): [%u]\n", (unsigned int)-1);
	r2 = ft_printf("[ft ]: Negative cast (-1): [%u]\n", (unsigned int)-1);
	check_res(r1, r2);

	printf("==================== %%x / %%X (HEX) ================\n");
	r1 = printf("[std]: Zero:               [%x] | [%X]\n", 0, 0);
	r2 = ft_printf("[ft ]: Zero:               [%x] | [%X]\n", 0, 0);
	check_res(r1, r2);

	r1 = printf("[std]: Single digit:       [%x] | [%X]\n", 15, 15);
	r2 = ft_printf("[ft ]: Single digit:       [%x] | [%X]\n", 15, 15);
	check_res(r1, r2);

	r1 = printf("[std]: UINT_MAX:           [%x] | [%X]\n", UINT_MAX, UINT_MAX);
	r2 = ft_printf("[ft ]: UINT_MAX:           [%x] | [%X]\n", UINT_MAX, UINT_MAX);
	check_res(r1, r2);

	r1 = printf("[std]: Arbitrary number:   [%x] | [%X]\n", 305419896, 305419896);
	r2 = ft_printf("[ft ]: Arbitrary number:   [%x] | [%X]\n", 305419896, 305419896);
	check_res(r1, r2);

	printf("==================== %%p (POINTER) =================\n");
	r1 = printf("[std]: Stack address:      [%p]\n", (void *)&dummy);
	r2 = ft_printf("[ft ]: Stack address:      [%p]\n", (void *)&dummy);
	check_res(r1, r2);

	r1 = printf("[std]: NULL pointer:       [%p]\n", (void *)NULL);
	r2 = ft_printf("[ft ]: NULL pointer:       [%p]\n", (void *)NULL);
	check_res(r1, r2);

	r1 = printf("[std]: Max address (-1):   [%p]\n", (void *)-1);
	r2 = ft_printf("[ft ]: Max address (-1):   [%p]\n", (void *)-1);
	check_res(r1, r2);

	printf("==================== %%%% (PERCENT) ================\n");
	r1 = printf("[std]: Single escaped:     [%%]\n");
	r2 = ft_printf("[ft ]: Single escaped:     [%%]\n");
	check_res(r1, r2);

	r1 = printf("[std]: Consecutive:        [%%%%] [%%%%%%]\n");
	r2 = ft_printf("[ft ]: Consecutive:        [%%%%] [%%%%%%]\n");
	check_res(r1, r2);

	printf("==================== MIXED EDGE CASE ===============\n");
	r1 = printf("[std]: Combined: [%c] [%s] [%d] [%x] [%p] [%%]\n",
			'Z', "42 Beirut", INT_MIN, 255, (void *)&dummy);
	r2 = ft_printf("[ft ]: Combined: [%c] [%s] [%d] [%x] [%p] [%%]\n",
			'Z', "42 Beirut", INT_MIN, 255, (void *)&dummy);
	check_res(r1, r2);

	return (0);
}

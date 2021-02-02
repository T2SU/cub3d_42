/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_random_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 23:57:50 by smun              #+#    #+#             */
/*   Updated: 2021/01/31 06:27:58 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static t_uint64		rotl(t_uint64 x, int k)
{
	return ((x << k) | (x >> (64 - k)));
}

/*
** XorShift 256 plusplus
** https://en.wikipedia.org/wiki/Xorshift#xoshiro256+
** https://terms.naver.com/entry.nhn?docId=850481&cid=50373&categoryId=50373
** https://ko.wikipedia.org/wiki/LFSR
** http://prng.di.unimi.it/xoshiro256plusplus.c
*/

t_uint64			util_random_int(void)
{
	static t_uint64	seed[4];
	t_uint64		t;
	t_uint64		res;

	if (!seed[0])
	{
		seed[0] = 0x1436abd34ef6ull;
		seed[1] = 0x22ef783ab321ull;
		seed[2] = 0xf838388a8827ull;
		seed[3] = 0x123412341234ull;
	}
	res = seed[0] + seed[3];
	t = seed[1] << 17;
	seed[2] ^= seed[0];
	seed[3] ^= seed[1];
	seed[1] ^= seed[2];
	seed[0] ^= seed[3];
	seed[2] ^= t;
	seed[3] = rotl(seed[3], 45);
	return (res);
}

double				util_random_double(void)
{
	t_uint64		x;
	t_uint64		xdbl;

	x = util_random_int();
	xdbl = (0x3FFull << 52) | (x >> 12);
	return ((*(double*)&xdbl) - 1.0);
}

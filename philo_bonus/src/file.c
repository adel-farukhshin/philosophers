/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsarai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 13:29:14 by bsarai            #+#    #+#             */
/*   Updated: 2022/06/12 13:29:15 by bsarai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

static void	ft_itoa(int index, char buf[]);
static int	power(int nb);
static int	divider(int len);

void	name_file(char *src, char dst[], int index)
{
	int		c;

	c = 0;
	while (src[c])
	{
		dst[c] = src[c];
		c++;
	}
	ft_itoa(index, dst + c);
}

static void	ft_itoa(int index, char buf[])
{
	int	i;
	int	div;

	i = 0;
	div = divider(power(index));
	while (div)
	{
		buf[i] = (index / div) + '0';
		index %= div;
		div /= 10;
		i++;
	}
	buf[i] = '\0';
}

static int	divider(int len)
{
	int	ret;

	ret = 1;
	while (len > 1)
	{
		ret *= 10;
		len--;
	}
	return (ret);
}

static int	power(int nb)
{
	int	i;

	i = 0;
	while (nb)
	{
		i++;
		nb /= 10;
	}
	return (i);
}

// int	main(void)
// {
// 	char	buf[10];
// 	char	*a;

// 	for (int i = 0; i < 10; i++)
// 	{
// 		name_file("last_", buf, i);
// 		printf("%s\n", buf);
// 	}
// }

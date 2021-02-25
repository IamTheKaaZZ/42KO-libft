/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 09:40:53 by bcosters          #+#    #+#             */
/*   Updated: 2021/02/25 18:13:24 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Helper function to get the arraysize
**	returns size 1 when c is not found in s
*/

static size_t	get_arrsize(char const *s, char c)
{
	size_t	i;
	size_t	size;

	if (ft_strchr(s, c) == NULL)
		return (2);
	i = 0;
	size = 0;
	while (*(s + i))
	{
		if (s[i] != c)
		{
			size++;
			while (s[i] != c && s[i])
				i++;
			i--;
		}
		i++;
	}
	size++;
	return (size);
}

/*
**	Iteratively finds the next string and corresponding lenght*
*/

static void		ft_get_next_str(char const **next_str, size_t *next_len, char c)
{
	size_t	i;

	*next_str += *next_len;
	*next_len = 0;
	i = 0;
	while (**next_str && **next_str == c)
		(*next_str)++;
	while ((*next_str)[i])
	{
		if ((*next_str)[i] == c)
			return ;
		(*next_len)++;
		i++;
	}
}

/*
**	Panic dump all the memory allocated*
*/

static char		**ft_malloc_fail(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

/*
**	1. Protect the function for case s == NULL
**	2. Get the array size with the helper function
**	3. Calloc the array (fill with nulls) and check for fails
**	4. Use the next_str function to find next str and length
**	5. Calloc the found string, check for fails and add it with strlcpy
**		5.1	if anything goes wrong --> panic dump with ft_malloc_fail
**	6. Add terminating NULL str to the array and return
*/

char			**ft_split(char const *s, char c)
{
	char	**arrsplit;
	size_t	next_len;
	size_t	i;
	size_t	arrsize;

	if (!s)
		return (NULL);
	arrsize = get_arrsize(s, c);
	if (!(arrsplit = (char**)ft_calloc(arrsize, sizeof(char*))))
		return (NULL);
	i = 0;
	next_len = 0;
	while (i < arrsize - 1)
	{
		ft_get_next_str(&s, &next_len, c);
		if (!(arrsplit[i] = (char*)ft_calloc((next_len + 1), sizeof(char))))
			return (ft_malloc_fail(arrsplit));
		ft_strlcpy(arrsplit[i], s, next_len + 1);
		i++;
	}
	return (arrsplit);
}

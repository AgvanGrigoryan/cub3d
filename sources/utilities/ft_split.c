/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:23:09 by natamazy          #+#    #+#             */
/*   Updated: 2024/07/22 18:23:10 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_sep(char *seps, char letter)
{
	int	i;

	i = 0;
	if (letter == '\0')
		return (0);
	while (seps[i] != '\0')
	{
		if (seps[i] == letter)
			return (1);
		i++;
	}
	return (0);
}

static size_t	count_words(char const *s, char *seps)
{
	unsigned int	words_count;
	unsigned int	i;

	words_count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && is_sep(seps, s[i]) == 1)
			i++;
		if (s[i] && is_sep(seps, s[i]) == 0)
			words_count++;
		while (s[i] && is_sep(seps, s[i]) == 0)
			i++;
	}
	return (words_count);
}

static void	free_prev_words(char **words, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		free(words[i++]);
}

static int	separate_words(char const *s, char *seps,
		size_t words_count, char **words)
{
	size_t		word_num;
	char const	*word_start;

	word_num = 0;
	while (*s && word_num < words_count)
	{
		while (*s && is_sep(seps, *s) == 1)
			s++;
		if (*s && is_sep(seps, *s) == 0)
			word_start = s;
		while (*s && is_sep(seps, *s) == 0)
			s++;
		words[word_num] = ft_substr(word_start, 0, s - word_start);
		if (words[word_num] == NULL)
		{
			free_prev_words(words, word_num);
			return (0);
		}
		word_num++;
	}
	words[word_num] = NULL;
	return (1);
}

char	**ft_split(char const *s, char *seps)
{
	size_t		words_count;
	char		**words;

	if (s == NULL)
		return (NULL);
	words_count = count_words(s, seps);
	words = (char **)malloc((words_count + 1) * sizeof(char *));
	if (words == NULL)
		return (perror("FT_SPLIT"), NULL);
	if (!separate_words(s, seps, words_count, words))
		return (NULL);
	return (words);
}

#include "cub3d.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	s_len;
	unsigned int	substr_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len < start)
		substr_len = 0;
	else if (s_len < len)
		substr_len = s_len;
	else
		substr_len = len;
	substr = (char *)malloc(substr_len + 1);
	if (substr == NULL)
		return (NULL);
	s += start;
	substr[substr_len] = '\0';
	while (substr_len--)
		substr[substr_len] = s[substr_len];
	return (substr);
}

int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}

int	starts_with_digit(const char *str)
{
	if (str == NULL)
		return (0);
	while (*str && ft_isspace(*str) == 1)
		str++;
	return (ft_isdigit(*str));
}

int	is_only_spaces(const char *str)
{
	while (str && *str)
	{
		if (ft_isspace(*str) == 0)
			return (0);
		str++;
	}
	return (1);
}
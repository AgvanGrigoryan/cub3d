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

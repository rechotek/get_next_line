/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrechuli <mrechuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 10:27:38 by mrechuli          #+#    #+#             */
/*   Updated: 2024/04/03 15:33:00 by mrechuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	x;

	x = 0;
	while (str[x] != '\0')
	{
		x++;
	}
	return (x);
}

char	*ft_strchr(char *str, int c)
{
	int	x;

	x = 0;
	if (!str)
		return (0);
	if (c == '\0')
		return ((char *)&str[ft_strlen(str)]);
	while (str[x] != '\0')
	{
		if (str[x] == (char) c)
			return ((char *)&str[x]);
		x++;
	}
	return (0);
}

char	*ft_strjoin(char *left_str, char *buff)
{
	size_t	x;
	size_t	y;
	char	*str;

	if (!left_str)
	{
		left_str = (char *)malloc(1 * sizeof(char));
		left_str[0] = '\0';
	}
	if (!left_str || !buff)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen(left_str) + ft_strlen(buff)) + 1));
	if (str == NULL)
		return (NULL);
	x = -1;
	y = 0;
	if (left_str)
		while (left_str[++x] != '\0')
			str[x] = left_str[x];
	while (buff[y] != '\0')
		str[x++] = buff[y++];
	str[ft_strlen(left_str) + ft_strlen(buff)] = '\0';
	free(left_str);
	return (str);
}

char	*ft_get_line(char *left_str)
{
	int		x;
	char	*line;

	x = 0;
	if (!left_str[x])
		return (NULL);
	while (left_str[x] != '\0' && left_str[x] != '\n')
		x++;
	line = (char *)malloc(sizeof(char) * (x + 2));
	if (!line)
		return (NULL);
	x = 0;
	while (left_str[x] != '\0' && left_str[x] != '\n')
	{
		line[x] = left_str[x];
		x++;
	}
	if (left_str[x] == '\n')
	{
		line[x] = left_str[x];
		x++;
	}
	line[x] = '\0';
	return (line);
}

char	*ft_new_left_str(char *left_str)
{
	int		x;
	int		y;
	char	*new_left_str;

	x = 0;
	y = 0;
	while (left_str[x] != '\0' && left_str[x] != '\n')
		x++;
	if (!left_str[x])
	{
		free(left_str);
		return (NULL);
	}
	new_left_str = (char *)malloc(sizeof(char) * (ft_strlen(left_str) - x));
	if (!new_left_str)
		return (NULL);
	x++;
	while (left_str[x] != '\0')
	{
		new_left_str[y++] = left_str[x++];
	}
	new_left_str[y] = '\0';
	free(left_str);
	return (new_left_str);
}

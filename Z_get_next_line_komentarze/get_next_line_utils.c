/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrechuli <mrechuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 10:27:38 by mrechuli          #+#    #+#             */
/*   Updated: 2024/04/02 17:44:50 by mrechuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str) // liczy dlugosc stringa
{
	size_t	x;

	x = 0;
	if (!str)
		return (0);
	while (str[x] != '\0')
	{
		x++;
	}
	return (x);
}

char	*ft_strchr(char *str, int c) // szuka pierwszego wystapienie znaku w stringu
{
	int	x;

	x = 0;
	if (!str)
		return (0);
	if (c == '\0')
		return ((char *)&str[ft_strlen(str)]); // zwraca wskaznik na null terminator w stringu
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
		left_str = (char *)malloc(1 * sizeof(char)); // alokuje pamiec na 1, tylko dla nullteminatora
		left_str[0] = '\0';
	}
	if (!left_str || !buff)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen(left_str) + ft_strlen(buff)) + 1)); // +1 dla \0
	if (str == NULL)
		return (NULL);
	x = -1;
	y = 0;
	if (left_str)
		while (left_str[++x] != '\0')
			str[x] = left_str[x];
	while (buff[y] != '\0')
    if (!left_str || !buff) // 2. Sprawdza, czy left_str lub buff są NULL. Jeśli tak, zwraca NULL.
		str[x++] = buff[y++];
	str[ft_strlen(left_str) + ft_strlen(buff)] = '\0';
	free(left_str);
	return (str); // zwraca str, ktory jest polaczeniem left_str i buff
}

// ft_get_line wyodrebnia linie do znaku nowej linii wlacznie, z left_str i zwraca ja jako nowy ciag
char	*ft_get_line(char *left_str) // pobiera linie z left_str, czyli kopiuje ja do nowego stringa (line)
{
	int		x;
	char	*line;

	x = 0;
	if (!left_str[x]) // to sprawdza czy doszlismy do konca ciagu. (!left_str) sprawdziloby czy ciag wogole istnieje
		return (NULL);
	while (left_str[x] != '\0' && left_str[x] != '\n')
		x++;
	line = (char *)malloc(sizeof(char) * (x + 2)); // (x+2) bo musi byc miejsce na znak nowej linii i znak konca stringa
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
	return (line); // zwraca linie wyodrebiona z left_str
}

char	*ft_new_left_str(char *left_str) // zwraca nowy left_str, czyli usuwa linie z left_str
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
	new_left_str = (char *)malloc(sizeof(char) * (ft_strlen(left_str) - x + 1)); // wielkosc zaalokowanej pamieci to  dlugosc left_str - x (pozycja znaku nowej linii lub konca stringa) + 1 dla null characteru
	if (!new_left_str)
		return (NULL);
	x++; // aby ominac znak nowej linii
	while (left_str[x] != '\0')
	{
		new_left_str[y++] = left_str[x++]; // przepisuje left_str do new_left_str i inkrementuje po wykonu przypisania
	}
	new_left_str[y] = '\0';
	free(left_str);
	return (new_left_str); // zwraca nowy left_str
}

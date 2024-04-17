/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrechuli <mrechuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 10:26:40 by mrechuli          #+#    #+#             */
/*   Updated: 2024/04/02 18:24:34 by mrechuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ex. Hello World
// 	This is a test
// 	End of file

// Opis poprawny jesli mamy duzy BUFFER. Jesli Buffer bedzie wynosil np. 5 to to pierwszym przejsciu przez ft_read_to_left_str, bedziemy mieli "Hello World\nThi". get_line wyciagnie nam z tego pierwszy wiersz: "Hello World\n". ft_new_left_str zrobi nam nowy left_str ucinajac pierwsza linijke, czyli zostawi "Thi". Do tego przy kolejnych wywolaniach ft_read_to_left beda dodawane kolejne znaki.

// 1. On the first call to get_next_line, left_str is empty. The function ft_read_to_left_str is called, which reads from the file into left_str until it encounters a newline character or the end of the file. After this call, left_str contains "Hello World\nThis is a test\nEnd of file".
// 2. ft_get_line is then called, which extracts the first line from left_str ("Hello World\n") and returns it. left_str still contains the rest of the file.
// 3. ft_new_left_str is called, which creates a new left_str that contains the remaining lines of the file ("This is a test\nEnd of file"). The old left_str is freed.
// 4. get_next_line returns the first line ("Hello World\n").
// 5. On the second call to get_next_line, left_str contains "This is a test\nEnd of file". ft_read_to_left_str is called again, but since left_str already contains a newline character, it doesn't read any more from the file.
// 6. ft_get_line extracts the second line ("This is a test\n") and ft_new_left_str updates left_str to contain the remaining line ("End of file").
// 7. get_next_line returns the second line ("This is a test\n").
// 8. On the third call to get_next_line, the process repeats and the third line ("End of file") is returned.
// 9. On the fourth call to get_next_line, ft_read_to_left_str tries to read more from the file, but since we're at the end of the file, it doesn't read anything. ft_get_line returns NULL because there are no more lines to read, and get_next_line also returns NULL, indicating that we've reached the end of the file.

#include "get_next_line.h"

char	*ft_read_to_left_str(int fd, char *left_str) // wczytuje deskryptor pliku do bufora, a następnie dołącza bufor do left_str, dopóki nie napotka znaku nowego wiersza lub nie będzie już więcej bajtów do odczytania. Następnie zwracana jest zaktualizowana wartość left_str.
{
	char	*buff;
	int		bytes; // przetrzymuje ilosc przeczytanych bajtow

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char)); // +1 dla \0
	if (!buff)
		return (NULL);
	bytes = 1;
	while (!ft_strchr(left_str, '\n') && bytes != 0) // wykonuje petle dopoki nie znajdzie znaku nowej linii lub gdy nie ma juz bajtow do przeczytania
	{
		bytes = read(fd, buff, BUFFER_SIZE); // zwraca ilosc wczytanych bajtow z deskryptora pliku do bufora
		if (bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[bytes] = '\0';
		left_str = ft_strjoin(left_str, buff); // dolacza string buffer do stringa left_str
	}
	free(buff);
	return (left_str); // zwraca zaktualizowany left_str
}

char	*get_next_line(int fd) // fd to jest file descriptor, czyli to co mamy odczytac i jest np. w konsoli
{
	char		*line;
	static char	*left_str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	left_str = ft_read_to_left_str(fd, left_str); // wczytuje z file descriptora do left_str
	if (!left_str)
		return (NULL);
	line = ft_get_line(left_str); // pobiera linie z left_str
	left_str = ft_new_left_str(left_str); // tworzy nowy left_str z pozostalymi liniami (bo ft_get_line wyodrebnia linie do znaku nowej linii wlacznie)
	return (line);
}

int	main(void)
{
	char	*line;
	int		i;
	int		fd1;
	// int		fd2;
	// int		fd3;
	fd1 = open("tests/test.txt", O_RDONLY);
	// fd2 = open("tests/test2.txt", O_RDONLY);
	// fd3 = open("tests/test3.txt", O_RDONLY);
	i = 1;
	while (i < 7)
	{
		line = get_next_line(fd1);
		printf("line [%02d]: %s", i, line); // %02d to miejsce, gdzie zostanie wstawiona wartość zmiennej i. 02d oznacza, że liczba będzie wydrukowana jako dwucyfrowa liczba dziesiętna, z wiodącymi zerami, jeśli liczba ma mniej niż dwie cyfry
		free(line);
		// line = get_next_line(fd2);
		// printf("line [%02d]: %s", i, line);
		// free(line);
		// line = get_next_line(fd3);
		// printf("line [%02d]: %s", i, line);
		// free(line);
		i++;
	}
	close(fd1);
	// close(fd2);
	// close(fd3);
	return (0);
}

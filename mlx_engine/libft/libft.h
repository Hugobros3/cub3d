/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:07:15 by reclaire          #+#    #+#             */
/*   Updated: 2023/01/26 01:04:47 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

# include "ft_lists.h"
# include "ft_strings.h"
# include "ft_maths.h"

# define MALLOC_ERROR 100

# define TRUE 1
# define FALSE 0

typedef int		t_bool;

int		ft_cmpint(void *i1, void *i2);

int		ft_cmpaddr(void *p1, void *p2);

//Reads the whole file
char	*ft_readfile(int fd, int read_size);

//Compares two strings
int		ft_strcmp(char *s1, char *s2);

//Malloc, but protected
void	*ft_malloc(size_t size);

//Check if character is digit or alpha.
int		ft_isalnum(int c);

//Check if character is alpha.
int		ft_isalpha(int c);

//Check if character is ascii.
int		ft_isascii(int c);

//Check if character is digit.
int		ft_isdigit(int c);

//Check if character is printable.
int		ft_isprint(int c);

//Converts a string to a number.
int		ft_atoi(const char *str);

//Converts a float to a number
char	*ft_ftoa(float n);

//Converts an unsigned int in a string to a hexadecimal string
void	ft_atoix(unsigned long i, char *buf, size_t size);

//Writes n zeroed bytes to the string s.
void	ft_bzero(void *s, size_t n);

//Allocate memory of size count * size and set all values to NULL.
void	*ft_calloc(size_t count, size_t size);

//Locates the first occurrence of c in string s.
void	*ft_memchr(const void *s, int c, size_t n);

//Compares byte string s1 against byte string s2.
int		ft_memcmp(const void *s1, const void *s2, size_t n);

/*
Copies n bytes from memory area src to memory area dst. 
The two strings may not overlap. If they do use ft_memmove instead.
*/
void	*ft_memcpy(void *dst, const void *src, size_t n);

void	*ft_memdup(void *p, size_t n);

/*
Copies len bytes from string src to string dst. The two strings may overlap; 
the copy is always done in a non-destructive manner.
*/
void	*ft_memmove(void *dst, const void *src, size_t len);

//Writes len bytes of value c.
void	*ft_memset(void *b, int c, size_t len);

//Converts an int to an string.
char	*ft_itoa(int n);

//Writes character c in file descriptor fd.
void	ft_putchar_fd(char c, int fd);

//Write string s in file descriptor fd.
void	ft_putstr_fd(char *s, int fd);

//Write s in file fd, and append a line end.
void	ft_putendl_fd(char *s, int fd);

//Write a number in file descriptor fd.
void	ft_putnbr_fd(int n, int fd);

//Read the next line in fd, NULL if all lines are read.
char	*ft_gnl(int fd);

t_list	*ft_gnl_save(void);

//Creates an array of int from min to max.
int		*ft_range(int min, int max);

//Creates an array of int from min to max and returns the size of the array.
int		ft_nrange(int **range, int min, int max);

//Itoa for unsigned int
char	*ft_uitoa(unsigned int n);

//Printf...
int		ft_printf(const char *str, ...);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strings.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 20:42:45 by reclaire          #+#    #+#             */
/*   Updated: 2022/12/31 12:14:27 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRINGS_H
# define FT_STRINGS_H

# include <stdlib.h>

//Append a at the end of b
char	*ft_str_append(char *a, char *b, int free_a, int free_b);

//Check if str is digit.
int		ft_str_isdigit(char *str);

//Returns the index of the first occurrence of c in str, -1 if not found.
int		ft_strgetindex(char *str, char c);

char	*ft_strcat(char *dest, char *src);

/*
Locates the first occurrence of c in the string pointed to by s.
The terminating null character taken into account.
*/
char	*ft_strchr(const char *s, int c);

//Duplicates the string s1 into a new char array
char	*ft_strdup(const char *s1);

/*
Appends string src to the end of dst.  
It will append at most dstsize - strlen(dst) - 1 characters. 
It will then NUL-terminate the new string
*/
size_t	ft_strlcat(char *dest, char *src, size_t size);

/*
Copies up to dstsize - 1 characters from the string src to dst, 
NUL-terminating the result if dstsize is not 0.
*/
size_t	ft_strlcpy(char *dest, char *src, size_t size);

//Returns the length of string s
size_t	ft_strlen(const char *s);

//Compares string s1 against string s2.
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/*
Locates the first occurrence of the null-terminated string needle in the 
string haystack, where not more than len characters are searched.
If to_find is an empty string, str is returned; if to_find occurs 
nowhere in str, NULL is returned; otherwise a pointer to the first
character of the first occurrence of to_find is returned.
*/
char	*ft_strnstr(const char *str, const char *to_find, size_t len);

//Locates the last occurrence of c in string s
char	*ft_strrchr(const char *s, int c);

//Converts a lower-case letter to the corresponding upper-case letter.
int		ft_tolower(int c);

//Converts a upper-case letter to the corresponding lower-case letter.
int		ft_toupper(int c);

//Returns a new string from s, starting at index start with size len.
char	*ft_substr(char const *s, unsigned int start, size_t len);

//Concatenate s1 and s2
char	*ft_strjoin(char const *s1, char const *s2);

//Creates a copy of s1 wihout the characters in set at end and start of string.
char	*ft_strtrim(char const *s1, char const *set);

//Splits string s by separator c.
char	**ft_split(char const *s, char c);

//Duplicates a split
char	**ft_dupsplit(char **s);

//Free a split
void	ft_freesplit(char **split);

//Returns the length of a split
int		ft_splitlen(char **split);

/*
Applies function f to each characters in string s, and returns
a new string of all the results of f.
*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

//Applies function f to each characters in string s.
void	ft_striteri(char *s, void (*f)(unsigned int, char *));

//Returns the index of the first occurrence of c in str, -1 if not found.
int		ft_strgetindex(char *str, char c);

#endif
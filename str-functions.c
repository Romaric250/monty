#include "monty.h"
size_t _strspn(const char *str1, const char *str2);
char *_strchr(const char *s, int c);
size_t _strpn(const char *str1, const char *str2);

/**
 * _strtok - divides a string into subsequent toekns.
 * @str: st to be toekenised
 * @delim: string to seprate the tokens one it is reached
 * Return: pointer to the tokens
 **/
char *_strtok(char *str, const char *delim)
{
	static char *s;

	if (str)
		s = str;
	else if (!s)
		return (0);
	str = s + _strspn(s, delim);
	s = str + _strpn(str, delim);
	if (s == str)
		return (s = 0);
	s = *s ? *s = 0, s + 1 : 0;
	return (str);
}

/**
 * _strcmp - function compares srtings.
 * @s1: string
 * @s2: string
 * Return: 0
 */

int _strcmp(char *s1, char *s2)
{
	int a;

	for (a = 0; s1[a] != '\0' && s2[a] != '\0'; a++)
	{
		if (s1[a] != s2[a])
			return ((int)s1[a] - s2[a]);
	}
	return (0);
}
/**
 * _strpn - locaate the first occurens of a st.
 * string pointed to by s2.
 * @str1: string2
 * @str2: string1
 * Return: len of seg
 **/
size_t _strpn(const char *str1, const char *str2)
{
	size_t i = 0;

	while (*str1)
	{
		if (_strchr(str2, *str1))
			return (i);
		str1++, i++;
	}
	return (i);
}
/**
 * _strspn - get the max length o a seg.
 * @str1: strint to compute the lengh
 * @str2: string 2
 * Return: length of seg.
 **/
size_t _strspn(const char *str1, const char *str2)
{
	size_t i = 0;

	while (*str1 && _strchr(str2, *str1++))
		i++;
	return (i);
}
/**
 * _strchr - gets the first occurnec of a string.
 * @str: string to search for occurrence.
 * @c: char to locate
 * Return: pointer to str
 **/
char *_strchr(const char *str, int c)
{
	while (*str != (char)c)
		if (!*str++)
			return (0);
	return ((char *)str);
}

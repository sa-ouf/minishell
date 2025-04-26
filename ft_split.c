
#include "minishell.h"

static int      count_word(const char *str, char c)
{
        int     count;

        count = 0;
        while (*str)
        {
                while (*str && *str == c)
                        str++;
                if (*str && *str != c)
                {
                        count++;
                        while (*str && *str != c)
                                str++;
                }
        }
        return (count);
}

static int      clear(char **str, size_t k)
{
        size_t  j;

        j = 0;
        while (j < k)
        {
                free(str[j]);
                j++;
        }
        free(str);
        return (0);
}

static size_t   len_words(const char *s, char sepera)
{
        size_t  len;

        len = 0;
        while (*s != sepera && *s)
        {
                s++;
                len++;
        }
        return (len);
}

static int      fill_str(char **ptr, const char *s, char sep)
{
        size_t  length;
        size_t  i;

        i = 0;
        while (*s)
        {
                length = 0;
                while (*s == sep && *s)
                        s++;
                length = len_words(s, sep);
                s += length;
                if (length > 0)
                {
                        ptr[i] = malloc((length + 1) * sizeof(char));
                        if (!ptr[i])
                                return (clear(ptr, i), -1);
                        memcpy(ptr[i], s - length, length);
                        ptr[i][length] = '\0';
                        i++;
                }
        }
        ptr[i] = NULL;
        return (0);
}

char    **ft_split(char const *s, char c)
{
        size_t  n;
        char    **ptr;

        if (!s)
                return (NULL);
        n = count_word(s, c);
        ptr = malloc((n + 1) * sizeof(char *));
        if (!ptr)
                return (NULL);
        if (fill_str(ptr, s, c) == 0)
                return (ptr);
        return (NULL);
}

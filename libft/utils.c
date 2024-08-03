#include "libft.h"

char *ft_strpbrk(const char *s, const char *accept)
{
    const char *a;

    while (*s) {
        for (a = accept; *a; ++a)
        {
            if (*s == *a)
            {
                return (char *)s;
            }
        }
        ++s;
    }
    return NULL;
}

size_t ft_strspn(const char *s, const char *accept) 
{
    const char *a;
    const char *p = s;

    while (*p) {
        for (a = accept; *a; ++a)
        {
            if (*p == *a)
            {
                break;
            }
        }
        if (*a == '\0')
        {
            return p - s;
        }
        ++p;
    }
    return p - s;
}

char *ft_strndup(const char *s, size_t n) {
    char *result;
    size_t len = ft_strlen(s);
    if (n < len) len = n;
    result = (char *)malloc(len + 1);
    if (result) {
        ft_memcpy(result, s, len);
        result[len] = '\0';
    }
    return result;
}

char *ft_strtok(char *str, const char *delim)
{
    static char *save_str;
    char *token;

    if (str == NULL)
        str = save_str;
    if (str == NULL)
        return NULL;

    str += ft_strspn(str, delim);
    if (*str == '\0')
    {
        save_str = NULL;
        return NULL;
    }
    token = str;
    str = ft_strpbrk(token, delim);
    if (str) {
        *str = '\0';
        save_str = str + 1;
    } else {
        save_str = NULL;
    }

    return token;
}
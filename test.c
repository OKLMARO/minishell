int	is_charset(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

void	free_split(char **tab, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int count_words(char *str)
{
    int count = 0;
    int in_word = 0;
    int in_quote = 0;
    char quote_char = 0;

    while (*str)
    {
        if (!in_quote && (*str == '\'' || *str == '"'))
        {
            in_quote = 1;
            quote_char = *str;
            if (!in_word)
            {
                in_word = 1;
                count++;
            }
        }
        else if (in_quote && *str == quote_char)
        {
            in_quote = 0;
        }
        else if (!in_quote && is_charset(*str))
        {
            in_word = 0;
        }
        else if (!in_word)
        {
            in_word = 1;
            count++;
        }
        str++;
    }
    return count;
}

char *ft_strndup_quote(char *str, int start, int end)
{
    char *dup;
    int i = 0;
    int j = start;
    int in_quote = 0;
    char quote_char = 0;

    dup = malloc(sizeof(char) * (end - start + 1));
    if (!dup)
        return NULL;
    while (j < end)
    {
        if (!in_quote && (str[j] == '\'' || str[j] == '"'))
        {
            in_quote = 1;
            quote_char = str[j];
        }
        else if (in_quote && str[j] == quote_char)
        {
            in_quote = 0;
        }
        else
        {
            dup[i++] = str[j];
        }
        j++;
    }
    dup[i] = '\0';
    return dup;
}


char **ft_split(char *str, int i, int j, int k)
{
    char **tab;
    int in_quote = 0;
    char quote_char = 0;

    tab = malloc(sizeof(char *) * (count_words(str) + 1));
    if (!tab)
        return NULL;
    while (str[i])
    {
        while (str[i] && is_charset(str[i]))
            i++;
        if (!str[i])
            break;

        j = i;
        while (str[i])
        {
            if (!in_quote && (str[i] == '\'' || str[i] == '"'))
            {
                in_quote = 1;
                quote_char = str[i];
            }
            else if (in_quote && str[i] == quote_char)
            {
                in_quote = 0;
            }
            else if (!in_quote && is_charset(str[i]))
                break;
            i++;
        }
        tab[k] = ft_strndup_quote(str, j, i);
        if (!tab[k])
        {
            free_split(tab, k);
            return NULL;
        }
        k++;
    }
    tab[k] = NULL;
    return tab;
}

int init_token(t_list **list)
{
	ft_lstadd_front(list, ft_lstnew("<"));
	ft_lstadd_front(list, ft_lstnew(">"));
	ft_lstadd_front(list, ft_lstnew("<<"));
	ft_lstadd_front(list, ft_lstnew(">>"));
	ft_lstadd_front(list, ft_lstnew("|"));
	ft_lstadd_front(list, ft_lstnew("$"));
	ft_lstadd_front(list, ft_lstnew("\""));
	ft_lstadd_front(list, ft_lstnew("'"));
	return (0);
}

char	*find_first_adr(char *res[])
{
	char	*min;
	int		i;

	i = 0;
	min = NULL;
	while (res[i])
	{
		if (min == NULL || min > res[i])
		{
			min = res[i];
			i++;
		}
	}
	return (min);
}

char	*is_token(t_list *list, char *token)
{
	char	*res[ft_lstsize(list)];
	t_list	*temp;
	int		i;

	temp = list;
	i = 0;
	while (temp)
	{
		if (ft_strnstr(token, temp->content, 3))
		{
			res[i] = ft_strnstr(token, temp->content, 3);
			i++;
		}
		temp = temp->next;
	}
	if (i == 0)
		return (NULL);
	if (i == 1)
		return (res[0]);
	return (find_first_adr(res));
}

void print_tokens(t_token *list)
{
    t_token *current = list;
    int i = 0;

    if (!current)
    {
        printf("(no tokens)\n");
        return;
    }
    while (current)
    {
        printf("Token[%d]: type=%d content=\"%s\" quote=%d\n",
               i, current->type, current->content, current->quote);
        current = current->next;
        i++;
    }
}

void free_tokens(t_token *list)
{
    t_token *current;
    t_token *next;

    current = list;
    while (current)
    {
        next = current->next;
        free(current->content);
        free(current);
        current = next;
    }
}

int main(void)
{
    t_token *tokens;
    char *test;

    // Test 8: Quotes vides
    printf("\n=== Test 8: echo '' ===\n");
    test = "echo ''";
    tokens = lexer(test);
    print_tokens(tokens);
    free_tokens(tokens);

    // Test 9: Quotes multiples
    printf("\n=== Test 9: echo 'hello' \"world\" test ===\n");
    test = "echo 'hello' \"world\" test";
    tokens = lexer(test);
    print_tokens(tokens);
    free_tokens(tokens);

    // Test 10: Espaces multiples
    printf("\n=== Test 10: echo    hello     world ===\n");
    test = "echo    hello     world";
    tokens = lexer(test);
    print_tokens(tokens);
    free_tokens(tokens);

    // Test 11: Pas d'espaces autour des redirections
    printf("\n=== Test 11: cat<file.txt ===\n");
    test = "cat<file.txt";
    tokens = lexer(test);
    print_tokens(tokens);
    free_tokens(tokens);

    // Test 12: Multiple redirections
    printf("\n=== Test 12: cat < in.txt > out.txt ===\n");
    test = "cat < in.txt > out.txt";
    tokens = lexer(test);
    print_tokens(tokens);
    free_tokens(tokens);

    // Test 13: Dollar dans single quotes (ne doit PAS être traité)
    printf("\n=== Test 13: echo '$USER' ===\n");
    test = "echo '$USER'";
    tokens = lexer(test);
    print_tokens(tokens);
    free_tokens(tokens);

    // Test 14: Dollar dans double quotes (doit être traité)
    printf("\n=== Test 14: echo \"$USER\" ===\n");
    test = "echo \"$USER\"";
    tokens = lexer(test);
    print_tokens(tokens);
    free_tokens(tokens);

    // Test 15: Quotes avec espaces au début/fin
    printf("\n=== Test 15: echo '  hello  ' ===\n");
    test = "echo '  hello  '";
    tokens = lexer(test);
    print_tokens(tokens);
    free_tokens(tokens);

    // Test 16: Caractères spéciaux protégés par quotes
    printf("\n=== Test 16: echo 'test|pipe>redirect$var' ===\n");
    test = "echo 'test|pipe>redirect$var'";
    tokens = lexer(test);
    print_tokens(tokens);
    free_tokens(tokens);

    // Test 17: Pipe multiple
    printf("\n=== Test 17: cat file | grep test | wc -l ===\n");
    test = "cat file | grep test | wc -l";
    tokens = lexer(test);
    print_tokens(tokens);
    free_tokens(tokens);

    // Test 18: Redirections multiples
    printf("\n=== Test 18: cat < in1.txt < in2.txt ===\n");
    test = "cat < in1.txt < in2.txt";
    tokens = lexer(test);
    print_tokens(tokens);
    free_tokens(tokens);

    // Test 19: Input vide
    printf("\n=== Test 19: (empty string) ===\n");
    test = "";
    tokens = lexer(test);
    print_tokens(tokens);
    free_tokens(tokens);

    // Test 20: Seulement des espaces
    printf("\n=== Test 20: '     ' (only spaces) ===\n");
    test = "     ";
    tokens = lexer(test);
    print_tokens(tokens);
    free_tokens(tokens);

    // Test 21: Dollar collé au texte
    printf("\n=== Test 21: echo prefix$USERsuffix ===\n");
    test = "echo prefix$USERsuffix";
    tokens = lexer(test);
    print_tokens(tokens);
    free_tokens(tokens);

    // Test 22: Quotes imbriquées de types différents
    printf("\n=== Test 22: echo 'test\"inside' ===\n");
    test = "echo 'test\"inside'";
    tokens = lexer(test);
    print_tokens(tokens);
    free_tokens(tokens);

    // Test 23: Double quotes avec single quote inside
    printf("\n=== Test 23: echo \"test'inside\" ===\n");
    test = "echo \"test'inside\"";
    tokens = lexer(test);
    print_tokens(tokens);
    free_tokens(tokens);

    // Test 24: Tokens collés
    printf("\n=== Test 24: echo hello'world' ===\n");
    test = "echo hello'world'";
    tokens = lexer(test);
    print_tokens(tokens);
    free_tokens(tokens);

    // Test 25: Quote non fermée (doit afficher erreur)
    printf("\n=== Test 25: echo 'not closed ===\n");
    test = "echo 'not closed";
    tokens = lexer(test);
    print_tokens(tokens);
    free_tokens(tokens);

    // Test 26: Double quote non fermée (doit afficher erreur)
    printf("\n=== Test 26: echo \"not closed ===\n");
    test = "echo \"not closed";
    tokens = lexer(test);
    print_tokens(tokens);
    free_tokens(tokens);

    return (0);
}

void	free_double(char **tab_str)
{
	int	i;

	i = 0;
	while (tab_str[i])
	{
		free(tab_str[i]);
		i++;
	}
	free(tab_str);
}

// Fonctions helper pour affichage
void print_tokens(t_token *tokens)
{
    t_token *current = tokens;
    int i = 0;

    printf("\n=== TOKENS ===\n");
    while (current)
    {
        printf("Token[%d]: type=%d content=\"%s\" quote=%d\n",
            i, current->type, current->content, current->quote);
        current = current->next;
        i++;
    }
    printf("==============\n\n");
}

void print_cmd_list(t_cmd *cmd_list)
{
    t_cmd *cmd = cmd_list;
    t_redirect *redir;
    int cmd_idx = 0;
    int i;

    printf("\n=== PARSED COMMANDS ===\n");
    while (cmd)
    {
        printf("Command[%d]:\n", cmd_idx);
        
        // Afficher argv
        printf("  argv: ");
        if (cmd->argv)
        {
            i = 0;
            while (cmd->argv[i])
            {
                printf("\"%s\" ", cmd->argv[i]);
                i++;
            }
        }
        else
            printf("(empty)");
        printf("\n");

		printf("  quote: ");
        if (cmd->argv)
        {
            i = 0;
            while (cmd->argv[i])
            {
                printf("\"%d\" ", cmd->quote[i]);
                i++;
            }
        }
        else
            printf("(empty)");
        printf("\n");

        // Afficher redirections
        printf("  redirects: ");
        redir = cmd->redirects;
        if (redir)
        {
            printf("\n");
            while (redir)
            {
                printf("    type=%d file=\"%s\"\n", redir->type, redir->file);
                redir = redir->next;
            }
        }
        else
            printf("(none)\n");
        
        cmd = cmd->next;
        cmd_idx++;
    }
    printf("=======================\n\n");
}
int main(void)
{
    char *test_cases[] = {
        "echo hello world",
        "cat < in.txt > out.txt",
        "ls -la | grep test | wc -l",
        "echo 'single quote' \"double quote\"",
        "cat << EOF > file.txt",
        "echo $USER $HOME",
        "ls | wc",
        NULL
    };
    
    int i = 0;
    t_token *tokens;
    t_cmd *cmd_list;

    printf("╔════════════════════════════════════════╗\n");
    printf("║   MINISHELL LEXER/PARSER TESTER       ║\n");
    printf("╚════════════════════════════════════════╝\n");

    while (test_cases[i])
    {
        printf("\n");
        printf("────────────────────────────────────────\n");
        printf("Test %d: %s\n", i + 1, test_cases[i]);
        printf("────────────────────────────────────────\n");
        
        // Lexer
        tokens = lexer(test_cases[i]);
        if (!tokens)
        {
            printf("❌ Lexer failed\n");
            i++;
            continue;
        }
        
        print_tokens(tokens);
        
        // Parser
        cmd_list = parser(tokens, 0);
        if (!cmd_list)
        {
            printf("❌ Parser failed\n");
            ft_tokendestroy(&tokens);
            i++;
            continue;
        }
        
        print_cmd_list(cmd_list);
        
        // Cleanup
        ft_tokendestroy(&tokens);
        ft_cmddestroy(&cmd_list);
        
        printf("✅ Test passed\n");
        i++;
    }

    printf("\n");
    printf("╔════════════════════════════════════════╗\n");
    printf("║         ALL TESTS COMPLETED            ║\n");
    printf("╚════════════════════════════════════════╝\n");

    return (0);
}

void	free_double(char **tab_str)
{
	int	i;

	i = 0;
	while (tab_str[i])
	{
		free(tab_str[i]);
		i++;
	}
	free(tab_str);
}

void print_test_header(char *test_name, int test_num)
{
    printf("\n");
    printf("════════════════════════════════════════\n");
    printf("Test %d: %s\n", test_num, test_name);
    printf("════════════════════════════════════════\n");
}

void print_cmd_before_after(t_cmd *cmd)
{
    int i;
    
    printf("\nBEFORE expansion:\n");
    i = 0;
    while (cmd->argv && cmd->argv[i])
    {
        printf("  argv[%d]: \"%s\" [quote=%d]\n", i, cmd->argv[i], cmd->quote[i]);
        i++;
    }
}

void print_after_expansion(t_cmd *cmd)
{
    int i;
    
    printf("\nAFTER expansion:\n");
    i = 0;
    while (cmd->argv && cmd->argv[i])
    {
        printf("  argv[%d]: \"%s\" [quote=%d]\n", i, cmd->argv[i], cmd->quote[i]);
        i++;
    }
}

void test_expand(char *input, char **env, int test_num)
{
    t_token *tokens;
    t_cmd *cmd_list;
    
    print_test_header(input, test_num);
    
    // Lexer + Parser
    tokens = lexer(input);
    if (!tokens)
    {
        printf("❌ Lexer failed\n");
        return;
    }
    
    cmd_list = parser(tokens, 0);
    if (!cmd_list)
    {
        printf("❌ Parser failed\n");
        ft_tokendestroy(&tokens);
        return;
    }
    
    // Afficher avant expansion
    print_cmd_before_after(cmd_list);
    
    // EXPANSION
    expand_varialbes(cmd_list, env);
    
    // Afficher après expansion
    print_after_expansion(cmd_list);
    
    printf("\n✅ Test completed\n");
    
    // Cleanup
    ft_tokendestroy(&tokens);
    ft_cmddestroy(&cmd_list);
}

int main(int argc, char **argv, char **env)
{
    printf("╔════════════════════════════════════════╗\n");
    printf("║    MINISHELL EXPANSION TESTER         ║\n");
    printf("╚════════════════════════════════════════╝\n");
    
    // Tests basiques
    test_expand("echo $USER", env, 1);
    test_expand("echo $HOME", env, 2);
    test_expand("echo $PATH", env, 3);
    
    // Variable inexistante
    test_expand("echo $TOTO", env, 4);
    
    // Avec single quotes (pas d'expansion)
    test_expand("echo '$USER'", env, 5);
    
    // Avec double quotes (expansion)
    test_expand("echo \"$USER\"", env, 6);
    
    // Mixte
    test_expand("echo $USER '$HOME' \"$PATH\"", env, 7);
    
    // Multiples variables
    test_expand("echo $USER $HOME $PWD", env, 8);
    
    // Variable + texte normal
    test_expand("echo hello $USER world", env, 9);
    
    // Sans $
    test_expand("echo hello world", env, 10);
    
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║      ALL EXPANSION TESTS COMPLETED     ║\n");
    printf("╚════════════════════════════════════════╝\n");
    
    return 0;
}

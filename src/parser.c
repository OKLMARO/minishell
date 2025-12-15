/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 11:52:29 by oamairi           #+#    #+#             */
/*   Updated: 2025/12/15 10:30:46 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_argv_to_cmd(t_cmd *cmd, char *argv)
{
	int		count;
	char	**new_argv;

	count = 0;
	while (cmd->argv && cmd->argv[count])
		count++;
	new_argv = malloc(sizeof(char *) * (count + 2));
	if (!new_argv)
		return ;
	count = 0;
	while (cmd->argv && cmd->argv[count])
	{
		new_argv[count] = cmd->argv[count];
		count++;
	}
	new_argv[count] = ft_strdup(argv);
	new_argv[count + 1] = NULL;
	free(cmd->argv);
	cmd->argv = new_argv;
}

bool	add_redirect_to_cmd(t_token *temp, t_cmd *new)
{
	t_redirect	*new_redirect;

	if (!temp->next || temp->next->type != WORD)
		return (ft_putstr_fd("unexpected element\n", 2), false);
	new_redirect = malloc(sizeof(t_redirect));
	if (!new_redirect)
		return (false);
	new_redirect->type = temp->type;
	new_redirect->file = ft_strdup(temp->next->content);
	if (!new_redirect->file)
		return (false);
	new_redirect->next = NULL;
	ft_redirectadd_back(&new->redirects, new_redirect);
	return (true);
}

int	parser_compare(t_token *temp, t_cmd **cmd_list, t_cmd **new)
{
	if (temp->type == PIPE)
		return (ft_cmdadd_back(cmd_list, *new), 0);
	else if (temp->type == WORD)
		add_argv_to_cmd(*new, temp->content);
	else
	{
		if (add_redirect_to_cmd(temp, *new) == true)
			return (1);
		else
			return (-1);
	}
	return (2);
}

t_cmd	*parser(t_token *token, int result)
{
	t_token	*temp;
	t_cmd	*new;
	t_cmd *cmd_list;

	temp = token;
	cmd_list = NULL;
	new = ft_cmdnew();
	if (!new)
		return (NULL);
	while (temp)
	{
		result = parser_compare(temp, &cmd_list, &new);
		if (result == -1)
			my_exit(&cmd_list, NULL, "unexpected element");
		else if (result == 0)
		{
			new = ft_cmdnew();
			if (!new)
				return (NULL);
		}
		else if (result == 1)
			temp = temp->next;
		temp = temp->next;
	}
	return (ft_cmdadd_back(&cmd_list, new), cmd_list);
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


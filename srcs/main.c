/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 02:02:52 by sucho             #+#    #+#             */
/*   Updated: 2023/08/08 05:08:02 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"


int	parse_read_node(char *line, int parse_status, t_list **node)
{
	t_node_xy *tmp;

	char **split_tmp;

	(void) parse_status;
	if (!parse_node_xy_check(line))
		return 0;

	tmp = (t_node_xy *)malloc(sizeof(t_node_xy));
	split_tmp = ft_split(line, ' ');
	tmp->name = split_tmp[0];
	tmp->x = split_tmp[1];
	tmp->y = split_tmp[2];
	tmp->node_type = parse_status;
	(*node)->content = tmp;

	// printf("name:[%s] x:[%s] y:[%s]\n", tmp->name, tmp->x, tmp->y);
	return 1;
}

int	check_split_count(char *line, char delim)
{
	char **tmp;
	int i;

	i = 0;
	tmp = ft_split(line, delim);
	while (tmp[i] != NULL)
		i++;
	return i;
}

int compare_nodename(void *content1, void *content2)
{
	int diff;
	t_node_xy *node_1;
	t_node_xy *node_2;

	node_1 = (t_node_xy *)content1;
	node_2 = (t_node_xy *)content2;
	// printf("node1:[%s] node2:[%s]\n", node_1->name, node_2->name);
	diff = ft_strncmp(node_1->name, node_2->name, ft_strlen(node_1->name));
	if (diff == 0)
		return (1);
	else
		return (0);
}

int check_duplicate_nodes(t_list *nodes_head)
{
	t_list *tmp;

	tmp = nodes_head;
	while(tmp != NULL)
	{
		t_list *other = tmp->next;

		// there'll be always 'number of nodes + 1' linked list nodes.
		if (tmp->content == NULL)
			break;

		while (other != NULL)
		{
			// there'll be always 'number of nodes + 1' linked list nodes.
			if (other->content == NULL)
				break;
			if (compare_nodename(tmp->content, other->content))
				return (0);
			other = other->next;
		}
		tmp = tmp->next;
	}
	return (1);
}

t_parse	*init_parse_struct(void)
{
	t_parse *parse;
	parse = (t_parse *)malloc(sizeof(t_parse));
	parse->nodes_head = ft_lstnew(NULL);
	parse->edge_info_head = ft_lstnew(NULL);
	return (parse);
}

int main(void)
{

	t_list	*lines;
	// t_list	*nodes_head;
	// t_list	*edge_info_head;
	t_list	*tmp;

	t_parse *parse;

	parse = init_parse_struct();

	int	line_count;
	int parse_status;

	// nodes_head = ft_lstnew(NULL);
	lines = ft_lstnew(NULL);
	parse_readlines(lines);

	line_count = 1;
	parse_status = 0;

	tmp = parse->nodes_head;
	while (lines != NULL)
	{
		parse_status = parse_check_line(lines->content, line_count, parse_status, &tmp);
		printf("[%s]\n", (char *)lines->content);
		if (!parse_status)
		{
			ft_putstr_fd("Error in line ", STDOUT_FILENO);
			ft_putnbr_fd(line_count, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
			exit(1);
		}
		else if (parse_status == PARSE_XY && tmp->content != NULL)
		{
			tmp->next = ft_lstnew(NULL);
			tmp = tmp->next;
		}
		lines = lines->next;
		line_count++;
	}
	// ft_lstdelone(tmp, free);
	printf("========================\n");

	if (!check_duplicate_nodes(parse->nodes_head))
	{
		ft_putstr_fd("duplicates node found", STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		exit(1);
	}

	ft_putstr_fd("lem-in\n", STDOUT_FILENO);

	return (0);
}

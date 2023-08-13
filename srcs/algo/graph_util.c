#include "../../includes/lem-in.h"

static void	swap_start_end(char **node_map, char *start, char *end, int array_len)
{
	int i;
	char *str_tmp;

	i = 0;
	while (i < array_len)
	{
		if (ft_strncmp(node_map[i], start, ft_strlen(start)) == 0)
		{
			str_tmp = node_map[0];
			node_map[0] = start;
			node_map[i] = str_tmp;
			break;
		}
		i++;
	}
	i = 0;
	while (i < array_len)
	{
		if (ft_strncmp(node_map[i], end, ft_strlen(end)) == 0)
		{
			str_tmp = node_map[array_len - 1];
			node_map[array_len - 1] = end;
			node_map[i] = str_tmp;
			break;
		}
		i++;
	}
}

char	**node_map_to_array(t_list *nodes_head)
{
	char **ret;
	int i;
	t_node_xy *tmp;
	char *start;
	char *end;

	ret = (char**)malloc(sizeof(char*) * (ft_lstsize(nodes_head) + 1));
	start = NULL;
	end = NULL;
	i = 0;
	while (nodes_head != 0)
	{
		tmp = nodes_head->content;
		ret[i] = tmp->name;
		if (tmp->node_type == PARSE_XY_START)
			start = tmp->name;
		else if (tmp->node_type == PARSE_XY_END)
			end = tmp->name;
		nodes_head = nodes_head->next;
		i++;
	}
	swap_start_end(ret, start, end, i);
	return (ret);
}

int	node_find_index(char **node_array, char *node_name)
{
	int i;

	i = 0;
	(void) node_name;
	while (node_array[i] != NULL)
	{
		if (ft_strncmp(node_array[i], node_name, ft_strlen(node_name)) == 0)
			break ;
		i++;
	}
	return i;
}

void	print_graph_mapping(int list_size, char **node_map)
{
	int i = 0;
	while (i < list_size)
	{
		printf("index: %d, str:[%s]\n", i, node_map[i]);
		i++;
	}
}

char **init_nodes_mapping(int list_size)
{
	char **nodes_map;

	nodes_map = (char **)malloc(sizeof(char *) * (list_size + 1));

	int i = 0;
	while (i < list_size)
	{
		nodes_map[i] = (char *)malloc(sizeof(char *) + 1);
		i++;
	}
	nodes_map[i] = NULL;
	return (nodes_map);
}

#include "../includes/queue.h"
#include "../includes/lem-in.h"

void    init_paths_ants(t_paths_ants* paths_ants, int num_paths)
{
    printf("num_paths:%d\n", num_paths);
    paths_ants->paths_ants = (t_ants**)malloc(sizeof(t_ants*) * (num_paths + 1));
    //for (int i = 0; i < num_paths; ++i)
    //	paths_ants->paths_ants[i] = (t_ants*)malloc(sizeof(t_ants) * (elements[i].num_ants + 1));
}

void    init_ants(t_ants* ants, t_path_len *elements, int num_paths)
{
    printf("num_paths:%d\n", num_paths);
    ants->movements_list = (t_path_list**)malloc(sizeof(t_path_list*) * (num_paths + 1));
    for (int i = 0; i < num_paths; ++i)
    	ants->movements_list[i] = (t_path_list*)malloc(sizeof(t_path_list) * (elements[i].num_ants + 1));
}

void	print_ant_movement(t_route *route, int num_ants)
{
	t_path_list *curr;
	(void)num_ants;

	//for(int i = 0; i < route->paths->num_paths; i++)
    {
		int i = 0;
		curr = route->paths->paths_list[i];
		//printf("forward\n");
        while (curr->next != NULL)
		{
			//printf("%d\n", curr->vertex);
            curr = curr->next;
		}
		/*
		//curr = route->paths->paths_list[i];
		printf("backard\n");
        while (curr->prev != NULL)
		{
            curr = curr->prev;
			printf("%d\n", curr->vertex);
		}
		*/
        while (curr->prev != NULL)
        {
            curr = curr->prev;
			printf("%dL%d-%s", num_ants, ++curr->count_ants, route->node_map[curr->vertex]);
			if (curr->prev != NULL && num_ants != curr->count_ants)
				printf("\n");
			else
				printf(" ");
        }
    }
}

void    print_test(t_route *route, t_path_len *elements)
{
    printf("\n\n==================print test=====================\n\n");

	t_paths_ants paths_ants;
	t_ants ants;
	int	max_num_ants = 0;

    init_ants(&ants, elements, route->paths->num_paths);
    init_paths_ants(&paths_ants, route->paths->num_paths);
	for(int i = 0; i < route->paths->num_paths; ++i)
    {
		if (max_num_ants < elements[i].num_ants)
			max_num_ants = elements[i].num_ants;
	}
	printf("max num ants:%d\n\n", max_num_ants);
	for(int i = 0; i < route->paths->num_paths; ++i)
	{
    	for (int j = 0; j < elements[i].num_ants; ++j)
		{
			ants.movements_list[j] = route->paths->paths_list[i];
    	}
	}
    for (int i = 0; i < max_num_ants; ++i)
	{
		print_ant_movement(route, elements[0].num_ants--);
    }

	return ;

/*
    t_t q;

    init_q(&q, route->paths->num_paths);
	for(int i = 0; i < route->paths->num_paths; i++)
    {
        init_queue(q.lst[i]);
		if (max_num_ants < elements[i].num_ants)
			max_num_ants = elements[i].num_ants;
		t_path_list *curr = route->paths->paths_list[i];
        while (curr->next != NULL)
        {
			if (elements[i].num_ants > 0)
            	enqueue(q.lst[i], curr->vertex);
            curr = curr->next;
        }
		printf("elements - value: %d\t index:%d\tnum_ants:%d\n", 
			elements[i].value, elements[i].index, elements[i].num_ants);
    }
    //int v;
	
	printf("max num ants:%d\n\n", max_num_ants);
    for (int i = 0; i < max_num_ants; ++i)
	{
		for(int j = 0; j < route->paths->num_paths; ++j)
    	{
			t_path_list *curr = route->paths->paths_list[j];
    	    //v = route->paths->paths_list[0]->content;
    	    //printf("L%d-%d", curr->count_ants, dequeue(q.lst[0]));
			if (!is_empty(q.lst[j]))
			{
    	    	printf("L%d-%d", ++curr->count_ants, dequeue(q.lst[j]));
				curr = curr->next;
			}
    	    //printf("L%d-%d", curr->count_ants, curr->vertex);
    	    printf(" ");
    	    //printf("\n");
    	}
	}
	*/
}

int	main(void)
{
	t_parse	*parse;
	//t_paths	paths;
	t_route	route;

	int	capacity[MAX_VERTICES][MAX_VERTICES] = {0};
	int	temp[MAX_VERTICES][MAX_VERTICES] = {0};
	int	parent[MAX_VERTICES];

	parse = parsing();
	printf("parse result:\n");
	parse_result_print(parse);
	route.num_ants = parse->num_ants;
	route.graph = parse_to_graph(parse);

	/*
	**	create node map 
	*/
	init_route(&route, parse);
	//init_paths(&paths);

	printf("number of vertices: %d\n", route.num_vertices);
	printf("start: (%d)\n", route.start);
	printf("end: (%d)\n", route.end);
	fill_capacity(route.graph, capacity);
	//print_capacity(capacity, route.num_vertices);

	/*
	**	edmonds-karp
	*/
	edmonds_karp(&route, route.paths, parent, capacity);
	int i = 0;
	while (i < (route.list_size))
	{
		printf("index: %d, str:[%s]\n", i, route.node_map[i]);
		i++;
	}
	//print_capacity(capacity, route.num_vertices);
	//printf("disjoin paths:\n");
	//print_paths(&route, &paths);

	/*
	**	create new temp capacity based on the updated capacity
	*/
	fill_capacity(route.graph, temp);
	for (int u = 0; u < route.num_vertices; ++u)
	{
		for (int v = 0; v < route.num_vertices; ++v)
		{
			if (capacity[u][v] == 1)
				temp[u][v] = 0;
		}
	}
	//print_capacity(temp, route.num_vertices);

	/*
	** run edmonds-karp with new temp capacity	
	*/
	init_paths(route.paths);
	edmonds_karp(&route, route.paths, parent, temp);

	printf("\n\ndisjoin paths:\n");
	print_paths(&route, route.paths);
	print_paths_list(route.paths);
	t_path_len *elements =distribute_ant(route);
	for(int i = 0; i < route.paths->num_paths; i++)
		printf("elements - value: %d\t index:%d\tnum_ants:%d\n", 
			elements[i].value, elements[i].index, elements[i].num_ants);

    print_test(&route, elements);

	return (0);
}

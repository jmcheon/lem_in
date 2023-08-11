#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50


void init(t_graph *graph)
{
	int v;

	graph->n = 0;
	v = 0;
	while(v < MAX_VERTICES)
	{
		graph->adj_list[v] = NULL;
		v++;
	}
}


void insert_vertex(t_graph *g, int v)
{
	if(((g->n)+1)>MAX_VERTICES){
        fprintf(stderr,"overflow");
        return;
    }
    g->n++;
}

// link in reverse way
// void insert_edge(t_graph *g, int u, int v)
// {
// 	t_graph_node* node;
//     if(u>=g->n||v>=g->n){
//         fprintf(stderr,"vertex index error");
//         return;
//     }

// 	node = (t_graph_node *)malloc(sizeof(t_graph_node));
// 	node->vertex = v;
// 	node->link = g->adj_list[u];
// 	g->adj_list[u] = node;
// }

void insert_edge(t_graph* g, int u, int v) {
    if (u >= g->n || v >= g->n) {
        printf("vertex index error\n");
        return;
    }

    // create a new edge node
    t_graph_node* new_edge = malloc(sizeof(t_graph_node));
    new_edge->vertex = v;
    new_edge->link = NULL;

    // add new edge node to the end of the adjacency list for vertex u
    if (g->adj_list[u] == NULL) {
        g->adj_list[u] = new_edge;
    } else {
        t_graph_node* curr = g->adj_list[u];
        while (curr->link != NULL) {
            curr = curr->link;
        }
        curr->link = new_edge;
    }
}

void print_adj_list(t_graph *g)
{
	int i;
	int j;

	i = 0;
	while (i < g->n)
	{
		t_graph_node *p = g->adj_list[i];
		printf("node [%d]", i);
		while (p != NULL)
		{
			printf("->%d", p->vertex);
			p = p->link;
		}
		printf("\n");
		i++;
	}
}

int main()
{
    t_graph *g;
    g = (t_graph*)malloc(sizeof(t_graph));

    init(g);
    for(int i=0 ; i<4; i++)
        insert_vertex(g,i);
    insert_edge(g,0,1);
    insert_edge(g,1,0);
    insert_edge(g,0,2);
    insert_edge(g,2,0);
    insert_edge(g,0,3);
    insert_edge(g,3,0);
    insert_edge(g,1,2);
    insert_edge(g,2,1);
    insert_edge(g,2,3);
    insert_edge(g,3,2);
    print_adj_list(g);

    free(g);

    return 0;


}

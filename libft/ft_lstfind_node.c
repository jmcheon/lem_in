#include "libft.h"
#include <stdio.h>

t_list	*ft_lstfind_node(t_list *lst, int index)
{
	int i;

	if (lst == NULL)
		return (NULL);
	if (index == 0)
	{
		//printf("current index is the head node...\n");
		return (lst);
	}
	i = 1;
	while (lst->next)
	{
		if (i == index)
		{
			//printf("current index for path has found...\n");
			return (lst->next);
		}
		// printf("(i, index) = (%d, %d)\n",i , index);
		i++;
		lst = lst->next;
	}
	return (NULL);
}

#include "libft.h"
#include <stdio.h>

t_list	*ft_lstfind_node(t_list *lst, int index)
{
	int i;

	if (lst == NULL)
		return (NULL);
	if (index == 0)
	{
		return (lst);
	}
	i = 1;
	while (lst->next)
	{
		if (i == index)
		{
			return (lst->next);
		}
		i++;
		lst = lst->next;
	}
	return (NULL);
}

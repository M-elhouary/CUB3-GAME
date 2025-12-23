/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 18:13:38 by moirhira          #+#    #+#             */
/*   Updated: 2025/12/22 12:21:13 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_memory_alloc	**get_mem_head(void)
{
	static t_memory_alloc	*head;

	return (&head);
}

void	*ft_malloc(size_t size)
{
	void			*allocated_mem;
	t_memory_alloc	*new_node;
	t_memory_alloc	**head;

	head = get_mem_head();
	allocated_mem = malloc(size);
	if (!allocated_mem)
	{
		printf("Error\nFrom malloc\n");
		free_all_memory();
		exit(1);
	}
	new_node = malloc(sizeof(t_memory_alloc));
	if (!new_node)
	{
		free(allocated_mem);
		free_all_memory();
		exit(1);
	}
	new_node->mem_segment = allocated_mem;
	new_node->next = *head;
	*head = new_node;
	return (allocated_mem);
}

void	free_all_memory(void)
{
	t_memory_alloc	**head;
	t_memory_alloc	*cur_node;
	t_memory_alloc	*next_node;

	head = get_mem_head();
	if (!head || !*head)
		return ;
	cur_node = *head;
	while (cur_node != NULL)
	{
		next_node = cur_node->next;
		free(cur_node->mem_segment);
		free(cur_node);
		cur_node = next_node;
	}
	*head = NULL;
}

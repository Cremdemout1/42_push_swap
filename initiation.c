/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:43:38 by ycantin           #+#    #+#             */
/*   Updated: 2024/10/13 15:29:08 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./push_swap.h"

int	empty_arg(char *argv)
{
	int	i;
	int	found;

	i = 0;
	found = 1;
	while (argv[i])
	{
		if (ft_isascii(argv[i]) && argv[i] != ' ' && argv[i] != '\0')
			return (0);
		i++;
	}
	return (found);
}

char	*onearg(int argc, char **argv)
{
	int		i;
	char	*temp;
	char	*spaced;

	if (argc <= 1 || argv == NULL)
		return (ft_strdup(""));
	i = 1;
	spaced = ft_strdup("");
	while (i < argc)
	{
		if (empty_arg(argv[i]))
		{
			free(spaced);
			return (NULL);
		}
		else if (i == 1)
			temp = ft_strdup(argv[1]);
		else
			temp = ft_strjoin(spaced, argv[i]);
		free(spaced);
		spaced = ft_strjoin(temp, " ");
		free(temp);
		i++;
	}
	return (spaced);
}

char	**all_args(int argc, char **argv)
{
	char	*one;
	char	**array;

	one = onearg(argc, argv);
	if (!one)
	{
		write(2, "Error\n", 6);
		return (NULL);
	}
	array = ft_split(one, ' ');
	if (array == NULL)
	{
		free(one);
		exit(1);
	}
	free(one);
	if (arg_validity(array) == 1)
	{
		write(2, "Error\n", 6);
		free_str_array(array);
		return (NULL);
	}
	else
		return (array);
}

void	stack_creat(t_stack **stack, int argc, char **argv)
{
	char	**array_arg;
	t_stack	*node_new;
	long	content;
	int		i;

	i = 0;
	array_arg = all_args(argc, argv);
	if (array_arg == NULL)
		exit(1);
	while (array_arg[i])
	{
		content = ft_atol(array_arg[i]);
		if (content > INT_MAX || content < INT_MIN
			|| ft_strlen(array_arg[i]) > 11)
			free_all(stack, array_arg, "Error\n", 6);
		node_new = ft_lstnew(content);
		if (!node_new)
			free_all(stack, array_arg, "Error\n", 6);
		ft_lstadd_back(stack, node_new);
		i++;
	}
	if (duplicate_checker(stack) == 1)
		free_all(stack, array_arg, "Error\n", 6);
	free_str_array(array_arg);
}

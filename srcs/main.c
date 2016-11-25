/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroussea <vroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 16:12:41 by vroussea          #+#    #+#             */
/*   Updated: 2016/11/25 11:11:03 by vroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/OpenClproject.h"

int	main(void)
{
//	cl_command_queue	command_queue;
	cl_kernel			kernel;
//	cl_mem				memobj;

	if (!(kernel = get_kernel()))
	{
		ft_putendl("Program abort");
		return (1);
	}
	return (0);
}

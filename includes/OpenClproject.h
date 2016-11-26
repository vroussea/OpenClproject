/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenClproject.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroussea <vroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 16:47:08 by vroussea          #+#    #+#             */
/*   Updated: 2016/11/26 15:16:23 by vroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENCLPROJECT_H

# define OPENCLPROJECT_H

# ifdef __APPLE__
# include <OpenCL/opencl.h>
# else
# include <cl.h>
# endif

# include "../libft/includes/libft.h"
# include <OpenCL/opencl.h>

# define SOURCE_SIZE 10000

cl_kernel	get_kernel(cl_context *context, cl_program *prog, cl_mem *memobj);
void		*error_msg(char *str);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenClproject.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroussea <vroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 16:47:08 by vroussea          #+#    #+#             */
/*   Updated: 2016/12/01 18:19:07 by vroussea         ###   ########.fr       */
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

# define SOURCE_SIZE 0x100000

char		*load_source_code();
cl_context	get_context(cl_device_id *dvic);
cl_program	build_program(char *src, cl_context ctxt, cl_device_id dvic);
cl_kernel	init_kernel(cl_program prog);
cl_command_queue	init_queue(cl_context ctxt, cl_device_id dvic);
cl_mem		*tab_buffer(cl_context context, size_t nb);
void		*error_msg(char *str);

#endif

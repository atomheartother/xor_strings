#ifndef _OPTIONS_H_
# define _OPTIONS_H_

typedef struct	s_options
{
  int		fd;
}		t_optn;

void	init_optns(t_optn *options);
void	end_optns(t_optn *options);
int	get_args(int ac, char **av, char **key, t_optn *options);

#endif 

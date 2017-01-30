#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "defines.h"
#include "options.h"

void	init_optns(t_optn *o)
{
  o->fd = STDIN_FILENO;
}

void	end_optns(t_optn *o)
{
  if (o->fd != STDIN_FILENO)
    close(o->fd);
}

int	set_file(char **av, int *i, t_optn *options)
{
  if (!av[*i])
    {
      fprintf(stderr, USAGE);
      return 1;
    }
  if (options->fd != STDIN_FILENO)
    {
      fprintf(stderr, "You can only xor from one file!\n");
      return 1;
    }
  
  char	*filename = av[*i];
  int	fd;

  if ((fd = open(filename, O_RDONLY)) == -1)
    {
      perror(av[*i]);
      return 1;
    }
  options->fd = fd;
  *i += 1;
  return 0;
}

int	get_option(char **av, int *i, t_optn *options)
{
  static char	*op[] = {"f", 0};
  int	(*funcs[])(char **av, int *i, t_optn *options) = {&set_file, 0};

  unsigned x;
  while (op[x])
    {
      if (!strcmp(av[*i] + 1, op[x]))
	{
	  *i += 1;
	  return funcs[x](av, i, options);
	}
      x++;
    }
  fprintf(stderr, "Unrecognized option: %s\n", av[*i]);
  *i += 1;
  return 1;
}

int	get_args(int ac, char **av, char **key, t_optn *options)
{
  int	i = 1;
  while (i < ac)
    {
      if (av[i][0] == '-')
	{
	  if (get_option(av, &i, options))
	    return 1;
	}
      else if (!*key)
	*key = av[i++];
      else
	{
	  fprintf(stderr, "Unexpected argument: %s\n", av[i]);
	  return 1;
	}
    }
  if (!*key)
    {
      fprintf(stderr, USAGE);
      return 1;
    }
  return 0;
}

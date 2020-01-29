#include <stdio.h>
#include <unistd.h>

#include "defines.h"
#include "options.h"
#include "xor.h"

int	main(int ac, char **av)
{
  if (ac < 2)
    {
      fprintf(stderr, USAGE);
      return 1;
    }

  char		*key = NULL;
  t_optn	options;
  init_optns(&options);

  if (get_args(ac, av, &key, &options))
    return 1;
  do_xor(key, &options);

  end_optns(&options);
  return 0;
}

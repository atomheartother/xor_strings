#include <stdio.h>
#include <unistd.h>
#include "options.h"
#include "string.h"

void	apply_key(char *buffer, char *key, const ssize_t string_len)
{
  const unsigned key_len = strlen(key);
  if (!key_len)
    return ;

  unsigned i = 0;
  while (i < string_len)
    {
      buffer[i] ^= key[i % key_len];
      i++;
    }
}

void	do_xor(char *key, t_optn *options)
{
  const size_t BUFFER_SIZE = 1024;

  char		buffer[BUFFER_SIZE + 1];
  ssize_t	len;
  while ((len = read(options->fd, buffer, BUFFER_SIZE)) > 0)
    {
      buffer[len] = 0;
      apply_key(buffer, key, len);
      write(STDOUT_FILENO, buffer, len);
    }
  if (len == -1)
    perror("read");  
}

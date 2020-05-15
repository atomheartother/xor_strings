#include <stdio.h>
#include <unistd.h>
#include "options.h"
#include "string.h"

ssize_t	apply_key(unsigned char *buffer, const char *key, const ssize_t string_len, const size_t key_len, const ssize_t iOffset)
{
  ssize_t i = 0;
  while (i < string_len)
    {
      buffer[i] ^= key[(i + iOffset) % key_len];
      i++;
    }
    return (i + iOffset) % key_len;
}

void	do_xor(const char *key, t_optn *options)
{
  const size_t BUFFER_SIZE = 1024;

  unsigned char		buffer[BUFFER_SIZE + 1];
  ssize_t	len;
  ssize_t iOffset = 0;
  const size_t key_len = strlen(key);
  if (!key_len) return;
  while ((len = read(options->fd, buffer, BUFFER_SIZE)) > 0)
    {
      buffer[len] = 0;
      iOffset = apply_key(buffer, key, len, key_len, iOffset);
      write(STDOUT_FILENO, buffer, len);
    }
  if (len == -1)
    perror("read");  
}

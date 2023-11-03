#include "main.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

/**
 * read_textfile - Reads a text file and prints it to POSIX stdout.
 *
 * @filename : name of the file
 * @letters : number of letters to read and print
 *
 * Return : The actual number of letters to read and print
 */
ssize_t read_textfile(const char *filename, size_t letters)
{
int file_descriptor;
ssize_t bytes_read, bytes_written;
char *data_buffer;
if (filename == NULL)
return (0);
file_descriptor = open(filename, O_RDONLY);
if (file_descriptor == -1)
return (0);
data_buffer = malloc(sizeof(char) * letters);
if (data_buffer == NULL)
{
close(file_descriptor);
return (0);
}
bytes_read = read(file_descriptor, data_buffer, letters);
close(file_descriptor);
if (bytes_read == -1)
{
free(data_buffer);
return (0);
}
bytes_written = write(STDOUT_FILENO, data_buffer, bytes_read);
free(data_buffer);
if (bytes_written != bytes_read)
return (0);
return (bytes_written);
}

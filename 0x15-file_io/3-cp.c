#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFSIZE 1024
/**
 * open_source_file - Opens the source file for reading.
 *
 * @file_from: Name of the source file.
 *
 * Return: File descriptor on success, -1 on failure.
 */
int open_source_file(const char *file_from)
{
int fd_from = open(file_from, O_RDONLY);
return (fd_from);
}
/**
 * open_destination_file - Opens the destination file for writing.
 *
 * @file_to: Name of the destination file.
 *
 * Return: File descriptor on success, -1 on failure.
 */
int open_destination_file(const char *file_to)
{
int fd_to = open(file_to, O_WRONLY | O_CREAT | O_TRUNC,
S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
return (fd_to);
}
/**
 * copy_file_content - Copies the content from source to destination.
 *
 * @fd_from: File descriptor for the source file.
 * @fd_to: File descriptor for the destination file.
 *
 * Return: 0 on success, -1 on failure.
 */
int copy_file_content(int fd_from, int fd_to)
{
char buffer[BUFSIZE];
ssize_t bytes_read, bytes_written;
while ((bytes_read = read(fd_from, buffer, BUFSIZE)) > 0)
{
bytes_written = write(fd_to, buffer, bytes_read);
if (bytes_written != bytes_read)
{
return (-1);
}
}
return (bytes_read == (-1) ? (-1) : (0));
}
/**
 * main - Copies the content of a file to another file.
 *
 * @argc: Number of command-line arguments.
 * @argv: Array of command-line arguments.
 *
 * Return: 0 on success, 97, 98, 99, or 100 on failure.
 */
int main(int argc, char *argv[])
{
int fd_from, fd_to;
if (argc != 3)
{
dprintf(STDERR_FILENO, "Usage: %s file_from file_to\n", argv[0]);
return (97);
}
fd_from = open_source_file(argv[1]);
if (fd_from == -1)
{
dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", argv[1]);
return (98);
}
fd_to = open_destination_file(argv[2]);
if (fd_to == -1)
{
dprintf(STDERR_FILENO, "Error: Can't write to file %s\n", argv[2]);
close(fd_from);
return (99);
}
if (copy_file_content(fd_from, fd_to) == -1)
{
dprintf(STDERR_FILENO, "Error: Can't write to file %s\n", argv[2]);
close(fd_from);
close(fd_to);
return (99);
}
if (close(fd_from) == -1)
{
dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd_from);
return (100);
}
if (close(fd_to) == -1)
{
dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd_to);
return (100);
}
return (0);
}

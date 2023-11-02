#include "main.h"
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
/**
 * append_text_to_file - Appends text to the end of a file.
 *
 * @filename: name of the file
 * @text_content: NULL-terminated string to append to the file
 *
 * Return: 1 on success, -1 on failure
 */
int append_text_to_file(const char *filename, char *text_content)
{
int file_descriptor;
ssize_t bytes_written;
if (filename == NULL)
return (-1);
if (text_content == NULL)
return (1);
file_descriptor = open(filename, O_WRONLY | O_APPEND);
if (file_descriptor == -1)
return (-1);
bytes_written = write(file_descriptor, text_content, strlen(text_content));
close(file_descriptor);
if (bytes_written == -1)
return (-1);
return (1);
}

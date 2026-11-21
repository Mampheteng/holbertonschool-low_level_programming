#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

/**
 * copy_file - copies contents from one file to another
 * @fd_from: source file descriptor
 * @fd_to: destination file descriptor
 * @filename: destination filename
 *
 * Return: 0 on success, 98 on read failure, 99 on write failure
 */
int copy_file(int fd_from, int fd_to, char *filename)
{
	char buffer[BUFFER_SIZE];
	ssize_t r, w, total_written;

	while ((r = read(fd_from, buffer, BUFFER_SIZE)) > 0)
	{
		total_written = 0;

		while (total_written < r)
		{
			w = write(fd_to, buffer + total_written,
				  r - total_written);
			if (w <= 0)
			{
				dprintf(STDERR_FILENO,
					"Error: Can't write to %s\n", filename);
				return (99);
			}
			total_written += w;
		}
	}

	if (r == -1)
		return (98);

	return (0);
}

/**
 * open_files - opens source and destination files
 * @argv: program arguments
 * @fd_from: pointer to source file descriptor
 * @fd_to: pointer to destination file descriptor
 *
 * Return: 0 on success, 98 or 99 on failure
 */
int open_files(char **argv, int *fd_from, int *fd_to)
{
	*fd_from = open(argv[1], O_RDONLY);
	if (*fd_from == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't read from file %s\n", argv[1]);
		return (98);
	}

	*fd_to = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (*fd_to == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't write to %s\n", argv[2]);
		close(*fd_from);
		return (99);
	}

	return (0);
}

/**
 * main - copies the content of a file to another file
 * @argc: number of arguments
 * @argv: array of arguments
 *
 * Return: 0 on success, or the specified error code
 */
int main(int argc, char *argv[])
{
	int fd_from, fd_to, status;

	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}

	status = open_files(argv, &fd_from, &fd_to);
	if (status != 0)
		exit(status);

	status = copy_file(fd_from, fd_to, argv[2]);

	if (status == 98)
		dprintf(STDERR_FILENO,
			"Error: Can't read from file %s\n", argv[1]);

	if (close(fd_from) == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't close fd %d\n", fd_from);
		exit(100);
	}

	if (close(fd_to) == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't close fd %d\n", fd_to);
		exit(100);
	}

	return (status);
}


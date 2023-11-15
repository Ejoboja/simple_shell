#include "shell.h"

/**
* get_history_file - gets the history file path
* @info: parameter struct
*
* Return: allocated string containing history file path
*/
	char *get_history_file(info_t *info)
	{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
	return (NULL);

	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
	{
	free(dir);
	return (NULL);
	}

	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);

	free(dir);
	return (buf);
}

/**
* write_history - writes command history to a file
* @info: the parameter struct
*
* Return: 1 on success, else -1
*/
	int write_history(info_t *info)
	{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
	return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	free(filename);

	if (fd == -1)
	return (-1);

	for (node = info->history; node; node = node->next)
	{
	_putsfd(node->str, fd);
	_putfd('\n', fd);
	}

	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
* read_history - reads command history from a file
* @info: the parameter struct
*
* Return: histcount on success, 0 otherwise
*/
	int read_history(info_t *info)
	{
	int linecount = 0;
	ssize_t fd, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
	return (0);

	fd = open(filename, O_RDONLY);
	free(filename);

	if (fd == -1)
	return (0);

	if (!fstat(fd, &st))
	fsize = st.st_size;

	if (fsize < 2)
	return ((close(fd), 0));

	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
	return ((close(fd), 0));

	ssize_t rdlen = read(fd, buf, fsize);

	buf[fsize] = 0;

	if (rdlen <= 0)
	return ((free(buf), close(fd), 0));

	close(fd);

	int last = 0, i;

	for (i = 0; i < fsize; i++)
	{
	if (buf[i] == '\n')
	{
	buf[i] = 0;
	build_history_list(info, buf + last, linecount++);
	last = i + 1;
	}
}

	if (last != i)
	build_history_list(info, buf + last, linecount++);

	free(buf);
	info->histcount = linecount;

	while (info->histcount-- >= HIST_MAX)
	delete_node_at_index(&(info->history), 0);

	renumber_history(info);
	return (info->histcount);
}

/**
* build_history_list - adds entry to a history linked list
* @info: parameter struct
* @buf: buffer
* @linecount: the history line count
*
* Return: Always 0
*/
	int build_history_list(info_t *info, char *buf, int linecount)
	{
	list_t *node = NULL;

	if (info->history)
	node = info->history;

	add_node_end(&node, buf, linecount);

	if (!info->history)
	info->history = node;

	return (0);
}

/**
* renumber_history - renumbers the history linked list after changes
* @info: parameter struct
*
* Return: the new histcount
*/
	int renumber_history(info_t *info)
	{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
	node->num = i++;
	node = node->next;
	}

	return (info->histcount = i);
}

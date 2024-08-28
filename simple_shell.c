#include "simple_shell.h"
/**
 * main - Entry point of the shell
 *
 * Return: 0 on success
 */
int main(void)
{
char *input = NULL; /* Buffer for user input */
size_t len = 0; /* Buffer length */
ssize_t read; /* Read status */
while (1) /* Infinite loop for shell prompt */
{
prompt(); /* Display prompt */
read = getline(&input, &len, stdin); /* Read user input */
if (read == -1) /* Check for EOF */
{
free(input);
exit(0); /* Exit on EOF */
}
execute_command(input); /* Execute the command */
}
free(input); /* Free allocated memory */
return (0); /* Return success */
}
/**
 * prompt - Displays the shell prompt
 */
void prompt(void)
{
write(STDOUT_FILENO, "#cisfun$ ", 9); /* Display the prompt */
}
/**
 * execute_command - Executes the given command
 * @input: The command to execute
 */
void execute_command(char *input)
{
pid_t pid; /* Process ID */
int status; /* Status of executed command */
char **argv; /* Command arguments */
char *command_path; /*Command path*/

input[strcspn(input, "\n")] = 0; /* Remove newline character */
argv = parse_input(input); /* Parse the input into arguments */

if (argv[0] == NULL) /* Handle empty input */
{
free(argv); /* Free allocated memory */
return; /* Do nothing */
}

command_path = find_command(argv[0]); /* Find command path */
if (command_path == NULL) /* Command not found */
{
fprintf(stderr, "./shell: %s: No such file or directory\n", argv[0]);
free(argv);
return; /* Exit without executing */
}

pid = fork(); /* Fork process */
if (pid < 0) /* Fork failed */
{
perror("Fork failed");
}
else if (pid == 0) /* Child process */
{
execve(command_path, argv, NULL); /* Execute command */
perror(command_path); /* Print error if command fails */
exit(EXIT_FAILURE); /* Exit on failure */
}
else /* Parent process */
{
waitpid(pid, &status, 0); /* Wait for child process to complete */
}
free(argv); /* Free allocated memory for arguments */
free(command_path);
}



/**
 * parse_input - Parses the input string into command and arguments
 * @input: The command line input to parse
 * Return: Array of command and arguments
 */
char **parse_input(char *input)
{
char **argv;
char *token;
int position = 0;
int bufsize = 64; /* Initial size for argument buffer */
argv = malloc(bufsize * sizeof(char *)); /* Allocate memory for arguments */
if (!argv) /* Check for allocation failure */
{
perror("Allocation error");
exit(EXIT_FAILURE);
}
token = strtok(input, " "); /* Split input into tokens */
while (token != NULL)
{
argv[position] = token; /* Add token to argument array */
position++;
if (position >= bufsize) /* Expand buffer if needed */
{
bufsize += 64; /* Increase buffer size */
argv = realloc(argv, bufsize *sizeof(char *)); /* Reallocate memory */
if (!argv) /* Check for allocation failure */
{
perror("Reallocation error");
exit(EXIT_FAILURE);
}
}
token = strtok(NULL, " "); /* Get the next token */
}
argv[position] = NULL; /* Null terminate the arguments */
return (argv); /* Return the array of arguments */
}

/**
 * find_command - Searches for a command in the PATH
 * @command: The command to search for
 * Return: Full path of the command if found, NULL otherwise
 */
char *find_command(char *command)
{
char *path = getenv("PATH"); /* Get PATH environment variable */
char *path_copy = strdup(path); /* Duplicate PATH string */
char *dir = strtok(path_copy, ":"); /* Split PATH into directories */
struct stat buffer; /* For checking if command exists */


if (stat(command, &buffer) == 0) /* Check if command exists */
{
free(path_copy); /* Free allocated memory */
return (strdup(command)); /* Return the command itself if executable */
}
while (dir != NULL) /* Iterate through directories in PATH */
{
char full_path[1024]; /* Buffer for full command path */
snprintf(full_path, sizeof(full_path), "%s/%s", dir, command); /* full path */
if (stat(full_path, &buffer) == 0) /* Check if command exists */
{
free(path_copy); /* Free allocated memory */
return (strdup(full_path)); /* Return the full command path */
}
dir = strtok(NULL, ":"); /* Get next directory */
}
free(path_copy); /* Free allocated memory */
return (NULL); /* Command not found */
}


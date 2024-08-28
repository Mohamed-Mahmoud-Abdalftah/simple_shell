#include "header.h"

/**
 * create_envi - Creates an array of Enviroment Variables
 * @envi: Array to store Env Variables
 */

void create_envi(char **envi)
{
	int i;

	for (i = 0; environ[i]; i++)
		envi[i] = _strdup(environ[i]);
	envi[i] = NULL;
}

/**
 * free_env - Frees the memory of the created Env Variables array
 * @env:  the created array of Env variables
 */
void free_env(char **env)
{
	int i;

	for (i = 0; env[i]; i++)
	{
		free(env[i]);
	}
}

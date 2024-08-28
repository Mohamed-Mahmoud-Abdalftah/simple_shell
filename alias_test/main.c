#include "main.h"

int main(int argc, char *argv[])
{
	// Example of using alias function
	char *args1[] = {"alias"};
	char *args2[] = {"alias", "list='ls -l'", "show='cat'"};
	char *args3[] = {"alias", "list"};

	// Adding and updating aliases
	alias(3, args2);

	// Printing all aliases
	alias(1, args1);

	// Printing specific alias
	alias(2, args3);

	// Cleanup
	free_aliases();

	return (0);
}


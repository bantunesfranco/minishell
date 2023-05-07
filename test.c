#include "minishell.h"
#include "parsing.h"

int	main(int argc, char *argv[], char **env)
{
	// printf("%s\n", *env);
	// print_array(env);
	// printf("hi\n");
	// chdir("/Users/jmolenaa/Codam/Codam_unfinished/minihell/minishell/incs");
	chdir("../../../..");
	char * str = getcwd(NULL, 0);
	printf("%s\n", str);
}
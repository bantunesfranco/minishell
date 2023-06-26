#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void	handle_sig(int signum)
{
	printf("lolno\n");
}

void	handle_sig2(int signum)
{
	exit(0);
}

int	main()
{
	int	id;

	signal(SIGINT, handle_sig);
	for (int i = 0; i < 10; i++)
	{
		id = fork();
		if (id == 0)
		{
			signal(SIGINT, handle_sig2);
			while (1)
			{
				printf("%d\n", i);
			}
		}
	}
	sleep(5);
		printf("parent\n");
	kill(0, SIGINT);
		printf("all dead\n");
	sleep(2);
}
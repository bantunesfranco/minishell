#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int	main()
{
	int	id;
	int	p[2];

	pipe(p);
	id = fork();
	if (id == 0)
	{
		close(p[0]);
		sleep(5);
		printf("%zd\n", write (p[1], "hello", 5));
		sleep(5);
		printf("%zd\n", write (p[1], "hi", 5));
		close(p[1]);
		while (1)
		{}
		exit(0);
	}
	close(p[1]);
	printf("parent\n");
	char	buffer[6];

	int	read_by;
	while (1)
	{
		read_by = read(p[0], buffer, 10);
		printf("%d\n", read_by);
		buffer[read_by] = '\0';
		printf("%s\n", buffer);
	}
	sleep(2);
}
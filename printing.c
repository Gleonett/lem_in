
#include "lem_in.h"

void	print_bigraph(t_tbhash ***bigr, int num_a_r[2])
{
	int i;
	int j;

	i = -1;
	printf("\n");
	while (++i < num_a_r[1])
	{
		j = -1;
		printf("%2d ", i);
		while (++j < num_a_r[1] && bigr[i] != NULL && bigr[i][j] != NULL)
		{
			if (bigr[i][j] != NULL)
				printf("["YELLOW"%s"REBOOT"]", bigr[i][j][0].room);
		}
		printf("\n");
	}
	printf("\n\n");
}
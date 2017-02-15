#include <stdlib.h>
#include <stdio.h>

int puzzle_parts[20][3];
int free_edges[40][2];

int main(int argc, char const *argv[])
{
	int num_parts = 0;

	while(scanf("%d %d %d",&puzzle_parts[num_parts][0],&puzzle_parts[num_parts][1],&puzzle_parts[num_parts][2]) != EOF)
	{
		num_parts++;
	}

	
	return 0;
}
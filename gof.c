#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void
prgrid(char **grid, int w, int h)
{
	int x, y;

	/* foreach row */
	for (y = 0; y < h; y++) {
		/* foreach cell */
		for (x = 0; x < w; x++) {
			if (grid[x][y])
				printf("█");
			else
				putchar(' ');
		}
		putchar('\n');
	}
}

void
randgrid(char **grid, int w, int h)
{
	int x, y;

	/* foreach row */
	for(y = 0; y < h; y++) {
		/* foreach cell */
		for(x = 0; x < w; x++) {
			grid[x][y] = rand() % 2 == 1;
		}
	}
}

char **
allocf(int width, int height)
{
	char **f;
	int i;

	f = calloc(sizeof(char *), width);
	for (i = 0; i < width; i++)
		f[i] = calloc(sizeof(char), height);

	return f;
}

void
freef(char **field, int width) {
	int i;
	for (i = 0; i < width; i++)
		free(field[i]);
	free(field);
}


int
calc_neighbour(char **cells, int x, int y, int width, int height) {
	int n = 0;
	int nx, ny;

	fflush(stdout);

	for (nx = x - 1; (nx <= x + 1); nx++) {
		if (nx < 0 || nx >= width)
			continue;

		for (ny = y - 1; (ny <= y + 1); ny++) {
			if (ny < 0 || ny >= height || (ny == y && nx == x))
				continue;
			if (cells[nx][ny])
				n++;
		}
	}

	return n;
}

void
calc_neighbours(char **neighbours, char **cells, int width, int height) {
	int x, y;

	/* foreach row */
	for (y = 0; y < height; y++) {
		/* foreach cell */
		for (x = 0; x < width; x++) {
			neighbours[x][y] = 
				calc_neighbour(cells, x, y, width, height);
		}
	}
}


int
gof(int alive, int nbours) {
	if(alive) {
		if(nbours < 2) {
			/* dead because under population */
			return 0;
		} else if(nbours == 2 || nbours == 3) {
			/* lives on */
			return 1;
		} else if(nbours > 3) {
			/* dead because over population */
			return 0;
		}
	} else {
		if(nbours == 3) {
			/* birth */
			return 1;
		}
	}
	return alive;
}

int
progress(char **cells, char **neighbours, int width, int height) {
	int x, y;
	int alive, nbours;
	int changes = 0;
	char *cell;

	calc_neighbours(neighbours, cells, width, height);

	for (x = 0; x < width; x++) {
		for (y = 0; y < height; y++) {
			cell = &cells[x][y];

			alive = *cell;
			nbours = neighbours[x][y];

			*cell = gof(*cell, nbours);
			if (*cell != alive)
				changes++;
		}
	}
	return changes;
}

int
main(void) {
	char **cells;
	char **neighbours;
	int width = 140;
	int height = 55;
	int gen;
	int max_gens = 1000;
	int changes;
	struct timespec slptime = { 0, 300000000 };


	cells = allocf(width, height);
	neighbours = allocf(width, height);

	srand(time(NULL));

	randgrid(cells, width, height);
	prgrid(cells, width, height);

	printf("\e[1;1H\e[2J");

	/* main loop */
	for(gen = 0; gen <= max_gens; gen++) {
		printf("Generation:\t%2d\n", gen);
		changes = progress(cells, neighbours, width, height);
		printf("Changes:\t%2d\n", changes);
		puts("-------------------------");
		prgrid(cells, width, height);
		puts("-------------------------");
		nanosleep(&slptime, NULL);
		printf("\e[1;1H\e[2J");
	}

	/* clean up */
	freef(cells, width);
	freef(neighbours, width);

	return 0;
}

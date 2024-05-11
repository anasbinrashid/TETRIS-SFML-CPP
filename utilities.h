
// Title for the game

const char gametitle[] = "PF-Project, Fall-2022";

// Defining the height and width of the grid of game

const int M = 20;
const int N = 10;

// Creating the grid of game

int gameGrid[M][N] = {0};

// Defining the positions and shadows for display and manipulating the movement of blocks

int point_1[4][2], point_2[4][2];
int dow1[4][2], dow2[4][2];

// Creating the check for boundaries

bool anamoly()
{
	for (int abr=0;abr<4;abr++)
		if (point_1[abr][0]<0 || point_1[abr][0]>=N || point_1[abr][1]>=M)	// Checking if the blocks exceed the boundaries of grid of game
 			return 0;
		else if (gameGrid[point_1[abr][1]][point_1[abr][0]])				// Checking for the rest of the blocks
			return 0;

	return 1;
};

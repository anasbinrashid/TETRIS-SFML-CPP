/* Anas Bin Rashid
22I-0907
CS-A
Final Project */

// Function that causes the Blocks to Drop 

void Block_Drop(long double& timer, long double& retard, long int& blockcolour)
{
	if (timer>retard)														// Condition for falling of blocks after every time the timer is less than retard which is 0.3 at default
 	{
		for (long int abr=0;abr<4;abr++) 
		{
			point_2[abr][0]=point_1[abr][0];
			point_2[abr][1]=point_1[abr][1]; 
			point_1[abr][1]+=1;												// Dropping the blocks
		}

		if (!anamoly())														// Checking the conditions from utilities.h
		{
			for (long int abr=0;abr<4;abr++)
			{
				gameGrid[point_2[abr][1]][point_2[abr][0]]=blockcolour;		// Giving colors to generated Tetraminos
			}

			blockcolour=1+rand()%7;											// Random color assigned to Tetraminos
			long int n=rand()%7;					
		     
			for (long int abr=0;abr<4;abr++)
			{	
				point_1[abr][0] = TetrisBlocks[n][abr] % 2;
				point_1[abr][1] = TetrisBlocks[n][abr] / 2;
			}
		}

	timer=0;																// Resetting timer value
	}
}

// Function for Dropping the Blocks at the exact instant

void Dead_fall()
{
	while(anamoly())														// Loop works till utilities.h conditions are correct
	{
		for(long int abr=0; abr<4; abr++)
		{
			point_2[abr][0]=point_1[abr][0];
			point_2[abr][1]=point_1[abr][1];
			point_1[abr][1]+=1;
		}
	}
	for(long int abr=0; abr<4; abr++)
	{
		point_1[abr][1]-=1;													// To keep the blocks one above the last row as they overlap
	}	
}

// Function for Left and Right Movement of Blocks 

void L_Movement(long int& lrc)
{
	for(long int abr=0; abr<4; abr++)
	{
 		point_2[abr][0]=point_1[abr][0];
 		point_2[abr][1]=point_1[abr][1];
  		point_1[abr][0] += lrc;												// Moving the blocks left
  	}
  	if (!anamoly())															// Checking for conditions from utilities.h
  	{
  		for (long int abr=0;abr<4;abr++)
  		{
  			point_1[abr][0]=point_2[abr][0];
  			point_1[abr][1]=point_2[abr][1];
  		}
	}
	lrc=0;																	// Resetting the variable
}

void R_Movement(long int& lrc)
{
	for(long int abr=0; abr<4; abr++)
	{
 		point_2[abr][0]=point_1[abr][0];
 		point_2[abr][1]=point_1[abr][1];
  		point_1[abr][0] += lrc;												// Moving the blocks right
  	}
  	if (!anamoly())															// Checking for conditions from utilities.h
  	{
  		for (long int abr=0;abr<4;abr++)
  		{
  			point_1[abr][0]=point_2[abr][0];
  			point_1[abr][1]=point_2[abr][1];								// Condition so blocks move only when they can
  		}
	}
	lrc=0;																	// Resetting the variable
}

// Function for Rotation of the Blocks 

void CA_Rotation(bool& twist)
{
	
	if (twist)																// Checking if rotation is true
	{        
		for (long int abr=0;abr<4;abr++)
		{
			long int rotor1, rotor2;
			rotor1 = point_1[abr][1]- point_1[1][1];
  			rotor2 = point_2[abr][0]- point_1[1][0];
			point_1[abr][0]=point_1[1][0] - rotor1;
            point_1[abr][1]=point_1[1][1] + rotor2;
		}
		
		if (!anamoly())														// Checking the conditions of utilities.h
		{
			for (long int abr=0;abr<4;abr++)
			{
				point_1[abr][0]=point_2[abr][0];
				point_1[abr][1]=point_2[abr][1];							// Condition so blocks move only when they can
			}
		}
	}
	twist= false;

}

// Function for Checking lines so filled lines can be removed

long int Cut_lines(long int& game_sc, long int& level_ofgame)
{
	long int P=M-1;															// Initialising the variable for 1 less than rows 
	
    for (long int abr=M-1;abr>0;abr--)
    {
        long int count=0, c=0;												// Counter and checker for removing lines and scoring respectively
        for (long int j=0;j<N;j++)
        {
            if (gameGrid[abr][j]) 											// Grid checker to remove lines
            	count++;
            gameGrid[P][j]=gameGrid[abr][j];								// Grid updater 
           
		}		
        
        if (count<N) 														// Counter condition
        {
        	P--;
        }
        else																// Score counter condition
        {
        	c++;
        }
        
        // Conditions for score addition
       
        if(c==1)
		{
			game_sc+= (10*level_ofgame);
		}
		else if(c==2)
		{
			game_sc+= (30*level_ofgame);
		}
		else if(c==3)
		{
			game_sc+= (60*level_ofgame);
		}
		else if(c==4)
		{
			game_sc+= (100*level_ofgame);
		}
    }
    
    return game_sc;
}

// Function for ending the game if grid is full

bool End_ofGame()
{
	for(long int abr=0; abr<N; abr++)
	{
		if(gameGrid[1][abr])												// Checking the grid
		{
			return true;													// Return true if first row is full
		}
	}
	return false;
}

// Shadow Check for boundaries and other blocks

bool shadow_anamoly()
{

	for(long int abr=0;abr<4;abr++)
		if(dow1[abr][0]<0||dow1[abr][0]>=N||dow1[abr][1]>=M)
			return 0;
		
		else if(gameGrid[dow1[abr][1]][dow1[abr][0]])
			return 0;
		
  return 1;	
}

// Shadow Movement Left and Right

void lrc_shadow(long int& lrc)
{
	for(long int abr=0;abr<4;abr++)
	{
		dow1[abr][0]=dow2[abr][0];
		dow1[abr][0]+=lrc;													// Moving the shadows left or right
	}
	if(shadow_anamoly()==0)													// Function for condition checking of shadows
	{
		for(long int abr=0; abr<4; abr++)
		{
			dow1[abr][0]=dow2[abr][0];										// Condition so shadows move only when they can
		}
	}
}

// Function for create shadows

void Shades(long int& lrc, long int& blockcolour)
{
	for(long int abr=0; abr<4; abr++)
	{
		for(long int j=0; j<2; j++)
		{
			dow1[abr][j]=point_1[abr][j];									// Setting the position of shadows the same as blocks
			dow2[abr][j]=point_1[abr][j];
		}
	}
	
	while(shadow_anamoly())													// Shadow dropping
	{
		for(long int abr=0;abr<4;abr++)
		{
			dow2[abr][0]=dow1[abr][0];
			dow2[abr][1]=dow1[abr][1];
			dow1[abr][1]+=1;
		}
	}
	
	if(lrc)
	{
		lrc_shadow(lrc);													// Function for movement of shadows
	}
}

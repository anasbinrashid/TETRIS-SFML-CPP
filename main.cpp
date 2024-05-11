/* Anas Bin Rashid
22I-0907
CS-A
Final Project */

// Including all the libraries necessary 
// SFML for graphics
// sstream for strings
// time.h for random number generator

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <sstream>
#include "pieces.h"
#include "utilities.h"
#include "functions.h"

using namespace sf;

int main()
{

	srand(time(0));
    RenderWindow window(VideoMode(500, 480), gametitle);

    // Including Background, Frame, and Tiles provided to us
    
    Texture objectnumber1, objectnumber2, objectnumber3, objectnumber4, objectnumber5;
    objectnumber1.loadFromFile("img/tiles.png");
    objectnumber2.loadFromFile("img/background.png");
    objectnumber3.loadFromFile("img/shadows.png");
    objectnumber4.loadFromFile("img/frame.png");
    objectnumber5.loadFromFile("img/bg.png");
    
    Sprite sprite(objectnumber1), background(objectnumber2), shades(objectnumber3), frame(objectnumber4), bg(objectnumber5);
    
    // Declaration and Initialization of all the variables
    
    long int lrc=0, blockcolour=1, game_sc=0, level_ofgame=1;
    long double timer=0, retard=0.3;
    bool twist=0;
    
    Clock clock;
    
    // Loading the downloaded font
    
    Font font;
    font.loadFromFile("font/Calibri Regular.ttf");
     
    // Declaring the text
     
    Text calculatedpoints, Nameof_Gamer, totscor_disp;
    
    // Setting the font for text, the size of text, and color of text
   
  	calculatedpoints.setFont(font);
  	calculatedpoints.setCharacterSize(20);
  	calculatedpoints.setFillColor(Color::White);
    Nameof_Gamer.setFont(font);
    Nameof_Gamer.setCharacterSize(12);
    Nameof_Gamer.setString("Player Name:  Anas Bin Rashid");
    Nameof_Gamer.setFillColor(Color::White);
    totscor_disp.setFont(font);
    totscor_disp.setCharacterSize(20);
    totscor_disp.setString("Score:  ");
    totscor_disp.setFillColor(Color::White);
  	
    /*	// Including Music

    Music music;
    if (!music.openFromFile("sound/music.ogg"));
   		 return -1;
   		 
    music.setPosition(0, 1, 10); 
	music.setPitch(2);           
	music.setVolume(50);         
	music.setLoop(true); 
    music.play();	*/
   
    // Loop continues till rendered window is open
   
    while (window.isOpen())
    {
        long double time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
            {
                window.close();
            }
			if (e.type == Event::KeyPressed)
            {
              if (e.key.code==Keyboard::Up) 					// Blocks rotation is true when up key is pressed
              		twist=true;
              else if (e.key.code==Keyboard::Left) 				// Blocks left movement when left key is pressed
              		lrc=-1;
              else if (e.key.code==Keyboard::Right) 			// Blocks right movement when right key is pressed
              		lrc=1;
            }
        }
		if (Keyboard::isKeyPressed(Keyboard::Space)) 
		{
			Dead_fall();										// Function for Dropping the blocks at the exact instant
 		}
		
		if (Keyboard::isKeyPressed(Keyboard::Down))				// Delay is reduced when down key is pressed
			retard=0.05;

		// Functions for Left and Right Movement of Blocks 
		
		if(lrc==1)
		{
			R_Movement(lrc);
		}
		else
		{
			L_Movement(lrc);
		}
		
		// Function for Rotation of the Blocks 
		
		CA_Rotation(twist);
		
		// Function to create shadows
		
		Shades(lrc, blockcolour);
		
		// Function that causes the Blocks to Drop 
		
		Block_Drop(timer, retard, blockcolour);
		
		// Function for Checking lines so filled lines can be removed
		
		Cut_lines(game_sc, level_ofgame);

		// Function for ending the game if grid is full

		bool check_EOG= End_ofGame();
		
		if(check_EOG==true)										// If true is returned, the window closes
		{
			window.close();
		}

		// Resetting the variables

		lrc=0; twist=0; retard=0.3;

		// Displaying the screen and backgrounds
		
		window.clear(Color::Black);    
		window.draw(background);
		bg.setPosition(310, -40);
		window.draw(bg);
		      
		// Displaying the tetraminos along with their shadows
		      
		for (long int abr=0;abr<M;abr++)
		{
			for (long int j=0;j<N;j++)
			{
				if (gameGrid[abr][j]==0)
					continue;
				sprite.setTextureRect(IntRect(gameGrid[abr][j]*18,0,18,18));
				sprite.setPosition(j*18,abr*18);
				sprite.move(28,31); 
				window.draw(sprite);
			}
		}

		for (long int abr=0; abr<4; abr++)
		{
            shades.setTextureRect(IntRect(blockcolour*18,0,18,18));
            shades.setPosition(dow2[abr][0]*18,dow2[abr][1]*18);
            shades.move(28,31);
            window.draw(shades);
        }

		for (long int abr=0;abr<4;abr++)
		{
			sprite.setTextureRect(IntRect(blockcolour*18,0,18,18));
		    sprite.setPosition(point_1[abr][0]*18,point_1[abr][1]*18);
		    sprite.move(28,31); 
		    window.draw(sprite);
		}

		// Displaying text by setting their positions

 		std::stringstream ss;										 // Using the sstream library for score calculation
 		ss<<game_sc;
 		calculatedpoints.setString(ss.str());
 		calculatedpoints.setPosition(415, 220);
 		window.draw(calculatedpoints);
  	    Nameof_Gamer.setPosition(325, 180);
   	    window.draw(Nameof_Gamer);
   	    totscor_disp.setPosition(325, 220);
 		window.draw(totscor_disp);

		window.draw(frame);
		window.display();
	}

    return 0;
}

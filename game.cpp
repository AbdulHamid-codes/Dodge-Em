//============================================================================
// Name        : game.cpp
// Author      : Hassan Mustafa
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Dodge 'Em...
//============================================================================

#ifndef DODGE_CPP_
#define DODGE_CPP_
#include "util.h"
#include <iostream>
#include<string>
#include<cmath> // for basic math functions such as cos, sin, sqrt
#include<curses.h> // Alternative of conio.h for get character
using namespace std;

// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}

/*
 * Main Canvas drawing function.
 * */
//Board *b;
int ar[8][9]{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
float xp = 405; 
float yp = 720;
float x = 485; 
float y = 415;
int In_xp, In_yp;
int score=0;
string Score;
int level=1;
string Level;
int lives=3;
string Lives;
int screen=0;

 void GameDisplay()/**/
{
	if(screen==0)   // Starting menu
	{
		glClear (GL_COLOR_BUFFER_BIT); //Update the colors
		DrawString( 400, 650, "Welcome", colors[MISTY_ROSE]);
		DrawString( 350, 600, "1. Srart New Game", colors[MISTY_ROSE]);
		DrawString( 350, 560, "2.See High Score", colors[MISTY_ROSE]);
		DrawString( 350, 520, "3.Help", colors[MISTY_ROSE]);
		DrawString( 350, 480, "4.Exit", colors[MISTY_ROSE]);
		glutSwapBuffers();
	}
	if(screen==2)    // Durring gaem pause
	{
		glClear (GL_COLOR_BUFFER_BIT); //Update the colors
		DrawString( 400, 650, "Welcome", colors[MISTY_ROSE]);
		DrawString( 350, 600, "1.Srart New Game", colors[MISTY_ROSE]);
		DrawString( 350, 560, "2.See Hight Score", colors[MISTY_ROSE]);
		DrawString( 350, 520, "3.Help", colors[MISTY_ROSE]);
		DrawString( 350, 480, "4.Exit", colors[MISTY_ROSE]);
		DrawString( 350, 440, "5.Continue", colors[MISTY_ROSE]);
	    glutSwapBuffers();
	}
	if(screen==3)  // Help
	{
		glClear (GL_COLOR_BUFFER_BIT); //Update the colors
		DrawString(180, 600,  "Collect the reward boxes avoiding collision with the blue car", colors[MISTY_ROSE]);
        DrawString(180, 570, "You are given three lives, each collision with blue car losse one life" , colors[MISTY_ROSE]);
		DrawString(180, 540, "Use arrow keys to jump between the roadways at the openings ", colors[MISTY_ROSE]);
		DrawString(180, 510,  "You can only jump in or out at one central point of the opening  ", colors[MISTY_ROSE]);
		DrawString(180, 480,  "So press and hold the desired key a moment before to avoid inconvenience ", colors[MISTY_ROSE]);
		DrawString(180, 450,  "When all the rewards are collected you will proceed to next level where  ", colors[MISTY_ROSE]);
		DrawString(180, 420,  "blue car will get smarter to hit you ", colors[MISTY_ROSE]);
		DrawString(180, 370,  "Press [P] go to main menu ", colors[MISTY_ROSE]);
		glutSwapBuffers();
	}
	if(screen==4)   // Won on completion
	{
		glClear (GL_COLOR_BUFFER_BIT); //Update the colors
		DrawString(400, 400,  "You Won!!! ", colors[MISTY_ROSE]);
		glutSwapBuffers();
	}
	if(screen==5)     // Game over
	{
		glClear (GL_COLOR_BUFFER_BIT); //Update the colors
		DrawString(400, 400, "Game over", colors[MISTY_ROSE]);
		glutSwapBuffers();
	}
	if(screen==1)
	{

	    glutPostRedisplay();
	    // set the background color using function glClearColor.
	    // to change the background play with the red, green and blue values below.
	    // Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.
    	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
		0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	    glClear (GL_COLOR_BUFFER_BIT); //Update the colors
	    // calling some functions from util.cpp file to help students
	    //Square at 400,20 position
	    //DrawSquare( 400 , 20 ,40,colors[RED]); 
	    //Square at 250,250 position
	    //DrawSquare( 250 , 250 ,20,colors[GREEN]); 
	    //Display Score
	    Score=to_string(score);
	    Level=to_string(level);
	    Lives=to_string(lives);

     	DrawString( 60, 840, "score "+Score, colors[MISTY_ROSE]);
	    DrawString( 260, 840, "level "+Level, colors[MISTY_ROSE]);
	    DrawString( 460, 840, "lives "+Lives, colors[MISTY_ROSE]);
	    DrawString( 660, 840, "p(menu)", colors[GREEN]);

	    //Triangle at 300, 450 position
	    //DrawTriangle( 300, 450 , 340, 450 , 320 , 490, colors[MISTY_ROSE] ); 
	    // Trianlge Vertices v1(300,50) , v2(500,50) , v3(400,250)
	    //Circle at 50, 670 position
	    //DrawCircle(50,670,10,colors[RED]);
	    //Line from 550,50 to 550,480 with width 10
	    //DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
	    //DrawLine( 550 , 50 ,  550 , 480 , 10 , colors[MISTY_ROSE] );	
	
	    // Drawing opponent car
	    float width = 15; 
	    float height = 12;
	    float* color = colors[BLUE_VIOLET]; 
	    float radius = 4.0;
	    DrawRoundRect(x,y,width,height,color,radius); // bottom left tyre
	    DrawRoundRect(x+width*3,y,width,height,color,radius); // bottom right tyre
	    DrawRoundRect(x+width*3,y+height*4,width,height,color,radius); // top right tyre
	    DrawRoundRect(x,y+height*4,width,height,color,radius); // top left tyre
	    DrawRoundRect(x, y+height*2, width, height, color, radius/2); // body left rect
	    DrawRoundRect(x+width, y+height, width*2, height*3, color, radius/2); // body center rect
	    DrawRoundRect(x+width*3, y+height*2, width, height, color, radius/2); // body right rect

    	// Drawing players car
	  
	    width = 15; 
	    height = 12;
	    color = colors[BROWN]; 
	    radius = 4.0;
	    DrawRoundRect(xp,yp,width,height,color,radius); // bottom left tyre
	    DrawRoundRect(xp+width*3,yp,width,height,color,radius); // bottom right tyre
	    DrawRoundRect(xp+width*3,yp+height*4,width,height,color,radius); // top right tyre
	    DrawRoundRect(xp,yp+height*4,width,height,color,radius); // top left tyre
	    DrawRoundRect(xp, yp+height*2, width, height, color, radius/2); // body left rect
	    DrawRoundRect(xp+width, yp+height, width*2, height*3, color, radius/2); // body center rect
	    DrawRoundRect(xp+width*3, yp+height*2, width, height, color, radius/2); // body right rect

	    // Drawing Arena
	    int gap_turn = 60;
	    int sx = 80;
	    int sy = 80;
	    int swidth = 710/2 - gap_turn/2; // half width
	    int sheight = 10;
	    float *scolor = colors[BROWN];
	    DrawRectangle(sx, sy, swidth, sheight, scolor); // bottom left
	    DrawRectangle(sx + swidth + gap_turn, sy, swidth, sheight, scolor); // bottom right
	    DrawRectangle(sx+swidth*2+gap_turn, sy+sheight, 2*sheight, swidth, scolor); // right down
	    DrawRectangle(sx+swidth*2+gap_turn, sy+sheight+swidth+gap_turn, sheight*2, swidth, scolor); // right up
	    DrawRectangle(sx + swidth + gap_turn, sy+710, swidth, sheight, scolor); // top left
	    DrawRectangle(sx, sy+710, swidth, sheight, scolor); // top right
	    DrawRectangle(sx-sheight*2, sy+sheight+swidth+gap_turn, sheight*2, swidth, scolor); // left up
	    DrawRectangle(sx-sheight*2, sy+sheight, sheight*2, swidth, scolor); // left down

	    // Drawing Arena
	    gap_turn = 60;
	    sx = 160;
	    sy = 160;
	    swidth = 550/2 - gap_turn/2; // half width
	    sheight = 10;
	    scolor = colors[BROWN];
	    DrawRectangle(sx, sy, swidth, sheight, scolor); // bottom left
	    DrawRectangle(sx + swidth + gap_turn, sy, swidth, sheight, scolor); // bottom right
	    DrawRectangle(sx+swidth*2+gap_turn, sy+sheight, 2*sheight, swidth, scolor); // right down
	    DrawRectangle(sx+swidth*2+gap_turn, sy+sheight+swidth+gap_turn, sheight*2, swidth, scolor); // right up
	    DrawRectangle(sx + swidth + gap_turn, sy+550, swidth, sheight, scolor); // top left
	    DrawRectangle(sx, sy+550, swidth, sheight, scolor); // top right
	    DrawRectangle(sx-sheight*2, sy+sheight+swidth+gap_turn, sheight*2, swidth, scolor); // left up
	    DrawRectangle(sx-sheight*2, sy+sheight, sheight*2, swidth, scolor); // left down

        // Drawing Arena
	    gap_turn = 60;
	    sx = 240;
	    sy = 240;
	    swidth = 390/2 - gap_turn/2; // half width
	    sheight = 10;
	    scolor = colors[BROWN];
	    DrawRectangle(sx, sy, swidth, sheight, scolor); // bottom left
	    DrawRectangle(sx + swidth + gap_turn, sy, swidth, sheight, scolor); // bottom right
	    DrawRectangle(sx+swidth*2+gap_turn, sy+sheight, 2*sheight, swidth, scolor); // right down
	    DrawRectangle(sx+swidth*2+gap_turn, sy+sheight+swidth+gap_turn, sheight*2, swidth, scolor); // right up
	    DrawRectangle(sx + swidth + gap_turn, sy+390, swidth, sheight, scolor); // top left
	    DrawRectangle(sx, sy+390, swidth, sheight, scolor); // top right
	    DrawRectangle(sx-sheight*2, sy+sheight+swidth+gap_turn, sheight*2, swidth, scolor); // left up
	    DrawRectangle(sx-sheight*2, sy+sheight, sheight*2, swidth, scolor); // left down

        // Drawing Arena
	    gap_turn = 60;
	    sx = 320;
	    sy = 320;
	    swidth = 230/2 - gap_turn/2; // half width
	    sheight = 10;
	    scolor = colors[BROWN];
	    DrawRectangle(sx, sy, swidth, sheight, scolor); // bottom left
	    DrawRectangle(sx + swidth + gap_turn, sy, swidth, sheight, scolor); // bottom right
	    DrawRectangle(sx+swidth*2+gap_turn, sy+sheight, 2*sheight, swidth, scolor); // right down
	    DrawRectangle(sx+swidth*2+gap_turn, sy+sheight+swidth+gap_turn, sheight*2, swidth, scolor); // right up
	    DrawRectangle(sx + swidth + gap_turn, sy+230, swidth, sheight, scolor); // top left
	    DrawRectangle(sx, sy+230, swidth, sheight, scolor); // top right
	    DrawRectangle(sx-sheight*2, sy+sheight+swidth+gap_turn, sheight*2, swidth, scolor); // left up
	    DrawRectangle(sx-sheight*2, sy+sheight, sheight*2, swidth, scolor); // left down

	    DrawLine( 395 , 405 ,  475 , 405 , 10 , colors[RED] );	   // Bottom of the centre most rectangle
	    DrawLine( 395 , 475 ,  475 , 475 , 10 , colors[RED] );     // Top of centre most rectangle
	    DrawLine( 395 , 405 ,  395 , 475 , 10 , colors[RED] );    // Left of the centre most rectangle
	    DrawLine( 475 , 405 ,  475 , 475 , 10 , colors[RED] );    // Right

	    // Movement of Player's car
        // Left
	    if((yp == 335 && xp <= 485 && xp > 325) || (yp == 260 && xp <= 565 && xp > 245) || (yp == 185 && xp <= 645 && xp > 165 ) || (yp == 110 && xp <= 725 && xp > 85 ) && (yp <= 405))
	    xp-=1;
     	// Right
	    if((yp == 495 && xp >= 325 && xp < 485) || (yp == 570 && xp >= 245 && xp < 565) || (yp == 645 && xp >= 165 && xp < 645) || (yp == 720 && xp >= 85 && xp < 725) && (yp >= 415))
	    xp+=1;
	    // Up
	    if((xp == 325 && yp >= 335 && yp < 495) || (xp == 245 && yp >= 260 && yp < 570) || (xp == 165 && yp >= 185 && yp < 645) || (xp == 85 && yp >= 110 && yp < 720 ) && ( xp <= 325))
	    yp+=1;
	    // Down
     	if((xp == 485 && yp <= 495 && yp > 335 ) || (xp == 565 && yp <= 570 && yp > 260) || (xp == 645 && yp <= 645 && yp > 185) || (xp == 725 && yp <= 720 && yp > 110) && ( xp >= 485))
        yp-=1;
	
    	// Turning decision of opponent car on the base of its distancd from players car
  
    	// Jump up
    	if(x == 405 && (y == 645 || y == 570 || y == 495 || y == 260 || y == 185 || y == 110))
    	{
    		if(abs(yp-y-75) < abs(yp-y)) 
    		y+=75;
    	}
    	// Jump down
    	if(x==405 && (y==720 || y==645 || y==570 || y == 335 || y ==260 || y == 185))
    	{
    	 	if(abs(yp-y+75) < abs(yp-y))
     		y-=75;
    	}
		// For levels greater than one opponents car can take left and right turn as well
		if(level>1)
		{
			// Right jump
  	        if(y== 415 && (x == 85 || x == 165 || x == 245 || x == 485 || x == 565 || x == 645))
	        {
	    	  if(abs(xp-x-80)< abs(xp-x))
	    	  x+=80;
			}
			// Left jump
	        if(y == 415 && (x == 725 || x == 645 || x == 565 || x == 325 || x == 245 || x == 165))
	        {
	    	  if(abs(xp-x+80) < abs(xp-x))
	    	  x-=80;
	        }
		}

		// To remove reward box when car hit that
        In_yp=110;
	  	for(int i=0;i<8;i++)
        {
		    In_xp=85;
			for(int j=0;j<9;j++)
			{
				if(((xp==In_xp)&&(yp==In_yp)) || ((xp-1==In_xp || xp+1==In_xp)&&(yp==In_yp))  || ((xp==In_xp)&&(yp-1==In_yp || yp+1==In_yp)))
				{ar[i][j]=0;
				score++;}
				In_xp+=80;
			}
			if(In_yp==335)
			{In_yp+=160;}
			else
			In_yp+=75;

		}	
	    // To draw the reward boxes
		In_yp=110;               
		for(int i=0;i<8;i++)
		{
			In_xp=85;
			for(int j=0;j<9;j++)
			{
				if(ar[i][j]==1)
				DrawSquare( In_xp+30 , In_yp+30 ,10,colors[GREEN]);
				In_xp+=80;
			}
			if(In_yp==335)
			{In_yp+=160;}
			else
			In_yp+=75;
		}
		// To check if all the reward boxes are collecte
		int sum=0;
		for(int i=0;i<8;i++)
		{
			for(int j=0;j<9;j++)
			{
				if(ar[i][j]==0)
				sum++;
			}
		}
		// If all the reward boxes are collected
		if(sum==72)  
		{
			if(level==4)
			{
				screen=4;
			}
			xp=405;       // To bring the cars to the starting position
			yp=720;
			x=485;
			y=415;
			score+=100;   // To give bonus of 100 
			level+=1;    // Continue to next level
			for(int i=0;i<8;i++)   // To refil the reward boxes
			{
				for(int j=0;j<9;j++)
				ar[i][j]=1;
			}
		}
		if(lives==0)    // To display game over
		{
			screen=5;
		}

		// When the cars collide
		if((xp==x && yp==y) || ((xp-1==xp || xp+1==x)&&(yp==y)) || ((xp==x)&&(yp-1==y || yp+1==y)))
		{
			xp=405;       // To bring the cars to the starting position
			yp=720;
			x=485;
			y=415;
			lives-=1;           // One life is lost
			score=0;              // Score becomes zero 
			for(int i=0;i<8;i++)   // To refil the reward boxes
			{
				for(int j=0;j<9;j++)
				ar[i][j]=1;
			}
	        
		}
	
        // Movement of opponent car
    	// Right movement
        if((y == 335 && x < 485 && x >= 325) || (y == 260 && x < 565 && x >= 245) || (y == 185 && x < 645 && x >= 165 ) || (y == 110 && x < 725 && x >= 85 ) && (y <= 405))
    	{x+=1;}
    	// Up movement
    	if((x == 485 && y < 495 && y >= 335 ) || (x == 565 && y < 570 && y >= 260) || (x == 645 && y < 645 && y >= 185) || (x == 725 && y < 720 && y >= 110) && ( x >= 485))
    	{y+=1;}
    	// Left movement
    	if((y == 495 && x > 325 && x <= 485) || (y == 570 && x > 245 && x <= 565) || (y == 645 && x >= 165 && x <= 645) || (y == 720 && x > 85 && x <= 725) && (y >= 415))
    	{x-=1;}
    	// Down movement
        if((x == 325 && y > 335 && y <= 495) || (x == 245 && y > 260 && y <= 570) || (x == 165 && y > 185 && y <= 645) || (x == 85 && y > 110 && y <= 720 ) && ( x <= 325))
    	{y-=1;}

    	// For level three when opponents car's speed has to be doubled so do the same thing again
    	if(level>2)
       	{
      	// Right movement
        if((y == 335 && x < 485 && x >= 325) || (y == 260 && x < 565 && x >= 245) || (y == 185 && x < 645 && x >= 165 ) || (y == 110 && x < 110 && x >= 85 ) && (y <= 405))
    	{x+=1;}
    	// Up movement
    	if((x == 485 && y < 495 && y >= 335 ) || (x == 565 && y < 570 && y >= 260) || (x == 645 && y < 645 && y >= 185) || (x == 725 && y < 720 && y >= 110) && ( x >= 485))
    	{y+=1;}
    	// Left movement
    	if((y == 495 && x > 325 && x <= 485) || (y == 570 && x > 245 && x <= 565) || (y == 645 && x >= 165 && x <= 645) || (y == 720 && x > 85 && x <= 725) && (y >= 415))
    	{x-=1;}
    	// Down movement
        if((x == 325 && y > 335 && y <= 495) || (x == 245 && y > 260 && y <= 570) || (x == 165 && y > 185 && y <= 645) || (x == 85 && y > 110 && y <= 720 ) && ( x <= 325))
    	{y-=1;}
    	}

    	glutSwapBuffers(); // do not modify this line.. or draw anything below this line
    } 
}
/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y)
 {
	if (key == GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/)
	{
        if(yp == 415 && (xp == 725 || xp == 645 || xp == 565 || xp == 325 || xp == 245 || xp == 165))
		xp-=80;
	} 
	else if (key == GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/)
    {
        if(yp== 415 && (xp == 85 || xp == 165 || xp == 245 || xp == 485 || xp == 565 || xp == 645))
		xp+=80;
	} 
	else if (key == GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) 
	{
		if(xp == 405 && (yp == 645 || yp == 570 || yp == 495 || yp == 355 || yp == 260 || yp == 185 || yp == 110))
		yp+=75;
	}
	else if (key == GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/)
	{
		if(xp==405 && (yp==720 || yp==645 || yp==570 || yp == 335 || yp ==260 || yp == 185))
		yp-=75;
	}
	

	glutPostRedisplay();

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) 
{
	if (key == 27/* Escape key ASCII*/)
	{
		exit(1); // exit the program when escape key is pressed.
    }
	if (key == 'p' ||  key == 'P')
	{
		screen=2;   // To display the menu durring game which has five options
	}
	if (key == '1' )   
	{
		screen=1; // To display the game screen when 1 is pressed
	}
	if (key == '3' )  
	{
		screen=3; // To display the help menu when 3 is pressed
	}
	if (key == '4' )   
	{
		exit(1); // To exit when 4 is pressed
	}
	if(key=='5')
	{
		screen=1;
	}
	if(key == 32)   // To double the speed
	{
	// Down
	if((xp == 485 && yp <= 495 && yp > 335 ) || (xp == 565 && yp <= 570 && yp > 260) || (xp == 645 && yp <= 645 && yp > 185) || (xp == 725 && yp <= 720 && yp > 110) && ( xp >= 485))
    yp-=1;
	// Up
	if((xp == 325 && yp >= 335 && yp < 495) || (xp == 245 && yp >= 260 && yp < 570) || (xp == 165 && yp >= 185 && yp < 645) || (xp == 85 && yp >= 110 && yp < 720 ) && ( xp <= 325))
	yp+=1;
	// Right
	if((yp == 495 && xp >= 325 && xp < 485) || (yp == 570 && xp >= 245 && xp < 565) || (yp == 645 && xp >= 165 && xp < 645) || (yp == 720 && xp >= 85 && xp < 725) && (yp >= 415))
	xp+=1;
	 // Left
	if((yp == 335 && xp <= 485 && xp > 325) || (yp == 260 && xp <= 565 && xp > 245) || (yp == 185 && xp <= 645 && xp > 165 ) || (yp == 110 && xp <= 725 && xp > 85 ) && (yp <= 405))
	xp-=1;
	}
	glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) {

	// implement your functionality here
  
	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(50.0, Timer, 0);
	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y) {
	cout << x << " " << y << endl;
	glutPostRedisplay();
}
void MouseMoved(int x, int y) {

	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
			{
		cout << GLUT_DOWN << " " << GLUT_UP << endl;

	} else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
			{

	}
	glutPostRedisplay();
}
/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {

	//b = new Board(60, 60); // create a new board object to use in the Display Function ...

	int width = 900, height = 900; // i have set my window size to be 800 x 600
	//b->InitalizeBoard(width, height);
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("/* i19-0565 */"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.
	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(50.0, Timer, 0);

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* AsteroidS_CPP_ */

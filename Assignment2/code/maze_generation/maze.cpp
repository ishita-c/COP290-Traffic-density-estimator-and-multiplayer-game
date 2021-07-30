//Purpy Pupple's amazing maze generator. 
//Released under the CC-BY-SA 3.0 License and the GFDL
#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <time.h>
#include "maze.h"
#include "output.h"
using namespace std;

#define UP 0     //-y
#define DOWN 1   //+y
#define LEFT 2   //-x
#define RIGHT 3  //+x

#define backtrack//enable this to generate mazes using depth-first search. Don't enable both.


long numin=1;     //Number of cells in the maze.
const int xsize=20;
const int ysize=20;

cell MAZE[xsize][ysize];

void initialize(){
	//Initialize the maze!
	for(int x=0;x<xsize;x++){
		for(int y=0;y<ysize;y++){
			//The maze cells on the edges of the maze are "in" to provide padding. Otherwise, all maze cells are not in.
			MAZE[x][y].in   = (x==0||x==xsize-1||y==0||y==ysize-1)?1:0;
			//All maze cells have all walls existing by default, except the perimeter cells.
			MAZE[x][y].up   = (x==0||x==xsize-1||y==0)?0:1;
			MAZE[x][y].left = (x==0||y==0||y==ysize-1)?0:1;
		}
	}
	return;
}
void generate(){
	int xcur=1, ycur=1;//start growing from the corner. It could theoretically start growing from anywhere, doesn't matter.
	MAZE[xcur][ycur].in = 1;
	int whichway;
	bool success;
	do{
		while( MAZE[xcur][ycur-1].in&&MAZE[xcur][ycur+1].in&&
			   MAZE[xcur-1][ycur].in&&MAZE[xcur+1][ycur].in ){
				   //If all the neighbourhood cells are in, backtrack.
				int xcur2=MAZE[xcur][ycur].prevx;
				ycur=MAZE[xcur][ycur].prevy;
				xcur=xcur2;
		}
		do{
			//Randomly grow the maze if possible.
			success=0;
			whichway=rand()%4;
			switch(whichway){
			case UP:
				if(!MAZE[xcur][ycur-1].in){
					success=1;
					MAZE[xcur][ycur].up=0;
					MAZE[xcur][ycur-1].prevx=xcur;
					MAZE[xcur][ycur-1].prevy=ycur;
					ycur--;
				}
				break;
			case DOWN:
				if(!MAZE[xcur][ycur+1].in){
					success=1;
					MAZE[xcur][ycur+1].up=0;
					MAZE[xcur][ycur+1].prevx=xcur;
					MAZE[xcur][ycur+1].prevy=ycur;
					ycur++;
				}
				break;
			case LEFT:
				if(!MAZE[xcur-1][ycur].in){
					success=1;
					MAZE[xcur][ycur].left=0;
					MAZE[xcur-1][ycur].prevx=xcur;
					MAZE[xcur-1][ycur].prevy=ycur;
					xcur--;
				}
				break;
			case RIGHT:
				if(!MAZE[xcur+1][ycur].in){
					success=1;
					MAZE[xcur+1][ycur].left=0;
					MAZE[xcur+1][ycur].prevx=xcur;
					MAZE[xcur+1][ycur].prevy=ycur;
					xcur++;
				}
				break;
			}
		}while(!success);
		MAZE[xcur][ycur].in=1;
		numin++; //Every iteration of this loop, one maze cell is added to the maze.
	}while(numin<(xsize-2)*(ysize-2));
	return;
}

bool** create2DArray(unsigned height, unsigned width)
    {
      bool** array2D = 0;
      array2D = new bool*[height];
    
      for (int h = 0; h < height; h++)
      {
            array2D[h] = new bool[width];
    
            for (int w = 0; w < width; w++)
            {
                  // fill in some initial values
                  // (filling in zeros would be more logic, but this is just for the example)
                  array2D[h][w] = false;
            }
      }
    
      return array2D;
    }

bool ** savebmp(int xspecial, int yspecial){
	//save a bitmap file! the xspecial, yspecial pixel is coloured red.
	FILE * outfile;
	int extrabytes, paddedsize;
	int x, y, n;
	int h=20;
	int w=20;
	int width=(xsize-1)*2-1;
	int height=(ysize-1)*2-1;

	extrabytes = (4 - ((width * w * 3) % 4))%4; 

	char filename[200];
	
	sprintf(filename, "%s_%dx%d_n%d.bmp", OUTFILE, xsize, ysize, numin);
	paddedsize = ((width * w * 3) + extrabytes) * height * 2;

	unsigned int headers[13] = {paddedsize + 54, 0, 54, 40, width * w, height * h, 0, 0, paddedsize, 0, 0, 0, 0};

	outfile = fopen(filename, "wb");
	fprintf(outfile, "BM");

	for (n = 0; n <= 5; n++){
	   fprintf(outfile, "%c", headers[n] & 0x000000FF);
	   fprintf(outfile, "%c", (headers[n] & 0x0000FF00) >> 8);
	   fprintf(outfile, "%c", (headers[n] & 0x00FF0000) >> 16);
	   fprintf(outfile, "%c", (headers[n] & (unsigned int) 0xFF000000) >> 24);
	}

	fprintf(outfile, "%c", 1);fprintf(outfile, "%c", 0);
	fprintf(outfile, "%c", 24);fprintf(outfile, "%c", 0);

	for (n = 7; n <= 12; n++){
	   fprintf(outfile, "%c", headers[n] & 0x000000FF);
	   fprintf(outfile, "%c", (headers[n] & 0x0000FF00) >> 8);
	   fprintf(outfile, "%c", (headers[n] & 0x00FF0000) >> 16);
	   fprintf(outfile, "%c", (headers[n] & (unsigned int) 0xFF000000) >> 24);
	}

	bool ** Map= create2DArray(width *w + extrabytes,height * h);
	//Actual writing of data begins here:
	for(y = height-1; y >=0; y--){
		for (int h1=0;h1<h;h1++){
		for(x = 0; x <= width - 1; x++){
			if(x%2 == 1 && y%2 == 1){
				if(x/2+1 == xspecial && y/2+1 == yspecial) {for(int i=0;i<w;i++){RED;Map[x * w+i][y*h+h1]=true;}}
				else{
					if(MAZE[x/2+1][y/2+1].in) {for(int i=0;i<w;i++){WHITE;Map[x * w+i][y*h+h1]=true;}} else {for(int i=0;i<w;i++){BLACK;Map[x * w+i][y*h+h1]=false;}}
				}
			}else if(x%2 == 0 && y%2 == 0){
				{for(int i=0;i<w;i++){BLACK;Map[x * w+i][y*h+h1]=false;}}
			}else if(x%2 == 0 && y%2 == 1){
				if(MAZE[x/2+1][y/2+1].left) {for(int i=0;i<w;i++){BLACK;Map[x * w+i][y*h+h1]=false;}} else {for(int i=0;i<w;i++){WHITE;Map[x * w+i][y*h+h1]=true;}}
			}else if(x%2 == 1 && y%2 == 0){
				if(MAZE[x/2+1][y/2+1].up) {for(int i=0;i<w;i++){BLACK;Map[x * w+i][y*h+h1]=false;}} else {for(int i=0;i<w;i++){WHITE;Map[x * w+i][y*h+h1]=true;}}
			}
		}
		if (extrabytes){     // See above - BMP lines must be of lengths divisible by 4.
			for (n = 1; n <= extrabytes; n++){
				fprintf(outfile, "%c", 0);
				Map[width * w + n][y*h+h1]= false;
			}
		}
		}
	}
	printf("file printed: %s\n", filename); 
	fclose(outfile);
	string s=filename;
	return Map;
}


bool ** maze(int x,int y){
	srand((unsigned int)time(NULL)); //seed random number generator with system time
	initialize();      //initialize the maze
	generate();
	return savebmp(x,y);
}






//Purpy Pupple's amazing maze generator. 
//Released under the CC-BY-SA 3.0 License and the GFDL
#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <time.h>
#include "maze.h"
#include "output.h"
using namespace std;

long numin=1;     //Number of cells in the maze.
const int xsize=22;
const int ysize=22;

    
bool MAZE[22][22]={
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,1,0,1,0,1,1,1,1,0,1,1,1,1,0,1,0,1,1,1,0,1},
{1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,0,1},
{1,1,0,1,0,1,1,1,1,0,1,1,1,1,0,1,0,1,1,0,0,1},
{1,0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0,0,1,1},
{1,0,1,1,1,1,1,0,1,0,1,0,1,1,1,1,1,0,1,0,1,1},
{1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
{1,0,1,0,0,0,1,0,1,0,1,0,1,0,0,0,1,0,1,1,0,1},
{1,0,1,1,1,0,1,0,1,0,1,0,1,0,1,1,1,0,0,0,0,1},
{1,0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,1,1,0,1},
{1,1,0,1,1,1,1,0,0,0,0,0,1,1,1,1,0,1,1,0,0,1},
{1,1,0,0,0,1,1,0,1,0,1,0,1,1,0,0,0,1,1,0,1,1},
{1,0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1,1},
{1,0,1,1,1,1,1,0,1,0,1,0,1,1,1,1,1,0,0,0,0,1},
{1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,0,0,0,1,1,0,1},
{1,1,0,1,0,0,0,1,1,0,1,1,0,0,0,1,0,1,1,1,0,1},
{1,1,0,1,1,1,0,1,1,0,1,1,0,1,1,1,0,1,1,1,0,1},
{1,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
{1,1,0,1,0,1,0,1,1,0,1,1,0,1,0,1,0,1,1,1,0,1},
{0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};

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


bool** savebmp(int xspecial, int yspecial){
	//save a bitmap file! the xspecial, yspecial pixel is coloured red.
	FILE * outfile;
	int extrabytes, paddedsize;
	int x, y, n;
	int h=20;
	int w=20;
	int width=xsize;
	int height=ysize;

	extrabytes = (width*w)%4; 

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

	bool ** Map= create2DArray(height * h,width *w + extrabytes);
	//Actual writing of data begins here:
	for(y = height-1; y >=0; y--){
		for (int h1=0;h1<h;h1++){
		for(x = 0; x <= width - 1; x++){
				if(x== xspecial && y == yspecial) {for(int i=0;i<w;i++){RED;Map[x * w+i][y*h+h1]=true;}}
				else{
					if(MAZE[y][x]) {for(int i=0;i<w;i++){BLACK;Map[x * w+i][y*h+h1]=false;}} else {for(int i=0;i<w;i++){WHITE;Map[x * w+i][y*h+h1]=true;}}
				}
			}
			
		if (extrabytes){     // See above - BMP lines must be of lengths divisible by 4.
			for (n = 0; n < extrabytes; n++){
				fprintf(outfile, "%c", 0);
				Map[width * w + n][y*h+h1]= false;
			}
			
		}
		}
	}
	printf("Done");
	for (int i=0;i<height *h;i++){
		for (int j=0;j<width *w + extrabytes;j++){
			if (Map[i][j])printf("T");
			else printf("F");
		}
		printf("\n");
	}
	printf("file printed: %s\n", filename); 
	fclose(outfile);
	string s=filename;
	return Map;
}


bool ** maze(int x,int y){
	return savebmp(x,y);
}






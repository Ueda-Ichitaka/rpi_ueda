#include "led-matrix.h"
#include "threaded-canvas-manipulator.h"

#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#include <assert.h>
#include <getopt.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
#include <algorithm>

using rgb_matrix::GPIO;
using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

static void DrawOnCanvas(Canvas *canvas) {
  /*
   * Let's create a simple animation. We use the canvas to draw
   * pixels. We wait between each step to have a slower animation.
   */
   
   
  int height = canvas->height();
  int width = canvas->width();
  
  while(true)
  {
	  canvas->SetPixel(std::rand()%32, std::rand()%16, std::rand()%255, std::rand()%255, std::rand()%255);
	  usleep(50 * 1000);
  }
  
  /*
  for(int j = 0; j < 32; j++)
  {
	  int g = 0;
	  for(int i = 0 +g; i < 32+g; i++)
	  {
		  canvas->SetPixel(i+g, 8*sin(1*i+g+0)+8, 0, 0, 255);
		  //usleep(200 * 1000);
	  }
	  ++g;
	  usleep(200 * 1000);
  }
  */
  /*
  canvas->Fill(255, 0, 0);	//red
  usleep(2000 * 1000);
  
  canvas->Fill(0, 255, 0);	//green
  usleep(2000 * 1000);
  
  canvas->Fill(0, 0, 255);	//blue
  usleep(2000 * 1000);
  
  canvas->Fill(255, 255, 0);	//yellow 1
  usleep(2000 * 1000);
  
  canvas->Fill(0, 255, 255);	// green türkis
  usleep(2000 * 1000);
  
  canvas->Fill(255, 0, 255);	//rose
  usleep(2000 * 1000);
  
  canvas->Fill(255, 255, 255);	//wyellow 2
  usleep(2000 * 1000);
  
  canvas->Fill(0, 0, 0);
  canvas->SetPixel(0, 0, 100, 100, 100);
  usleep(2000 * 1000);
  
  int dir = 1;
  
  if(dir == 1)
  {
	  for(int i = 0; i< 256; i++)
	  {
		  canvas->Fill(i, 0, 0);
		  std::cout << i << ":0:0"<< std::endl;
		  usleep(100 * 1000);
	  }
	  for(int i = 0; i< 256; i++)
	  {
		  canvas->Fill(255, i, 0);
		  std::cout << "255:" << i << ":0"<< std::endl;
		  usleep(100 * 1000);
	  }
	  for(int i = 0; i< 256; i++)
	  {
		  canvas->Fill(255, 255, i);
		  std::cout << "255:255:" << i << std::endl;
		  usleep(100 * 1000);
	  }
	  dir = 0;
  }
  if(dir == 0)
  {
	  for(int i = 255; i>= 0; i--)
	  {
		  canvas->Fill(i, 255, 255);
		  std::cout << i << std::endl;
		  usleep(100 * 1000);
	  }
	  for(int i = 255; i>= 0; i--)
	  {
		  canvas->Fill(0, i, 255);
		  usleep(100 * 1000);
	  }
	  for(int i = 255; i>= 0; i--)
	  {
		  canvas->Fill(0, 0, i);
		  usleep(100 * 1000);
	  }
	  dir = 1;
  }
  
  usleep(2000 * 1000);
  
  int c = 0;
  while (c<256) {
	// Calculate the next frame.
	c++;
	for (int x = 0; x < canvas->width(); ++x) {
	  for (int y = 0; y < canvas->height(); ++y) {
		canvas->SetPixel(x, y, c, c, c);
	  }
	}
	usleep(15 * 1000);
  }
  * */
  
}

int main(int argc, char *argv[]) {
  /*
   * Set up GPIO pins. This fails when not running as root.
   */
  GPIO io;
  if (!io.Init())
    return 1;
    
  /*
   * Set up the RGBMatrix. It implements a 'Canvas' interface.
   */
  int rows = 16;    // A 32x32 display. Use 16 when this is a 16x32 display.
  int chain = 1;    // Number of boards chained together.
  int parallel = 1; // Number of chains in parallel (1..3). > 1 for plus or Pi2
  Canvas *canvas = new RGBMatrix(&io, rows, chain, parallel);

  DrawOnCanvas(canvas);    // Using the canvas.
  
  usleep(2000 * 1000);
  
  // Animation finished. Shut down the RGB matrix.
  canvas->Clear();
  delete canvas;

  return 0;
}

#include "led-matrix.h"
#include "threaded-canvas-manipulator.h"

#include <assert.h>
#include <getopt.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <algorithm>

using std::min;
using std::max;

using namespace rgb_matrix;

/*
 * new model: volumebars: update gpio
 *			  fft: grap audio input && calc values
 *			  main: control
 *			  		int main()
 *			  		{
 *			  			bars = new volumebars();
 *			  			fft = new fft();
 *			  		}
 *
 *			  		void loop()
 *			  		{
 *			  			int[] freq = fft.analyze();
 *			  			bars.update(freq);
 *			  		}
 *
 *
 */

class VolumeBars : public ThreadedCanvasManipulator
{
	int m_values[];	
public:
  VolumeBars(Canvas *m) : ThreadedCanvasManipulator(m)
  {
  
  }

  ~VolumeBars() 
  {
	  
  }

  void Run() 
  {
    //const int width = canvas()->width();
    //height_ = canvas()->height();
	int values[] = {2, 2, 4, 5, 3, 6, 5, 7, 12, 12, 16, 16, 15, 10, 12, 5, 3, 3, 4, 9, 7, 13, 10, 8, 6, 3, 0, 2, 5, 1, 8, 10};	
	
	while(running())
	{		
		updateBars(values);
		// Random Values
		for(int i = 0; i < 32; ++i)
		{
			values[i] = rand() % 17;			
		}
		
		usleep(500 * 1000);
		//updateValues(/*get from fft */);
		//do fft
		//update values from fft
		//update bars
		//sleep
	}
	
 
  }
  
public:
  void updateValues(int values[])
  {
	  for(int i = 0; i < 32; ++i)
	  {
		  m_values[i] = values[i];
	  }
  }  
  
  void updateBars(int values[])
  {
	  for(int i = 0; i < 32; ++i)
	  {
		  drawBar(i, values[i]);
	  }
  }

private:
  void drawBar(int rownum, int amplitude) 
  {
	clearBar(rownum);  
    if(amplitude>14)
    {
		for(int y = 16; y >= 16-amplitude; --y)
		{
			canvas()->SetPixel(rownum, y, 255, 0, 0);
			//usleep(5 * 1000);
		}
	}
	else if(amplitude>12)
	{
		for(int y = 16; y >= 16-amplitude; --y)
		{
			canvas()->SetPixel(rownum, y, 255, 255, 0);
			//usleep(5 * 1000);
		}
	}
	else if(amplitude>8)
	{
		for(int y = 16; y >= 16-amplitude; --y)
		{	
			canvas()->SetPixel(rownum, y, 0, 255, 0);
			//usleep(5 * 1000);
		}
	}
	else
	{
		for(int y = 16; y >= 16-amplitude; --y)
		{
			canvas()->SetPixel(rownum, y, 0, 0, 255);
			//usleep(5 * 1000);
		}		
	}
  }
  
private:
  void clearBar(int rownum)
  {
	  for(int y = 0; y <= 16; ++y)
	  {
		canvas()->SetPixel(rownum, y, 0, 0, 0);
		//usleep(5 * 1000);
	  }
  }  

  int height_;
};


int main(int argc, char *argv[]) {
  bool as_daemon = false;
  int runtime_seconds = -1;
  int demo = -1;
  int rows = 16;
  int chain = 1;
  int parallel = 1;
  int scroll_ms = 30;
  int pwm_bits = -1;
  bool large_display = false;
  bool do_luminance_correct = true;

  const char *demo_parameter = NULL;

  // Initialize GPIO pins. This might fail when we don't have permissions.
  GPIO io;
  if (!io.Init())
    return 1;

  // Start daemon before we start any threads.
  if (as_daemon) {
    if (fork() != 0)
      return 0;
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
  }

  // The matrix, our 'frame buffer' and display updater.
  RGBMatrix *matrix = new RGBMatrix(&io, rows, chain, parallel);
  matrix->set_luminance_correct(do_luminance_correct);
  if (pwm_bits >= 0 && !matrix->SetPWMBits(pwm_bits)) {
    fprintf(stderr, "Invalid range of pwm-bits\n");
    return 1;
  }

  Canvas *canvas = matrix;

  // The ThreadedCanvasManipulator objects are filling
  // the matrix continuously.
  ThreadedCanvasManipulator *image_gen = NULL;
  image_gen = new VolumeBars(canvas);

  // Image generating demo is crated. Now start the thread.
  image_gen->Start();
  //drawBar(5, 8);

  // Now, the image genreation runs in the background. We can do arbitrary
  // things here in parallel. In this demo, we're essentially just
  // waiting for one of the conditions to exit.
  if (as_daemon) {
    sleep(runtime_seconds > 0 ? runtime_seconds : INT_MAX);
  } else if (runtime_seconds > 0) {
    sleep(runtime_seconds);
  } else {
    // Things are set up. Just wait for <RETURN> to be pressed.
    printf("Press <RETURN> to exit and reset LEDs\n");
    getchar();
  }

  // Stop image generating thread.
  delete image_gen;
  delete canvas;

  return 0;
}

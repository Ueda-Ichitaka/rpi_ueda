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

#include <algorithm>

using std::min;
using std::max;
using rgb_matrix::GPIO;
using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

using namespace rgb_matrix;


class MyCrazyDemo : public ThreadedCanvasManipulator {
public:
MyCrazyDemo(Canvas *canvas) : ThreadedCanvasManipulator(canvas) {}
virtual void Run() {
  unsigned char c;
  while (running()) {
	// Calculate the next frame.
	c++;
	for (int x = 0; x < canvas()->width(); ++x) {
	  for (int y = 0; y < canvas()->height(); ++y) {
		canvas()->SetPixel(x, y, c, c, c);
	  }
	}
	usleep(15 * 1000);
  }
}
};

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
  RGBMatrix *matrix = new RGBMatrix(&io, rows, chain, parallel);

	// Later, in your main method.
	//RGBMatrix matrix(&gpio);
	MyCrazyDemo *demo = new MyCrazyDemo(&matrix);
	demo->Start();   // Start doing things.
	// This now runs in the background, you can do other things here,
	// e.g. aquiring new data or simply wait. But for waiting, you wouldn't
	// need a thread in the first place.
	demo->Stop();
	delete demo;
	
  return 0;	
	
}	
	

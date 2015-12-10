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

class GraphicEqualizer : public ThreadedCanvasManipulator
{
		/*
		 * main class
		 * init volumebars for gpio control
		 * init fft audio processing
		 * give values to volumebars
		 *
		 */

	public:
		GraphicEqualizer(Canvas *m) : ThreadedCanvasManipulator(m)
		{
			//init volumebars
			//init audio processing
		}

		~GraphicEqualizer()
		{

		}

		void Run()
		{
			//get values from audio processing
			//pipe into volumebars
			//volumebars.update
		}
};

int main(int argc, char *argv[])
{
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
	if (as_daemon)
	{
		if (fork() != 0)
			return 0;
		close (STDIN_FILENO);
		close (STDOUT_FILENO);
		close (STDERR_FILENO);
	}

	// The matrix, our 'frame buffer' and display updater.
	RGBMatrix *matrix = new RGBMatrix(&io, rows, chain, parallel);
	matrix->set_luminance_correct(do_luminance_correct);
	if (pwm_bits >= 0 && !matrix->SetPWMBits(pwm_bits))
	{
		fprintf(stderr, "Invalid range of pwm-bits\n");
		return 1;
	}

	Canvas *canvas = matrix;

	// The ThreadedCanvasManipulator objects are filling
	// the matrix continuously.
	ThreadedCanvasManipulator *image_gen = NULL;
	image_gen = new VolumeBars(canvas);  //TODO move to constructor  new GraphicEqualizer(canvas)

	// Image generating demo is crated. Now start the thread.
	image_gen->Start();
	//drawBar(5, 8);

	// Now, the image genreation runs in the background. We can do arbitrary
	// things here in parallel. In this demo, we're essentially just
	// waiting for one of the conditions to exit.
	if (as_daemon)
	{
		sleep(runtime_seconds > 0 ? runtime_seconds : INT_MAX);
	}
	else if (runtime_seconds > 0)
	{
		sleep(runtime_seconds);
	}
	else
	{
		// Things are set up. Just wait for <RETURN> to be pressed.
		printf("Press <RETURN> to exit and reset LEDs\n");
		getchar();
	}

	// Stop image generating thread.
	delete image_gen;
	delete canvas;

	return 0;
}

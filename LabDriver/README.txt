Overview:
This file contains an overview of all files that are apart of the LabDriver package

Author:
written by Michael Ausilio mausilio@umich.edu


Program Requirments:
1. Weiner NimBox drivers are installed 
2. Prologix GPIB drivers are installed
3. VXM drivers (not implemented in these programs yet)


Note: nimbox # is currently 0, Pologix port is com5, and Vxm port is com6
These may change in the future and will require recompilation

Programs:
NOTE: SOURCE RATE NEEDS TO BE CONTROLLED CAREFULLY HERE. MORE INFO WILL BE ADDED

After-pulse Scan
	description: A program that takes after pulse measurements through a range of voltage.
	instructions:
		1.Specify how you want to edit header information
			-if manual is selected user will be prompted for values
			-if file is selected header will be read from a template (in same directory as .exe) a template is included with the desired form
			NOTE: There are 3 modes for use here
				1.User: The user is required to position source in proper place. The max pixels that will be looked at at a time is 1.
				2.Dynamic: The VXM will automatically position source. NOTE: THIS HAS NOT BEEN IMPLEMENTED YET.
				3.Static: The source should be fixed. Multiple pixels may be looked at concurrently
		2. Enter Setup information (start voltage, end voltage, step size, number of pixels to be looked at, their coordinates). If Statuc mode is selected user will also be prompted for the number of concurrent pixels. NOTE: not all combinations have not been implemented yet. If they haven't been user will be alerted. NOTE: the number of pixels being measured at once has an effect on the sampling rate. These rates are detail below.
		3.Run will commence.
			-if User mode is selectd user will be prompted periodically to reposition source
		4.logs, graphs, and data output will be saved in the appropriate directory of Collected Data

AfterPulse Sampling Rate:
1 line: ~.4ms
2 line: ~.8ms
3 line: ~1.2ms
4 line: ~1.6ms
5 line: ~1.9 ms
6 line: splits to 3 and 3
7 line: splits to 4 and 3
8 line: splits to 4 and 4
9 line: splits to 5 and 4
10 line: ~3.6 ms


Voltage Scan
	desription: A program that runs through a voltage scan
	instructions:
	1.Specify how you want to edit header information
			-if manual is selected user will be prompted for values
			-if file is selected header will be read from a template (in same directory as .exe) a template is included with the desired form
			Note: Differences between source configs has not been implemented
	2. Enter Setup information (start voltage, end voltage, step size, number of pixels to be looked at, their coordinates).
	3.Run will commence.
	4.logs, graphs, and data output will be saved in the appropriate directory of Collected Data



---------------------------------------------------------------------------------------------------------------------------------------------------------
How to Use:










-----------------------------------------------------------------------------------------------------------------------------------------------------
Code Layout:
There are 4 base components to this code base:
1. Weiner Nim Box control
2. Bertan series 225 high voltage control (controlled with Prologix GPIB to Usb hub) (http://prologix.biz/gpib-usb-controller.html)
3. VXM Stepping Motor Controller
4. Header information (for out putting files)

These components are then built into functional routines that can be directly used by the end user. The end game is for these components to be combined to accomplish anything that the lab setup should require


External Library Requirements:
1. Boost http://www.boost.org/
2. Root (a version that is usable on windows with visual c++)
3. CImg http://cimg.eu/


C++ code files:
Each header file is implemented in a corresponding cpp file, these will not be mentioned for brevity

-LabUtilities.h
	This file contains all of the functional methods to perform various tests (e.g. after-pulse tests, voltage scans, etc.)

-headers.h
	This file contains the implementation of the headers used for i/o

-MotorController.h
	This file contains the methods to controler the VXM motor

-RootGraph.h
	This file contains methods to create graphs for the after-pulse data sets we produce as well as methods to create graphs used for displaying Counter progress

-stdafx.h
	This file contains all of the header files required for this project to ease compile time

-VoltageControl.h
	This file contains all of the user methods for controling the High Voltage

-WeinerCounter.h
	This file contains all of the user methods as well as more base methods for controlling the Nim Box

-ComPort.h
	This file contains basic functions for using  the Prologix gpib to usb hub.
	NOTE: This was not directly written by me. All functionality from this we need has already been included in wrapper functions

-HighResClock.h
	Contains an implementation for a high resolution clock that is used for timing.
	NOTE: This was not directly written by me
-VxmDriver.h	
	Contains the methods for using the VXM motor control.
	Note: This was not directly written by me. All functionality from this we need has already been included in wrapper functions
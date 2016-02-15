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
			-if file is selected header will be read from a template (headerTemplate.txt in same directory as .exe).
			    A template is included with the desired form
			NOTE: There are 3 modes for use here
				1.User: The user is required to position source in proper place. The max pixels that will be looked at at a time is 1.
				2.Dynamic: The VXM will automatically position source.
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
	3. Run will commence.
	4. logs, graphs, and data output will be saved in the appropriate directory of Collected Data

---------------------------------------------------------------------------------------------------------------------------------------------------------
config file formating : to be added

---------------------------------------------------------------------------------------------------------------------------------------------------------
How to Use:
Running:
eventually will be compiled to own executable. For now just run using the green local windows debugger button in visual studios



Startup:
When starting up program you will be prompted for a few options:
1.panel config file- (mc.pix is one set up for current microcavities, see this file for formatting)
2.Does panel need to be zeroed- y should only be answered if the panel was just put in.
  if the panel is already configured select n (it takes a lot of time).


From here you are able to select what mode to run in.
Running:
5 options:

  doing an apscan/combo scan is almost always preferable (even for straight voltage-scans)
  because it samples at a higher rate and produces similar data.
  
    quit   - quits the lab station software"
    free   - initiates free mode. In free mode, user has direct control of lab station equipment.
    vscan  - initiates a voltage scan. Parameters for this test are set before running.
    apscan - initiates an after-pulse scan. Parameters for this test are set before running.
    combo  - initiates a combination voltage and after-pulse scan. Parameters for this run are set before running.

Setting up scan:
  1.you will be asked if you want to setup the scan from a file or from command line
      -presetup file is in program directory and titled headerTemplate.txt
  2.you will then be asked for parameters such as :
    -voltage range
    -voltage step-size
    -how many pixels to measure
    -how many pixels to measure at once (Note: this option is only given in Static mode (i.e. source is fixed))
    -what their readout lines/ hv lines (again in pixel config file mc.pix, the y tag on a pixel line idicate which pixel is instrumented)
    -how many samples to take (for a single line 1 sample = ~4ms)
  3. then run will run
Free mode:
  NOTE: command handling is not robust yet so be careful
  1. type ? for option list


---------------------------------------------------------------------------------
Config Files:

1. Panel setup file - configures location of pixels for in terms of motor coordinates
   units are in steps 400 steps = 1 mm
   format
   <# RO lines>
   <# of HV lines>
   <x offset from alignment point to 1st pixel><y offset from alignment point to 1st pixel>
   //this is followed by many definition of pixel location that are of the form
   <#RO>-<#HV> <xcoord> <ycoord> <y/n corresponding to if instrumented or not>
2. Header template - sets up the static configuration header for a panel
   exampe of format:
    Panel Name   MC22
    Source   Sr 
    Source Config  Dynamic/Static/User
    Gas Mixture   79Ne20C2F61Ar
    Gas Pressure (Torr)   740
    R-quench (MOhm)   1000/500/200
    Trigger Setup   0
    Discriminator Thr (mV)   1000
    Number RO lines   10
    RO lines 1-10
    Trigger RO   0
    Attenuation RO (db)  0
    Number HV lines 10
    HV lines  1-10
    Trigger HV	 0
    Attenuation HV (db)   0
3. Voltage Scan Configuration - sets up run parameters for a voltage scan. This is an alternative to entering these values on the command line
    format:
    <start voltage (integer)>
    <stop voltage (integer)>
    <voltage step (inter)>
    <duration of each set of data collections>
    <sampling frequency>
    <# pixels>
    //followed by a list of coordinates of each pixels. The number of pixels needs to match the number of tuples given.
    <RO1> <HV1>
    <RO2> <HV2>
    ...
    <RO#> <HV#>
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
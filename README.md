# 421_Final_Project
## Presence Detection

### Brainstorming:
#####	Use Cases: 
		- sleep
		- (sitting)
#####	Inputs:
		- weight of head (on pillow)
		- weight of body (on mattress)
#####	Sensing:
		- pressure sensor
		- (sound)
		- (light) 
#####	Executions:
		- turn machines on and off using AC/DC relay
			* coffee machines
			* (speakers)
#####	Outputs: Information display
		- text notification to phone


### Abstract:
	If you are one of many who find mornings to be difficult, we aim to bring you a pleasant morning wake-up experience. 
	Imagine waking up to a cup of coffee, your favorite tunes, and pleasant soft lighting without having to lift a finger. 
	"How is this possible?" you ask. Using pressure sensing technology, our device will track your sleep, collecting information 
	on duration and quality of sleep. When it is time for you to get up, pleasant music will play to help you wake up.
	As you get up, soft lights will illuminate to brighten your day, and coffee will begin brewing for you. 
	Additionally, data collected can be accessed easily to help you observe your sleep trends.  

	The sensor will be placed under your head area (example: pillow), and the force detected by the sensors will be used to determine if you are still in bed or getting up.
	User input will determine when music will begin playing in the morning. String lights and coffee maker will activate based on the signal output by the pressure sensor.
	While our device is mainly focused on tracking presence during sleep, the technology can be generalized to many use cases such as sitting, vehicle parking, and others
	and execute a variety of tasks.  

### Plan of Approach: 
#### Detect Presence:
	- Set up pressure circuit
	- Look at data using serial monitor
		- Determine threshold using data
		- Learn how to save/export data
	- Make a decision based on data and threshold
		- 0 or 1 output to serial monitor
#### User input:
	- Speakers 	
		- Song control
		- Time control
	- Lights
		- Time control
		- Brightness control
	- Coffee
		- Time control
		- Potentially strength control 
#### Lights
	- Research
		- How to use relay switch
		- Existing related Arduino projects
		- Look at other light sources that have been used with Arduino
		- Look into IR technology 
			- Circuit playground IR function
			- Independent IR LED
		- Determine light's IR signal
		- Turn lights on or  off at decision signal 
#### Coffee: 
	- Look at existing Arduino projects 
#### Speakers: 
	- Look into Arduino and bluetooth use
		- Where is music coming from?
	- Potential features: 
		- Volume Control
		- Music control
			- Song choice
			- Changing song
		- On/Off or pause/play
 
		
### Revised Plan of Appraoch (11/14/17):
#### What We Have:
	- presence detection using one square FSR
	- arduino turns on string lights
	- arduino switches water kettle on using relay
#### Next Steps:
	- extend to additional use case (sitting)
		- by alerting user when seated for too long 
			- buzzer
	- add features to original use case
		- estimate duration of sleep
		- notification of sleep
			- self reminder on daily basis
			- email to professor when <3 hours of sleep

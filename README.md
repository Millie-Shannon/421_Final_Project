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
	Tracking presence can be useful for many use cases such as sleep, sitting, vehicle parking, etc. 
	We could execute various tasks such as making coffee in the morning, switching lights on, or even playing some light music.

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
 
		

# Coding_Two_Final_Project
## Creative motivations&Inspirations 
The project involves using an Arduino sensor to interact with openFrameworks, similar to what a VJ does. 

## Inspirations 
The inspiration comes from the basic interaction behaviors that can be achieved with a keyboard and mouse in visual and sound design. However, using buttons to create a piano is not feasible due to the amount of work involved. 

## Challenges
One of the challenges faced was the serial monitor, which posed difficulties in sending data from Arduino to Unity. After overcoming this challenge, another tough issue arose - how to differentiate the messages sent by different sensors to openFrameworks. To address this, if statements were used in Arduino to distinguish between different button situations and assign different values to each button and component to differentiate the commands executed by openFrameworks.
### Read the message from arduino
![pic](https://github.com/ZoeXiongyyy/Coding_Two_Final_Project/blob/main/Screenshot/coding_Screenshot5.png)

![pic](https://github.com/ZoeXiongyyy/Coding_Two_Final_Project/blob/main/Screenshot/coding_Screenshot4.png)

### Using if statement in arduino
![pic](https://github.com/ZoeXiongyyy/Coding_Two_Final_Project/blob/main/Screenshot/coding_Screenshot3.png)

### Distinguish the different value from Arduino in OpenFramework
![pic](https://github.com/ZoeXiongyyy/Coding_Two_Final_Project/blob/main/Screenshot/coding_Screenshot1.png)

![pic](https://github.com/ZoeXiongyyy/Coding_Two_Final_Project/blob/main/Screenshot/coding_Screenshot2.png)

##Implementation of your system
The system was implemented using Open GL mesh and Maxi library in C++, and two push buttons and a potentiometer as input signals in Arduino. When different buttons are pressed, they send different byte data to openFrameworks, which draws different waveforms based on the values received. Each button also corresponds to a different sound resource and changes the mood of the mesh. When the potentiometer is rotated, the value sent by Arduino is associated with the waveform and mesh color.
###Code in OpenFarmework
#### main.cpp
https://github.com/ZoeXiongyyy/Coding_Two_Final_Project/blob/main/Code/src/main.cpp
#### ofApp.cpp
https://github.com/ZoeXiongyyy/Coding_Two_Final_Project/blob/main/Code/src/ofApp.cpp
#### ofApp.h
https://github.com/ZoeXiongyyy/Coding_Two_Final_Project/blob/main/Code/src/ofApp.h

### Code in Arduino
https://github.com/ZoeXiongyyy/Coding_Two_Final_Project/blob/main/Code/sketch_feb7a/sketch_feb7a.ino

## Video link



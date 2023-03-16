#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    //=====================================OSC==========================
        float waveform[4096]; //make this bigger, just in case
        int waveIndex;
    
        ofSoundStream soundStream;
        ofSoundPlayer   mySound1;
        ofSoundPlayer   mySound2;
        ofSoundPlayer   mySound3;
        ofSoundPlayer   mySound4;
    
        /* ofxMaxi*/
        void audioIn(ofSoundBuffer& input) override; // not used in this example
        void audioOut(ofSoundBuffer& output) override;
        maxiOsc oscillator1;
        maxiOsc oscillator2;
    
        string sensorValue;
        int byteData;
        bool serialMessage;            // a flag for sending serial
        char receivedData[10];        // for storing incoming data
    
        char sendData = 0;
    
    //======================================SERIAL===========================
        ofSerial serial;
    
    //=========================MESH==========================================
        void addPoint(float x, float y) {
        points.push_back(glm::vec2(x, y));
        speeds.push_back(glm::vec2(ofRandom(-1, 1), ofRandom(-1, 1)));
    }
    
    // a simple vector of points
        vector <glm::vec2> points;
        vector <glm::vec2> speeds;
    
    // in super fast mode we use a vbo
        ofVbo vbo;
        
    // mode switcher
        int mode;
};

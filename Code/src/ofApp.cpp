#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //=================================OSC===================================
    mySound1.load("audio1.wav");
    mySound2.load("audio2.wav");
    mySound3.load("audio3.wav");
    mySound4.load("audio5.wav");
    mySound1.play();
    mySound2.play();
    mySound3.play();
    mySound4.play();
    
    ofBackground(0,0,0);
    //ofBackground(byteData, byteData, byteData);
    
    //Initialize the drawing variables
    for (int i = 0; i < ofGetWidth(); ++i) {
        waveform[i] = 0;
    }
    waveIndex = 0;
    
    // Maximilian audio stuff
    int sampleRate = 44100; /* Sampling Rate */
    int bufferSize= 512; /* Buffer Size. you have to fill this buffer with sound using the for loop in the audioOut method */
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    
    // Setup ofSound
    ofSoundStreamSettings settings;
    settings.setOutListener(this);
    settings.sampleRate = sampleRate;
    settings.numOutputChannels = 2;
    settings.numInputChannels = 0;
    settings.bufferSize = bufferSize;
    soundStream.setup(settings);
    //================================SERIAL===================================
    serialMessage = false;
    
    //ofBackground(255);
    
    // Display the list of available serial devices serial.listDevices();
    serial.listDevices();
    vector <ofSerialDeviceInfo> devicelist = serial.getDeviceList();

    // Set the serial communication baud rate
    int baud = 9600;
        
    // Connect to the serial device
    // Change this line depending on your platform and device
    serial.setup("/dev/cu.usbmodem101", baud);
    //serial.setup("COM10", baud); // windows example
    //serial.setup("/dev/ttyUSB0", baud); //linux example

    
    //===============================MESH============================================
    //ofBackgroundHex(0x57554c);
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    
    
    // slow       = 1
    // faster     = 2
    // super fast = 3
    mode = 1;}

//--------------------------------------------------------------
void ofApp::update(){
    //=======================================SERIAL===============================
    // Check if there is any serial data available
    //Simple if statement to inform user if Arduino is sending serial messages.
    if (serial.available() < 0) {
        sensorValue = "Arduino Error";
    }else{
        while (serial.available() > 0) {
            //byte data is being writen into byteData as int.
            byteData = serial.readByte();
            
            //byteData is converted into a string for drawing later.
            sensorValue = ofToString(byteData);
        }
        serial.writeByte(sendData); // sending the data to arduino
        
        
        printf("receivedData is %d \n", receivedData);
    }
    //=======================================MESH=================================
    // add points all the time
    if(points.size() < 500000)
    {
        for (int i=0; i<30; i++) {
            addPoint(ofGetWidth()/2, ofGetHeight()/2);
        }
    }
    
    // move all the points around
    for (unsigned int i=0; i<points.size(); i++)
    {
        
        speeds[i].y += 0.04; // some grav
        points[i]   += speeds[i];
        speeds[i]   *= 0.98;
        
        // move from the mouse
        glm::vec2 mouseVec = glm::vec2(byteData*5, byteData*5) - points[i];
        if(glm::length(mouseVec) < 100)
        {
            mouseVec = glm::normalize(mouseVec);
            speeds[i] -= mouseVec;
        }
        
        // wrap the screen
        if(points[i].x > ofGetWidth())    points[i].x = 1;
        if(points[i].x < 0)               points[i].x = ofGetWidth()-1;
        if(points[i].y > ofGetHeight())   points[i].y = 1;
        if(points[i].y < 0)               points[i].y = ofGetHeight()-1;
        
    }
    
    /*void testApp::secondBoidUpdate(){//update function definition outside the class testAPP
     
     ofVec3f min(0, 0); //define an object1 of class ofVec3f
     ofVec3f max(ofGetWidth(), ofGetHeight());//define an object2 of class ofVec3f
     
     
     for (int i = 0; i < secondBoids.size(); i++)
     {
     secondBoids[i]->update(boids, min, max);
     }
     
     
     }*/
}

//--------------------------------------------------------------
void ofApp::draw(){

    //==================================DRAW MESH===============================
      if(sensorValue == "1")
      {
          #ifdef TARGET_OPENGLES
         // ofSetColor(255);
          //ofDrawBitmapString("OpenGL immediate mode not available in OpenGL ES. Press 2 or 3.",ofGetWidth() / 2.0f - 300,ofGetHeight() / 2.0f);
          #else
          ofSetColor(255,255,byteData%255);
          glBegin(GL_POINTS);
          for (unsigned int i=0; i<points.size(); i++) {
              glVertex2f(points[i].x, points[i].y);
          }
          glEnd();
          #endif
      }
      
      // a bit faster
      else if(sensorValue == "2")
      {
          ofSetColor(byteData%255,255,byteData%255);
          ofMesh mesh;
          mesh.setMode(OF_PRIMITIVE_POINTS);
          for (unsigned int i=0; i<points.size(); i++) {
              mesh.addVertex(ofVec3f(points[i].x, points[i].y, 0));
          }
          mesh.draw();
      }
      
      // super fast (vbo)
      else
      {
          ofSetColor(byteData%255,byteData%255,255);
          vbo.setVertexData(&points[0], (int)points.size(), GL_DYNAMIC_DRAW);
          vbo.draw(GL_POINTS, 0, (int)points.size());
      }
      
      //ofSetColor(0);
     // ofDrawRectangle(0, 0, 250, 90);
      //ofSetColor(255);
      //ofDrawBitmapString("Mode "+ofToString(mode), 20, 20);
     // ofDrawBitmapString("FPS "+ofToString(ofGetFrameRate(), 0), 20, 40);
     // ofDrawBitmapString("Total Points "+ofToString((int)points.size()), 20, 60);
      
      //============================DRAW AUDIO WAVEFORM ==========================
      //---------------------------------------------------------------------------
      ofTranslate(0, ofGetHeight()/2);
      ofSetColor(ofRandom(255), ofRandom(255), byteData%150);
      ofFill();
      ofSetLineWidth(3);
      //void ofDrawLine(float x1,float y1,float x2,float y2);
      ofDrawLine(0, 0, 1, waveform[1] * ofGetHeight()/2.); //first line
      for(int i = 1; i < (ofGetWidth() - 1); ++i) {
          /*ofSetColor(255, ofRandom(200,255), ofRandom(200,255));
          ofSetLineWidth(20);
          ofDrawLine(i, waveform[i] * ofGetHeight()/2., i + 1, waveform[i+1] * ofGetHeight()/2.);
          ofSetColor(ofRandom(200), ofRandom(255), 100,205);
          ofSetLineWidth(10);
          ofDrawLine(i*2, waveform[i] * ofGetHeight()/2.+50,( i + 1)*2, waveform[i+1] * ofGetHeight()/2.+50);*/
         // ofBackground(byteData, byteData, byteData);
          
          if(byteData>2){
              //ofBackground(byteData, byteData, byteData)
              ofSetColor(byteData, 200, 200);
              ofSetLineWidth(byteData%100);
              ofDrawLine(i, waveform[i] * ofGetHeight()/2., i + 1, waveform[i+1] * ofGetHeight()/2.);
             // ofSetLineWidth(byteData);
              ofDrawLine(i*2, waveform[i] * ofGetHeight()/2.+50,( i + 1)*2, waveform[i+1] * ofGetHeight()/2.+50);
          }else{
              ofSetColor(byteData, 255, 255);
              //ofSetLineWidth(20);
              ofDrawLine(i, waveform[i] * ofGetHeight()/2., i + 1, waveform[i+1] * ofGetHeight()/2.);
              ofSetLineWidth(0.1);
              ofDrawLine(i*2, waveform[i] * ofGetHeight()/2.+50,( i + 1)*2, waveform[i+1] * ofGetHeight()/2.+50);
          }
      }
      std::cout << byteData << endl;

}
//====================================AUIDO PLAY=================================
void ofApp::audioIn(ofSoundBuffer &input){
    std::size_t nChannels = input.getNumChannels();
    for (size_t i = 0; i < input.getNumFrames(); i++)
    {
        // handle input here
    }
}

void ofApp::audioOut(ofSoundBuffer &output){
    std::size_t outChannels = output.getNumChannels();
    if(sensorValue == "1"){
        //if(ofGetKeyPressed()){
        mySound1.play();
        mySound2.play();
        for (int i = 0; i < output.getNumFrames(); ++i){
            
            // output[i * outChannels] = oscillator1.square(532) * 0.5;
            output[i * outChannels] = oscillator1.sinewave(532) * 0.5;
            // output[i * outChannels + 1] = output[i * outChannels];
            output[i * outChannels + 1] = oscillator1.coswave(50) * 0.025;
            
            //Hold the values so the draw method can draw them
            waveform[waveIndex] =  output[i * outChannels];
            if (waveIndex < (ofGetWidth() - 1)) {
                ++waveIndex;
            } else {
                waveIndex = 0;
            }
        }
    }
    
    if(sensorValue == "2"){
    //if(ofGetKeyPressed()){
        mySound3.play();
        mySound4.play();
        for (int i = 0; i < output.getNumFrames(); ++i){
            
            output[i * outChannels] = oscillator2.sinewave(182) * 0.1;
            output[i * outChannels + 1] =oscillator2.sinewave(44) * 0.1;
            
            //Hold the values so the draw method can draw them
            waveform[waveIndex] =  output[i * outChannels];
             if (waveIndex < (ofGetWidth() - 1)) {
             ++waveIndex;
             } else {
             waveIndex = 0;
             }
        }
        
    }
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

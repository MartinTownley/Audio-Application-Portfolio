 #pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "ofxOsc.h"
#include "ofxGui.h"

#define RPORT 8888 //osc receiver


class ofApp : public ofBaseApp{

	public:
    
    void setup() override;
    void update() override;
    void draw() override;
    
   
    
    void keyPressed(int key) override;
    void keyReleased(int key) override;
    void mouseMoved(int x, int y ) override;
    void mouseDragged(int x, int y, int button) override;
    void mousePressed(int x, int y, int button) override;
    void mouseReleased(int x, int y, int button) override;
    void mouseEntered(int x, int y) override;
    void mouseExited(int x, int y) override;
    void windowResized(int w, int h) override;
    void dragEvent(ofDragInfo dragInfo) override;
    void gotMessage(ofMessage msg) override;
    
    //font
    ofTrueTypeFont font1, font2, font3;
    
    
    
    
    
    //GUI
    void guiSetup();
    
    //OSC
    void oscSetup();
    ofxOscReceiver receiver;
    int velocity; //note on/off from max.
    
    //Filter stuff
    maxiFilter myFilter;
    double filterOut;
    
    int mouseX;
    int mouseY;
    
    maxiOsc myCutoff;
    
        void envelopeSetup();
        double randomNoise();
    double noise;
    double currentVolume();
    double vol;
        double noiseBurst();
    double burst;
        int currentCount();
    int count;
    void envTrigger();
    bool trig;
    
    //ofSOUND
    void ofSoundSetup();
    ofSoundStream soundStream;
    void audioIn(ofSoundBuffer& input) override;
    void audioOut (ofSoundBuffer& output) override;
    
    //boolean
    
    maxiSample noiseSample;
    double noiseOut;
    //counters and drivers
    maxiOsc counter, noiseDriver;
    
    
   
    
    double myOutput;
    
    int noiseDriverCount, noiseFreq;
    
    maxiDelayline delayline;
    maxiFractionalDelay fracDelay;
    double delayOut;
    int delaySamps;
    
    //envelope
    maxiEnv noiseEnv;
   
    int midiNote;
    double mtof;
    double ftoms;
    double mstosamps;
    
    //GUI stuff
    //ofParameter<float> cutoff;
    
    ofParameter<float> cutoff;
    double hz; //cutoff frequency
    double hzNormd; //cutoff normalised
    ofxPanel gui;
    
    
    //randomNoise variables
    float rando;
    float randa;
    float amp;
    
		
};

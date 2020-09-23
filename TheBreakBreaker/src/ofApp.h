#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "ofxGui.h"

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
    
    void loadSamples();
    void chopper();
    void envelopeSetups();
    void zingerSetup();
    void maxiAudioSetup();
    void guiSetup();
    void zingerDive();
    void zingerClimb();
    void delayUnit();
    void sampleParamsUpdate();
    void switchSample(maxiSample& sample);
    
    void divisionNumberChanged(int & divNumber);
    
    void updateGuiChange();
    
    void playbackSpeedChanged(float &playbackSpeed);
    
    ofSoundStream soundStream; //rather than sending to rtaudio, sends to ofsound
    
    /* ofxMaxi*/
    void audioIn(ofSoundBuffer& input) override; // not used in this example
    void audioOut(ofSoundBuffer& output) override;
    
    //oscillator stuff:
    maxiOsc osco;
    double oscOut;
    //Sample stuff
    maxiSample beat1, beat2, beat3, beat4, vocal; //sample
    maxiSample currentBeat;
    
    bool isPlaying;
    
    //font
    ofTrueTypeFont font1, font2, font3;
    
    maxiOsc myPhasor, clockPhasor; //this phasor is later cast to an int and controls sample playback
    maxiFractionalDelay myDelay;
    double delayedOutput;
    long lengthSamps; //length of the audio file in samples
    int start;
    int finish;
    double lengthMS; //audio file length miliseconds
    double lengthS; //audio file length seconds
    double chunk; //total sample / division
    int division; // 1/8, 1/16 etc.
    int startPoints; //division - 1
    
    double freq; //playback frequency, set to 1 / lengthS
    double speed; //multiplied by the frequency. 1 = normal
    double sample1;
    
    double sample2;
    int currentCount;
    
    int clocker;
    
    //delay stuff
    double delaySamps; //delaytime in samples
    double delayMS; //delaytime in miliseconds
    
    //envelope stuff
    maxiEnv myEnv;
    double myCurrentVolume;
    
    //delayline phasor
    maxiOsc dlinePhasor;
    maxiOsc dlineReverser;
    double currentDtime;
    double currentDtimeRev;
    long currentDsamps;
    bool zingerDiveBool; //true on keypress
    bool zingerClimbBool;
    //double diveFB; //feedback
    //rdouble climbFB;
    double feedback;
    int zingerAmp; //how far does the delay line travel?
    
    //GUI stuff
    
    ofParameter<float> climbFB;
    ofParameter<float> diveFB;
    
  
    
    ofParameter<float> playbackSpeed;
    //int chopNumberInt;
    ofxPanel gui;
};

#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "block.hpp"

class ofApp : public ofBaseApp{

	public:
    void lightsCamSetup();
    void setup() override;
    void soundSetup();
    
    void waveformMaker();
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
    
    
    
    void colourBlocks();
    
    bool isPlaying;
    
    maxiSample audioFile;
    double player;
    
    int counter;
    
    int lenSamps;
    
    int count;
    
    //store the RMS values
    std::vector<double> RMS;
    
    
    //store the blocks
    std::vector<Block*> blocks;
    
    ofColor purple{138,43,226};
    ofColor green{152,251,152};
    ofColor grey{112,128,144};
    
    float blockX = 9;
    float blockY = 0;
    float blockZ = 0;
    
    float camXpos;
    
    float RMS_multiplier = 400;
    float blockWidth = 8;
    float blockDepth = 20;
    
    
    /* ofxMaxi*/
    void audioIn(ofSoundBuffer& input) override; // not used in this example
    void audioOut(ofSoundBuffer& output) override;
    
    //maxiSample clip1;
    ofSoundStream soundStream;

    double segmentAmount;
    
    double waveformWidth;
    
    //SHAPES
    ofBoxPrimitive box;
    ofEasyCam cam;
    ofLight light, light2;
    
    //FONT
    ofTrueTypeFont font1, font2;
    
   
		
};

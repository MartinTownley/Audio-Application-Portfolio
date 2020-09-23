//33537140
//Advanced Audiovisual Processing
//Portfolio Project 4

#include "ofApp.h"
#include <numeric>
#include <vector>
#include <cmath>


void ofApp::lightsCamSetup(){
    
    //3D LIGHTS AND STUFF
    
    camXpos = 0;
    
    ofEnableDepthTest();
    ofEnableLighting();
    ofEnableNormalizedTexCoords();
    light.setPointLight();
    light2.setPointLight();
    light.setDiffuseColor(ofFloatColor(1,1,1));
    light2.setDiffuseColor(ofFloatColor(0.5,0.5,0.5));
    
    light.setPosition(ofGetWidth()*.5,
                      ofGetHeight()*.7,300);
    
    light2.setPosition(ofGetWidth()*.3,
                       ofGetHeight()*.3,600);
    
    ofSetVerticalSync(true);
    
    // cam.setPosition(camXpos,0,0);
    cam.setDistance(1000);
}

void ofApp::soundSetup(){
    
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
}
//--------------------------------------------------------------
void ofApp::setup(){
    
    
    font1.load("jos.otf",180);
    
    counter = 0;
    
    isPlaying = false;
    
    lightsCamSetup();
    
    soundSetup();
    
    waveformMaker();
//-----------------------------
    waveformWidth = blockX * segmentAmount;
    std::cout<<"Width: "<< waveformWidth <<std::endl;
    
}

void ofApp::waveformMaker(){
    
    //DRAWING STUFF
    //we want to retrieve the amplitude values of the audio file, segment them, push them to a 2d vector
    
    // 1. load audio file
    audioFile.load(ofToDataPath("avpclip1.wav"));
    
    //audioFile.load("/Users/martintownley/Documents/Goldsmiths_3/AAVP/16BitWavs/byrdmax_16.wav");
    
    // 2. set length in samples to a variable
    lenSamps = audioFile.getLength();
    
    std::cout<<"len: " << lenSamps<<std::endl;
    
    int segmentSize = 1024; //same as buffersize
    
    // 3. the amount of blocks is total samps / segmentSize:
    segmentAmount = lenSamps / segmentSize;
    
    std::cout<< "segmentAmount: "<<segmentAmount <<std::endl;
    
    //create a vector of vectors: the outer vector is the number of segments, the inner vector is the number of samples in each segment:
    // 4. define vector of vectors
    vector< vector<double> > segments;
    
    // 5, 6, 7: define inner vector, fill inner vector, push to outer vector:
    for(int i = 0; i < segmentAmount; ++i)
    {
        // 5. define inner vector
        vector<double> ampVals;
        for(int j = 0; j < segmentSize; ++j)
        {
            //6. fill inner vector with amplitude values
            ampVals.push_back(audioFile.playOnce());
            
        }
        
        // 7. push inner vector to outer vector:
        segments.push_back(ampVals);
    }
    //  RMS Calculation: square each sample, get average, square root, then push values to the RMS vector.
    for(int i = 0; i<segments.size(); ++i)
    {
        for(int j = 0; j < segments[i].size(); ++j)
        {
            // 8. square every sample
            segments[i][j] = pow (segments[i][j], 2);
            
        }
        // 9. sum
        double ampSum = accumulate(segments[i].begin(), segments[i].end(), 0.);
        
        std::cout<< "sum: "<<ampSum <<std::endl;
        // 10. average
        double av = ampSum / segmentSize;
        std::cout<< "average: " <<av <<std::endl;
        // 11. square root:
        double root = sqrt(av);
        std::cout<< "RMS: " << root << std::endl;
        
        // 12. push back the RMS values to an RMS vector:
        RMS.push_back(root);
        
    }
    
    //push the visual blocks back to a vector
    
    for (int i = 0; i < segmentAmount; ++i)
    {
       
        
        Block* b = new Block
        {i * blockX - ofGetWidth()*2,
            blockY,
            blockZ,
            blockWidth,
            static_cast<float>((RMS[i] * 400)),
            blockDepth};
        
        blocks.push_back(b);
    }
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    //this conditional makes sure that non-existent blocks aren't being coloured, which crashes the program
    if(counter< lenSamps)
    {
    colourBlocks();
    }
    
}

void ofApp::audioIn(ofSoundBuffer& input){
    
}

void ofApp::audioOut(ofSoundBuffer& output){
    
    float volume = 0.7f;
    float player = 0.0f;
    
    
    std::size_t outChannels = output.getNumChannels();
    
    for (std::size_t i = 0; i < output.getNumFrames(); ++i){
        
        //player = audioFile.play();
        
        if(isPlaying){
            player = audioFile.play();
        } else {
            player = 0.0f;
        }
        
        output[i * outChannels] = player * volume;

        output[i * outChannels + 1] = output[i * outChannels];
        
    }
    
    //if you keep incrementing the counter, the program will try and colour non existing blocks, so stop it when it finishes the audio file
    if(counter < segmentAmount && isPlaying == true)
    {
    counter += 1;
    }
}

void ofApp::colourBlocks(){
    
    //this gets called in the update function
    //this will sample the counter at the speed of the update function
    int countSnapshot = counter;
    
    //this function iterates from zero up to the counter number, and colours all the blocks within that range.
    
    for(int i = 0; i < counter; ++i)
    {
        blocks[i]->setColor(purple);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    light.enable();
    light2.enable();
    cam.begin();
    
    
    ofDrawBitmapString("PUSH SPACE TO PLAY/PAUSE SOUND FILE, SCROLL TO ZOOM, DRAG TO MOVE AROUND", -1000, 100);
    
    ofSetColor(0,0,0);
    font1.drawString("3-D Waveform Visualiser", -1400, -300);
    ofSetColor(255);
    for (Block* b : blocks){
        
        b->draw();
    }
    
    cam.end();
    light.disable();
    light2.disable();
    
    
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
//spacebar to play and pause
    if(key == ' ' ){
        isPlaying = !isPlaying;
    }
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

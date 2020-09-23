//33537140
//Advanced Audiovisual Processing
//Portfolio Project 2
//December 2019
//Credit to Callum Magill for the collaborative development of parts of this code (cmagi001@gold.ac.uk)

#include "ofApp.h"

//--------------------------------------------------------------


void ofApp::loadSamples(){
    beat1.load(ofToDataPath("AmenFineTune_16.wav"));
    beat2.load(ofToDataPath("apache_16.wav"));
    beat3.load(ofToDataPath("byrdmax_16.wav"));
    beat4.load(ofToDataPath("hotpants_16.wav"));
    vocal.load(ofToDataPath("Keith16.wav"));
}

void ofApp::zingerSetup(){
    zingerDiveBool = false; //this controls the zinger envelope
    zingerClimbBool = false;
    currentDtime = 0.;
    feedback = 0.0;
    zingerAmp = 100;
}

void ofApp::playbackSpeedChanged(float &playbackSpeed){
    
    speed = playbackSpeed;
}

void ofApp::setup(){
    
    font1.load("frostgiant.ttf",40);
    font2.load("amurg.otf", 10);
    
    isPlaying = false;
    ofBackground(75,0,130);
    loadSamples();
    division = 24;

    //this listener makes sure that the playback speed starts at the correct value
playbackSpeed.addListener(this, &ofApp::playbackSpeedChanged);
    
    guiSetup();
    
    //currentBeat gets set to different samples on keypresses
    currentBeat = beat1;
    
    
    // Maximilian audio stuff
    int sampleRate = 44100; /* Sampling Rate */
    int bufferSize= 512; /* Buffer Size. you have to fill this buffer with sound using the for loop in the audioOut method */
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    
    //setup the zinger effect
    zingerSetup();
    
    //call the envelope setups
    envelopeSetups();
    
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
void ofApp::update(){
    sampleParamsUpdate();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    gui.draw();
    
    //ofDrawBitmapString("THE ZINGER!", 250, 10);
    
    ofDrawBitmapString("Hold Q to DIVE", 215, 45);
    ofDrawBitmapString("Hold W to CLIMB", 215, 64);
    //ofDrawBitmapString("Keys 1-5 switch samples", 215, 103);
    //ofDrawBitmapString("Hit SpaceBar to Play/Pause", 215,122);
    
    
    ofDrawBitmapString("33537140", 750, 10);
    ofDrawBitmapString("Advanced Audiovisual Processing", 750, 30);
    ofDrawBitmapString("Portfolio Project 2", 750, 50);
    ofDrawBitmapString("December 2019", 750, 70);
    
    font1.drawString("The Break-Breaker", 10, 200);
    font2.drawString("Hit Space to Play / Pause", 20, 220);
    font2.drawString("Keys 1-5 switch samples", 20, 240);
    font2.drawString("Q & W engage effects", 20, 260);
}

//--------------------------------------------------------------
void ofApp::audioIn(ofSoundBuffer& input){
    std::size_t nChannels = input.getNumChannels();
    for (size_t i = 0; i < input.getNumFrames(); i++)
    {
        // handle input here
    }
}


void ofApp::zingerDive(){
    //this sets the delay time to a phasor, so you get ramps that cause pitch effects on the delay line (doppler)
    currentDtime =   (dlinePhasor.phasor(freq * 2) * zingerAmp) ;
    
    currentDsamps = currentDtime * 44.1; //convert MS to samps
}

void ofApp::zingerClimb(){
    //it's a reverse phasor this time
    currentDtime = ((dlineReverser.phasor(freq*2) * (-1)) + 1) * zingerAmp;
    
    currentDsamps = currentDtime * 44.1; //convert MS to samps
}

void ofApp::chopper(){
    //This function uses a phasor to trigger playback of the sample at regular intervals, but random locations.
    //cast the phasor to an int to make some trigger points
    
    currentCount = (int)myPhasor.phasor(freq * division);
    
    //code below triggers a new starting point of the sample at the frequency of the phasor, and then triggers the playback.
    if (currentCount == 1)
    {
        start = currentCount * rand()% startPoints;
        finish = start + 1;
        currentBeat.trigger(); //start
    }
}



void ofApp::envelopeSetups(){
    //volume envelope setup
    myEnv.setAttack(0);
    myEnv.setDecay(1);
    myEnv.setSustain(1);
    myEnv.setRelease(500);
}

void ofApp::delayUnit(){
    
    if(zingerDiveBool)
    {
        feedback = diveFB;
        
    }
    if(zingerClimbBool)
    {
        feedback = climbFB;
    }

    delayedOutput = myDelay.dl(sample1, currentDsamps, feedback);
    
 
}

void ofApp::switchSample(maxiSample& sample){
    
    currentBeat = sample;
}

//--------------------------------------------------------------
void ofApp::audioOut(ofSoundBuffer& output){
    
    sample1 = 0.0f;
    
    std::size_t outChannels = output.getNumChannels();
    
    for (int i = 0; i < output.getNumFrames(); ++i){
        
        //set the sample variable with its variable frequencies, start times and end times
        
        if(isPlaying){
            sample1 = currentBeat.play(freq * division, chunk * start, chunk * finish);
        } else {
            sample1 = 0.0f;
        }
        
        //call the chopper function to chop it up!
        chopper();
        
        //the zinger booleans are flipped by keypresses
        if(zingerDiveBool)
        {
            zingerDive(); //this function is run on keypress
        }
        
        
        if(zingerClimbBool)
        {
            zingerClimb(); //run on keypress (keypress flips a boolean)
        }
        
    //audio is routed through the delayunit function
    delayUnit();
        
        //if either effect is engaged, add the delayed output to the audio out signal
        if(zingerDiveBool || zingerClimbBool) {
        
            output[i * outChannels] = sample1 + (delayedOutput * 0.65);
        } else {
            output[i * outChannels] = sample1;
        }
        
        output[i * outChannels + 1] = output[i * outChannels];
        
    }
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' ' ){
        isPlaying = !isPlaying;
    }
    
    
    switch (key) {
        case 'q':
            zingerDiveBool = true;
            break;
        case 'w':
            zingerClimbBool = true;
            break;
        case '1':
            
            switchSample(beat1);
            division = 24;
            std::cout<<currentBeat.length<<std::endl;
            
            break;
        case '2':
            
            switchSample(beat2);
            division = 16;
            
             std::cout<<currentBeat.length<<std::endl;
            break;
        case '3':
            
            switchSample(beat3);
            division = 8;
            std::cout<<currentBeat.length<<std::endl;
            
            break;
        case '4':
            
            switchSample(beat4);
            division = 16;
            std::cout<<currentBeat.getSummary()<<std::endl;
            
            break;
        case '5':
            switchSample(vocal);
            division = 128;
            
            
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    switch (key) {
        case 'q':
            zingerDiveBool = false;
            break;
        case 'w':
            zingerClimbBool = false;
            break;
        default:
            break;
            
    }
}

void ofApp::guiSetup(){
    
    //add this listener before setting up so the initial division number is correct
    
    gui.setup("Zinger Effect");
    gui.add(diveFB.set("dive feedback", 0.9, 0., 0.99));
    gui.add(climbFB.set("climb feedback", 0.9, 0., 0.99));
    gui.add(playbackSpeed.set("speed", 1, 0.5, 1.5));
    
}
void ofApp::sampleParamsUpdate(){
    
    
    startPoints = (division - 1); //these will be randomised with rand(), which starts from zero, so let's minus 1 to the number of divisions.
    
    lengthSamps = currentBeat.length;
    
    lengthMS = lengthSamps / 44.1;
    lengthS = lengthMS / 1000;
    
    //speed = 1;
    freq = 1. / lengthS * speed; //play the whole sample once, for its entire length, multiplied by the speed
    chunk = lengthSamps / division;
    
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

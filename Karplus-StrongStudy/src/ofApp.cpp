#include "ofApp.h"

void ofApp::envelopeSetup(){
    
    noiseEnv.setAttack(0);
    noiseEnv.setDecay(50);
    noiseEnv.setSustain(0.0001);
    noiseEnv.setRelease(1);
    //noiseEnv.trigger = 0;
}

void ofApp::guiSetup(){
    gui.setup("filter parameters");
    gui.add(cutoff.set("cutoff", 7.,0., 14.));
    
    font1.load("stan.otf", 40);
    font2.load("Wardness.otf", 20);
    
}

void ofApp::oscSetup(){
    //OSC receiver
    receiver.setup(RPORT);
}

void ofApp::ofSoundSetup(){
    
    
    int sampleRate = 44100; /* Sampling Rate */
    int bufferSize= 512; /* Buffer Size. you have to fill this buffer with sound using the for loop in the audioOut method */
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    //needs to be called last in the master setup
    ofSoundStreamSettings settings;
    settings.setOutListener(this);
    settings.sampleRate = sampleRate;
    settings.numOutputChannels = 2;
    settings.numInputChannels = 0;
    settings.bufferSize = bufferSize;
    soundStream.setup(settings);
}

double ofApp::randomNoise(){
    rando = rand() % 200;
    noise = (rando - 100) /  100; //scale and offset to give a value between -1 and 1
    
    return noise;
}

double ofApp::currentVolume(){
   
    vol = noiseEnv.adsr(1., noiseEnv.trigger);
    return vol;
}

double ofApp::noiseBurst(){
    burst = randomNoise() * currentVolume();
    
    
    return burst;
}

int ofApp::currentCount(){
    
    count = counter.phasor(0.5, 1, 100);
    
    return count;
}
//-----------
void ofApp::envTrigger(){
    
    while (receiver.hasWaitingMessages())
    {
        //get the trigger message
        ofxOscMessage m;
        receiver.getNextMessage(m);
        
        //std::cout<<"msg receivedd! "<<m.getArgAsInt(0) <<std::endl;
        
        if(m.getAddress() == "/trig")
        {
        noiseEnv.trigger = m.getArgAsInt(0);
            std::cout<<delaySamps<<std::endl;
        } else if(m.getAddress() == "/midiNote")
                  {
                      midiNote = m.getArgAsInt(0);
                  }
    }
}

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(221,160,221);
    
    guiSetup();
    oscSetup();
    envelopeSetup();
    ofSoundSetup();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    //convert midi to frequency
    mtof = 261 * pow(2, (midiNote - 60)/ 12.0);
    
    //convert frequency to miliseconds for the delay
    ftoms = 1000. / mtof;
    
    //scaling filter cutoff to a curve, giving resolution at the low end
    hz = std::pow(2, cutoff);
    
    hzNormd = hz / 16384;
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    gui.draw();
    ofColor(0,0,0);
    ofDrawBitmapString("Hz: "+ ofToString(hz), 215, 45);
    ofDrawBitmapString("(Cutoff Frequency has been scaled to a curve", 215, 65);
                       
       ofDrawBitmapString("to give higher resolution in the low end)",215, 85 );
    
    ofDrawBitmapString("33537140", 750, 10);
    ofDrawBitmapString("Advanced Audiovisual Processing", 750, 30);
    ofDrawBitmapString("Portfolio Project 3", 750, 50);
    ofDrawBitmapString("December 2019", 750, 70);
    
    
    font1.drawString("Karplus-Strong", 10, 200);
    font2.drawString("Click around window for plucked-string simulation", 30, 240);
    
    
}
//-------------------

void ofApp::audioIn(ofSoundBuffer& input){
    std::size_t nChannels = input.getNumChannels();
    for (size_t i = 0; i < input.getNumFrames(); i++)
    {
        // handle input here
    }
}

void ofApp::audioOut(ofSoundBuffer& output){
    
    std::size_t outChannels = output.getNumChannels();
    for (int i = 0; i < output.getNumFrames(); ++i){
        
        
        //pass the noise burst through the filter:
        
        filterOut = myFilter.lopass(noiseBurst(), hzNormd);
        
        //pass the filtered noiseburst through the delay line:
        delayOut = fracDelay.dl(filterOut, delaySamps, 0.97);
        
        output[i * outChannels] = (filterOut + delayOut) * 3;
        
        output[i * outChannels + 1] = output[i * outChannels];
        
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
    x = (x - 1024) * -1;
    
    mouseX = x;
    
    mouseY = y;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    
    delaySamps = (mouseX / 1.6)  + 44;
    
      noiseEnv.trigger = 1;
    
    std::cout<<ofGetWidth()<<std::endl;
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
    noiseEnv.trigger = 0;
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

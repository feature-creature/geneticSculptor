#include "ofApp.h"
// ?? what is this for
#define FRAME_WIDTH 80
#define FRAME_HEIGHT 60

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255);
    
    // initialize forest settings
    popmax = 8;
    mutationRate = 0.025;
    forrest.setup(mutationRate, popmax);
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofTranslate(ofGetWidth()/20, ofGetHeight()-30);
    forrest.draw();
}

//--------------------------------------------------------------
void ofApp::displayInfo(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    // keys 0-7
    if (key>=47 || key <=56) {
        forrest.pick(ofToInt(ofToString(char(key))));
    }

    // init generation
    if (key == 'g' || key == 'G') {
        forrest.selection();
        forrest.generate();
    }

}

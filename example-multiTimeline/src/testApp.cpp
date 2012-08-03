#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofSetEscapeQuitsApp(false);
    
	timeline.setup();
    timeline.setFrameRate(24);
	timeline.setDurationInSeconds(100);
        
    timeline.addFlags("StartStop");
    
    ofAddListener(timeline.events().bangFired, this, &testApp::bangFired);

    for(int i = 0; i < 10; i++){
        ofxTimeline* t = new ofxTimeline();
		t->setup();
        t->setDurationInFrames(400);
        t->addKeyframes(ofToString(i));
        t->setShowTicker(false);
        t->setShowZoomer(false);
        t->setLockWidthToWindow(false);
        t->setWidth(ofGetWidth()/2);
        t->setLoopType(OF_LOOP_NORMAL);
        sublines.push_back(t);	
    }
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    
	ofBackground(.15*255);
	timeline.draw(); 
    sublines[0]->setOffset(timeline.getBottomLeft());
    for(int i = 0; i < sublines.size(); i++){
        if(i != 0){
            sublines[i]->setOffset(sublines[i-1]->getBottomLeft());
        }
        sublines[i]->draw();
    }
    
    ofDrawBitmapString(ofToString(ofGetFrameRate(), 3), ofGetWidth()-100, ofGetHeight()-50);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if(timeline.isModal()){
        return;
    }
    
	if(key ==  ' '){
        timeline.togglePlay();      
        if(!timeline.getIsPlaying()){
            for(int i = 0; i < sublines.size(); i++){
                sublines[i]->stop();
            }            
        }
    }
}

//--------------------------------------------------------------
void testApp::bangFired(ofxTLBangEventArgs& bang){
    
    //This is our own custom flag protocol to enslave playback
    //on the sub timelines
    //a flag that is start>3 or stop>2 will start and stop those timelines
	vector<string> command = ofSplitString(bang.flag, ">");
    if(command.size() == 2){
        int trackIndex = ofToInt(command[1]);           
        if(trackIndex >= 0 && trackIndex < sublines.size()){
            if(command[0] == "start"){
                sublines[trackIndex]->play();
            }
            else if(command[0] == "stop"){
                sublines[trackIndex]->stop();
            }    
        }
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}

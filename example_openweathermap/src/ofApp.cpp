#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    // weather
    string apiKey = "";
    string cityAndCountryCode = "Mainz,DE";
    
    weather.setApiKey(apiKey);
    weather.setCityAndCountryCode(cityAndCountryCode);
    weather.setHasLocalFile(true);
    weather.parseData(weather.loadData());
    
    // font
    myfont.load("fonts/Waukegan LDO Extended Bold.ttf", 32);
    mysmallfont.load("fonts/Waukegan LDO Extended Bold.ttf", 16);
    
    startTimeMillis = ofGetElapsedTimeMillis();
}

//--------------------------------------------------------------
void ofApp::update(){
    // hardcoded interval to call weather.update()
    elapsedTimeMillis = ofGetElapsedTimeMillis() - startTimeMillis;
    // update weather every 16minutes
    if (elapsedTimeMillis > 1000000) {
        weather.parseData(weather.loadData());
        startTimeMillis = ofGetElapsedTimeMillis();
    }
    currentTemperature = weather.getCurrentTemperature();
    
    currentWindSpeed = weather.getCurrentWindSpeed();
    currentWindDirection = weather.getCurrentWindDirection();
    currentClouds = weather.getCurrentClouds();
    currentAvg = weather.getAverageTemperature();
    currentTempTrend = weather.getTemperatureTrend();
    rainOrSnow = weather.getCurrentRainOrSnow();
    currentHumidity = weather.getCurrentHumidity();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofColor  bgInnerColor = calcBgColor();
    ofColor  bgOuterColor(bgInnerColor.getHex());
    bgOuterColor.setBrightness(bgInnerColor.getBrightness()/2.5);
    
    ofBackgroundGradient(bgInnerColor, bgOuterColor);
    
    myfont.drawString(ofToString(currentTemperature) + "°", 100, 80);

    mysmallfont.drawString(ofToString(currentHumidity) + " humidity", 100, 100);
    mysmallfont.drawString(ofToString(currentClouds) + "% clouds", 100, 120);
    mysmallfont.drawString(ofToString(currentWindSpeed) + "mps", 100, 140);
    mysmallfont.drawString(ofToString(currentWindDirection) + " wind direction", 100, 160);
    if(rainOrSnow){
    mysmallfont.drawString("~" + ofToString(weather.getAveragePrecipitation()) + ", " + ofToString(weather.getPrecipitation()) + ((rainOrSnow == OFX_WEATHER_RAIN) ? " Rain" : " Snow"), 100, 180);
    }
    mysmallfont.drawString("~" + ofToString(currentAvg) + "°", 100, 200);
    if (currentTempTrend == 1) {
        mysmallfont.drawString("TREND TEMP UP", 100, 220);
    } else if (currentTempTrend == -1) {
        mysmallfont.drawString("TREND TEMP DOWN", 100, 220);
    } else {
        mysmallfont.drawString("TREND TEMP STAYS", 100, 220);
    }
    // draw wind direction
    ofPushMatrix();
      ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
      ofRotateDeg(currentWindDirection);
      ofDrawTriangle(50,10,10,40,90,40);
    ofPopMatrix();
}

//--------------------------------------------------------------

ofColor ofApp::calcBgColor() {
    // todo: time or sun-set/rise based colors
    int hour = ofGetHours();
    ofColor c(48, 196, 255);
    c.setHueAngle(hour);
    return c;
};


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

#pragma once

#include "ofMain.h"
#include "ofxOpenWeatherMap.hpp"


class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
private:
    ofTrueTypeFont myfont;
    ofTrueTypeFont mysmallfont;

    ofxOpenWeatherMap weather;
    float currentTemperature;
    float currentWindSpeed;
    float currentRain;
    float currentAvgRain;
    float currentAvg;
    int currentWindDirection;
    int currentClouds;
    int currentTempTrend;
    uint64_t startTimeMillis;
    uint64_t elapsedTimeMillis;
    ofColor calcBgColor();
    int colorIteration{0};
};

//
//  ofxOpenWeatherMap.hpp
//  decisionmaker
//
//  Created by pce on 15.08.21.
//

#ifndef ofxOpenWeatherMap_hpp
#define ofxOpenWeatherMap_hpp

//#include <stdio.h>
#include <vector>

#include "ofMain.h"
#include "ofxAbstractWeather.hpp"



class ofxOpenWeatherMap : ofxAbstractWeather {
public:
    void setApiKey(string key);
    void setCityAndCountryCode(string city);
    void setHasLocalFile(bool hasLocalFile);
    void setLocalFilename(string filename);
    ofJson loadData();
    void parseData(ofJson js);
    string getSunRise();
    string getSunSet();
    WeatherData getCurrentData();
    float getCurrentTemperature();
    float getCurrentWindSpeed();
    float getPrecipitation();
    int getCurrentWindDirection();
    int getCurrentClouds();
    float getAveragePrecipitation();
    float getAverageTemperature();
    int getTemperatureTrend();

private:
    WeatherData currentData;
    std::vector<WeatherData> forecasts;
    std::string sunRise;
    std::string sunSet;
    bool hasLocalFile{false};
    string localFilename{"weather.xml"};
    string apiKey{""};
    string cityAndCountryCode{""};
};

#endif /* ofxOpenWeatherMap_hpp */

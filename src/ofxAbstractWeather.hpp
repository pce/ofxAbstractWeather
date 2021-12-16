//
//  ofxAbstractWeather.hpp
//  decisionmaker
//
//  Created by pce on 15.08.21.
//

#ifndef ofxAbstractWeather_hpp
#define ofxAbstractWeather_hpp

// #include <stdio.h>
#include <vector>

#include "ofMain.h"

struct WeatherData {
    float temperature{.0};
    float windSpeed{.0};
    float windDirection{.0};
    int clouds{0};
    int humidity{0};
    float precipitation{.0};
    int rainOrSnow{0}; // 0=none, 1=rain, 2=snow
    std::string from{""};
    std::string to{""};
    static const int rain{1};
    static const int snow{2};
};

class ofxAbstractWeather {
  public:
    virtual WeatherData getCurrentData() = 0;
    virtual float getCurrentTemperature() = 0;
    // virtual float getCurrentWindSpeed() = 0;
};

#endif /* ofxAbstractWeather_hpp */

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
  float temperature;
  float windSpeed;
  float windDirection;
  int clouds;
  float precipitation;
  int rainOrSnow{0}; // 0=none, 1=rain, 2=snow
  std::string from;
  std::string to;
};

#define OFX_WEATHER_RAIN 1
#define OFX_WEATHER_SNOW 2


class ofxAbstractWeather {
  public:
    virtual WeatherData getCurrentData() = 0;
    virtual float getCurrentTemperature() = 0;
    // virtual float getCurrentWindSpeed() = 0;
};

#endif /* ofxAbstractWeather_hpp */

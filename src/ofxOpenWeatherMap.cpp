//
//  ofxOpenWeatherMap.cpp
//  decisionmaker
//
//  Created by pce on 15.08.21.
//

#include "ofxOpenWeatherMap.hpp"

using namespace std;


ofJson ofxOpenWeatherMap::loadData() {
    string url = "http://api.openweathermap.org/data/2.5/forecast?q={cityAndCountryCode}&appid={apiKey}";
    
    ofStringReplace(url, "{apiKey}", apiKey);
    ofStringReplace(url, "{cityAndCountryCode}", cityAndCountryCode);
    
    ofLog() << url;
    ofHttpResponse response = ofLoadURL(url);
    ofLog() << response.data;
    
    ofJson js;
    try
    {
        js = ofJson::parse(response.data);
    }
    catch (ofJson::parse_error& ex)
    {
        std::cerr << "parse error at byte " << ex.byte << std::endl;
    }
    
    return js;
}

void ofxOpenWeatherMap::parseData(ofJson js) {
    // ofLog() << js;

    // global weatherdata
    auto sunrise = js.at("city").at("sunrise");
    auto sunset  = js.at("city").at("sunset");
    // auto t = std::chrono::system_clock::to_time_t(sunrise);
    // ofLog() << t;
    // ofLog() << sunrise;
    
    sunRise = std::to_string(static_cast<int>(js.at("city").at("sunrise")));
    sunSet  = std::to_string(static_cast<int>(js.at("city").at("sunset")));

    // time-nodes
    for (auto &timeNode : js.at("list")) {
        WeatherData weatherData;
        weatherData.from = timeNode.at("dt_txt");
        auto temperature = static_cast<float>(timeNode.at("main").at("temp")) - 273.15;
        // ofLog() << temperature;
        weatherData.temperature = temperature;
        // windspeed
        auto windSpeed = timeNode.at("wind").at("speed");
        // mps="2.48" unit="m/s" name="Light breeze"
        weatherData.windSpeed = windSpeed;
        
        auto windDirection = timeNode.at("wind").at("deg");
        weatherData.windDirection = windDirection;
            
        // rain
        try {
            auto precipitation = timeNode.at("rain").at("3h");
            weatherData.precipitation = precipitation;
            weatherData.rainOrSnow = OFX_WEATHER_RAIN;
        } catch (ofJson::out_of_range& e) {
            std::cout << "message: " << e.what() << '\n'
                      << "exception id: " << e.id << std::endl;
        }
            
        // snow
        try {
            auto precipitation = timeNode.at("snow").at("3h");
            weatherData.precipitation = precipitation;
            weatherData.rainOrSnow = OFX_WEATHER_SNOW;
        } catch (ofJson::out_of_range& e) {
            std::cout << "message: " << e.what() << '\n'
                      << "exception id: " << e.id << std::endl;
        }
        
        // clouds in percent
        auto clouds = timeNode.at("clouds").at("all");
        weatherData.clouds = clouds;
        
        forecasts.push_back(weatherData);
    }
    // TODO check current time and time node
    currentData = forecasts.at(0);
}

float ofxOpenWeatherMap::getAverageTemperature() {
    // reading forecasts
    float temp;
    int max = forecasts.size();
    if (max > 5) {
        max = 5;
    }
    
    for(unsigned i=0; i < max; i++) {
        temp += forecasts.at(i).temperature ;
    }
    return temp / max;
}

float ofxOpenWeatherMap::getAveragePrecipitation() {
    // reading forecasts
    float temp;
    int max = forecasts.size();
    if (max > 5) {
        max = 5;
    }
    
    for(unsigned i=0; i < max; i++) {
        temp += forecasts.at(i).precipitation ;
    }
    return temp / max;
}


int ofxOpenWeatherMap::getTemperatureTrend() {
    if (getAverageTemperature() >= getCurrentTemperature()) {
        return (getAverageTemperature() == getCurrentTemperature()) ? 0 : 1;
    } else {
        return -1;
    }
}


string ofxOpenWeatherMap::getSunRise() {
    return sunRise;
}

string ofxOpenWeatherMap::getSunSet() {
    return sunSet;
}


WeatherData ofxOpenWeatherMap::getCurrentData() {
    return currentData;
}


float ofxOpenWeatherMap::getCurrentTemperature() {
    return currentData.temperature;
}

float ofxOpenWeatherMap::getCurrentWindSpeed() {
    return currentData.windSpeed;
}

float ofxOpenWeatherMap::getPrecipitation() {
    return currentData.precipitation;
}



int ofxOpenWeatherMap::getCurrentWindDirection() {
    return currentData.windDirection;
}

int ofxOpenWeatherMap::getCurrentClouds() {
    return currentData.clouds;
}


void ofxOpenWeatherMap::setHasLocalFile(bool hasLocal) {
    hasLocalFile = hasLocal;
}

void ofxOpenWeatherMap::setLocalFilename(string filename) {
   localFilename = filename; 
}

void ofxOpenWeatherMap::setApiKey(string key) {
    apiKey = key;
}

void ofxOpenWeatherMap::setCityAndCountryCode(string city) {
    cityAndCountryCode = city;
}

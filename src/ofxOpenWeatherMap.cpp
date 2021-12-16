//
//  ofxOpenWeatherMap.cpp
//  decisionmaker
//
//  Created by pce on 15.08.21.
//

#include "ofxOpenWeatherMap.hpp"

using namespace std;


ofJson ofxOpenWeatherMap::loadData(){
    
    if (hasLocalFile) {
        ofLog(OF_LOG_VERBOSE, "ofxAbstractWeather: load local filename=" + localFilename);
        return ofLoadJson(localFilename);
    }
    
    string url = "http://api.openweathermap.org/data/2.5/forecast?q={cityAndCountryCode}&appid={apiKey}&units={units}";
    
    ofStringReplace(url, "{cityAndCountryCode}", cityAndCountryCode);
    ofStringReplace(url, "{apiKey}", apiKey);
    ofStringReplace(url, "{units}", units);

    ofLog(OF_LOG_VERBOSE, "ofxAbstractWeather: " + url);
    ofHttpResponse response = ofLoadURL(url);
    ofLog(OF_LOG_VERBOSE, "ofxAbstractWeather: " + ofToString(response.data));
    
    ofJson js;
    try{
        js = ofJson::parse(response.data);
    }catch(ofJson::parse_error& ex){
        ofLog(OF_LOG_ERROR, "ofxAbstractWeather: couldn't parse json at " + ofToString( ex.byte));
    }
    return js;
}

void ofxOpenWeatherMap::parseData(ofJson js){
    // global weatherdata
    auto sunrise = js.at("city").at("sunrise");
    auto sunset  = js.at("city").at("sunset");
    // ofLog() << t;
    sunRise = std::to_string(static_cast<int>(js.at("city").at("sunrise")));
    sunSet  = std::to_string(static_cast<int>(js.at("city").at("sunset")));

    // time-nodes
    for(auto &timeNode : js.at("list")) {
        WeatherData weatherData;
        weatherData.from = timeNode.at("dt_txt");
        auto temperature = static_cast<float>(timeNode.at("main").at("temp"));
        // ofLog() << temperature;
        weatherData.temperature = temperature;
        // humidity
        weatherData.humidity = timeNode.at("main").at("humidity");
        // windspeed
        auto windSpeed = timeNode.at("wind").at("speed");
        // mps="2.48" unit="m/s" name="Light breeze"
        weatherData.windSpeed = windSpeed;
                
        auto windDirection = timeNode.at("wind").at("deg");
        weatherData.windDirection = windDirection;
        // rain
        try{
            auto precipitation = timeNode.at("rain").at("3h");
            weatherData.precipitation = precipitation;
            weatherData.rainOrSnow = OFX_WEATHER_RAIN;
        }catch(ofJson::out_of_range& e){
            ofLogNotice() << "ofxAbstractWeather: parse json " << e.what() << ", exception id: " << e.id;
        }
        // snow
        try{
            auto precipitation = timeNode.at("snow").at("3h");
            weatherData.precipitation = precipitation;
            weatherData.rainOrSnow = OFX_WEATHER_SNOW;
        }catch(ofJson::out_of_range& e){
            ofLogNotice() << "ofxAbstractWeather: parse json " << e.what() << ", exception id: " << e.id;
        }
        // clouds in percent
        auto clouds = timeNode.at("clouds").at("all");
        weatherData.clouds = clouds;
        
        forecasts.push_back(weatherData);
    }
    currentData = forecasts.at(0);
}

float ofxOpenWeatherMap::getAverageTemperature(){
    // reading forecasts
    float temp;
    int max = forecasts.size();
    if(max > 5){
        max = 5;
    }
    
    for(unsigned i=0; i < max; i++){
        temp += forecasts.at(i).temperature ;
    }
    return temp / max;
}

float ofxOpenWeatherMap::getAveragePrecipitation(){
    // reading forecasts
    float temp;
    int max = forecasts.size();
    if(max > 5){
        max = 5;
    }
    for(unsigned i=0; i < max; i++){
        temp += forecasts.at(i).precipitation ;
    }
    return temp / max;
}


int ofxOpenWeatherMap::getTemperatureTrend(){
    if(getAverageTemperature() >= getCurrentTemperature()){
        return (getAverageTemperature() == getCurrentTemperature()) ? 0 : 1;
    }else{
        return -1;
    }
}

string ofxOpenWeatherMap::getSunRise(){
    return sunRise;
}

string ofxOpenWeatherMap::getSunSet(){
    return sunSet;
}

WeatherData ofxOpenWeatherMap::getCurrentData(){
    return currentData;
}

float ofxOpenWeatherMap::getCurrentTemperature(){
    return currentData.temperature;
}

float ofxOpenWeatherMap::getCurrentWindSpeed(){
    return currentData.windSpeed;
}

float ofxOpenWeatherMap::getPrecipitation(){
    return currentData.precipitation;
}

int ofxOpenWeatherMap::getCurrentWindDirection(){
    return currentData.windDirection;
}

int ofxOpenWeatherMap::getCurrentClouds(){
    return currentData.clouds;
}

int ofxOpenWeatherMap::getCurrentRainOrSnow(){
    return currentData.rainOrSnow;
}

int ofxOpenWeatherMap::getCurrentHumidity(){
    return currentData.humidity;
}

void ofxOpenWeatherMap::setHasLocalFile(bool hasLocal){
    hasLocalFile = hasLocal;
}

void ofxOpenWeatherMap::setLocalFilename(string filename){
   localFilename = filename; 
}

void ofxOpenWeatherMap::setApiKey(string key){
    apiKey = key;
}

void ofxOpenWeatherMap::setCityAndCountryCode(string city){
    cityAndCountryCode = city;
}

void ofxOpenWeatherMap::setUnits(string unitsOfMeasurement){
    // temperature in Fahrenheit: "imperial", Kelvin: "standard", Celsius: "metric"
    vector<string> availableUnits = {"standard", "metric", "imperial"};
    if (count(availableUnits.begin(), availableUnits.end(), unitsOfMeasurement) > 0) {
        units = unitsOfMeasurement;
    }else{
        ofLogWarning("ofxAbstractWeather: unknow given units, using metric system");
    }
}

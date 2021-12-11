# ofxAbstractWeather


Introduction
------------
OpenFrameworks Weather-Data addon.

### Usage/Examples

Create an API-Key at [OpenWeatherMap](https://openweathermap.org/) for the example.

```c++
void ofApp::setup(){
    weather.setApiKey(apiKey);
    weather.setCityAndCountryCode(cityAndCountryCode);
    weather.parseData(weather.loadData());
}

void ofApp::update(){
    currentTemperature = weather.getCurrentTemperature();
    currentWindSpeed = weather.getCurrentWindSpeed();
    currentWindDirection = weather.getCurrentWindDirection();
    currentClouds = weather.getCurrentClouds();
    currentRain = weather.getPrecipitation();
    currentAvg = weather.getAverageTemperature();
    currentTempTrend = weather.getTemperatureTrend();
    currentAvgRain = weather.getAveragePrecipitation();
}

```
![example_openweathermap](https://user-images.githubusercontent.com/445226/145677289-788d8c2d-52fd-4b23-bed3-b1c73b7518d9.png)


License
-------
[![MIT License](https://img.shields.io/apm/l/atomic-design-ui.svg?)](https://github.com/tterb/atomic-design-ui/blob/master/LICENSEs)


Installation
------------
Just drop the folder into the `openFrameworks/addons/` folder.  


Dependencies
------------
No Dependencies.

Compatibility
------------
Tested with OF 0.11.2

Known issues
------------
### Roadmap
- additional units: 
   - standard, metric, and imperial support
- rain/snow example
- add default icons
- add more providers/integrations

Version history
------------
Here you will find a version history (newest releases first), describing new features and changes to the addon. 

### Version 0.1 (DateInTheFuture):
Git-Tag to mark release 0.1 










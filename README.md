# ofxAbstractWeather


Introduction
------------
OpenFrameworks Weather-Data addon.

### Usage/Examples

Create an API-Key at [OpenWeatherMap](https://openweathermap.org/) 
or `weather.setHasLocalFile(true)` loads for example: `bin/data/openweathermap.json`


```c++
void ofApp::setup(){
    weather.setApiKey(apiKey);
    weather.setCityAndCountryCode(cityAndCountryCode);
    weather.parseData(weather.loadData());
}

void ofApp::update(){
    currentTemperature = weather.getCurrentTemperature();
    currentHumidity = weather.getCurrentHumidity();
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


### Optional: Set Units of Measurement

```c++
    // temperature in Celsius use "metric" (default)   
    // in Fahrenheit use "imperial", in Kelvin "standard"
    weather.setUnits("standard");
```


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
- [x] additional units: 
      - standard, metric, and imperial support
- [x] rain/snow
- [x] humidity
- [x] local file support
- [ ] add default icons mapping
- [ ] add more providers/integrations


Version history
------------
### Version 0.2 (2021-12-16):

- humidity
- local file support (example loads a cached json)


### Version 0.1 (2021-12-15):

- inital release










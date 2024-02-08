#ifndef SETTINGS_H
#define SETTINGS_H

// Weather Settings
#define CITY_ID "2832521"                                                       // Siegburg https://openweathermap.org/current#cityid
#define OPENWEATHERMAP_APIKEY "226c78ac4231695bcd543b1f815b2d9e"                // use your own API key :)
#define OPENWEATHERMAP_URL "http://api.openweathermap.org/data/2.5/weather?id=" // open weather api
#define TEMP_LANG "en"
#define WEATHER_UPDATE_INTERVAL 30 // must be greater than 5, measured in minutes
// NTP Settings
#define NTP_SERVER "ptbtime1.ptb.de"
#define GMT_OFFSET_SEC 3600 * +2 // New York is UTC -5 EST, -4 EDT, will be overwritten by weather data

watchySettings settings{
	.cityID = CITY_ID,
	.weatherAPIKey = OPENWEATHERMAP_APIKEY,
	.weatherURL = OPENWEATHERMAP_URL,
	.weatherLang = TEMP_LANG,
	.weatherUpdateInterval = WEATHER_UPDATE_INTERVAL,
	.ntpServer = NTP_SERVER,
	.gmtOffset = GMT_OFFSET_SEC,
	.vibrateOClock = true,
};

#endif

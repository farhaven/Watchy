#include "Watchy_7_SEG.h"

const uint8_t BATTERY_SEGMENT_WIDTH = 7;
const uint8_t BATTERY_SEGMENT_HEIGHT = 11;
const uint8_t BATTERY_SEGMENT_SPACING = 9;
const uint8_t WEATHER_ICON_WIDTH = 48;
const uint8_t WEATHER_ICON_HEIGHT = 32;

void Watchy7SEG::drawWatchFace() {
	display.fillScreen(GxEPD_WHITE);
	display.setTextColor(GxEPD_BLACK);
	drawTime();
	drawDate();
	drawSteps();
	drawWeather();
	drawBattery();
	display.drawBitmap(120, 77, WIFI_CONFIGURED ? wifi : wifioff, 26, 18, GxEPD_BLACK);
}

void Watchy7SEG::drawTime() {
	display.setFont(&DSEG7_Classic_Bold_53);
	display.setCursor(5, 53 + 5);

	if (currentTime.Hour < 10) {
		display.print("0");
	}
	display.print(currentTime.Hour);

	display.print(":");

	if (currentTime.Minute < 10) {
		display.print("0");
	}
	display.println(currentTime.Minute);
}

void Watchy7SEG::drawDate() {
	display.setFont(&Seven_Segment10pt7b);

	int16_t x1, y1;
	uint16_t w, h;

	String dayOfWeek = dayStr(currentTime.Wday);
	display.getTextBounds(dayOfWeek, 5, 85, &x1, &y1, &w, &h);
	if (currentTime.Wday == 4) {
		w = w - 5;
	}
	display.setCursor(85 - w, 85);
	display.println(dayOfWeek);

	String month = monthShortStr(currentTime.Month);
	display.getTextBounds(month, 60, 110, &x1, &y1, &w, &h);
	display.setCursor(85 - w, 110);
	display.println(month);

	display.setFont(&DSEG7_Classic_Bold_25);
	display.setCursor(5, 120);
	if (currentTime.Day < 10) {
		display.print("0");
	}
	display.println(currentTime.Day);
	display.setCursor(5, 150);
	display.println(tmYearToCalendar(currentTime.Year)); // offset from 1970, since year is stored in uint8_t
}

void Watchy7SEG::drawSteps() {
	// reset step counter at midnight
	if (currentTime.Hour == 0 && currentTime.Minute == 0) {
		sensor.resetStepCounter();
	}
	uint32_t stepCount = sensor.getCounter();
	display.drawBitmap(10, 165, steps, 19, 23, GxEPD_BLACK);
	display.setCursor(35, 190);
	display.println(stepCount);
}

void Watchy7SEG::drawBattery() {
	display.drawBitmap(154, 73, battery, 37, 21, GxEPD_BLACK);
	display.fillRect(159, 78, 27, BATTERY_SEGMENT_HEIGHT, GxEPD_WHITE); // clear battery segments
	int8_t batteryLevel = 0;
	float VBAT = getBatteryVoltage();
	if (VBAT > 4.1) {
		batteryLevel = 3;
	} else if (VBAT > 3.95 && VBAT <= 4.1) {
		batteryLevel = 2;
	} else if (VBAT > 3.80 && VBAT <= 3.95) {
		batteryLevel = 1;
	} else if (VBAT <= 3.80) {
		batteryLevel = 0;
	}

	for (int8_t batterySegments = 0; batterySegments < batteryLevel; batterySegments++) {
		display.fillRect(159 + (batterySegments * BATTERY_SEGMENT_SPACING),
		                 78,
		                 BATTERY_SEGMENT_WIDTH,
		                 BATTERY_SEGMENT_HEIGHT,
		                 GxEPD_BLACK);
	}
}

void Watchy7SEG::drawWeather() {
	weatherData currentWeather = getWeatherData();

	int8_t temperature = currentWeather.temperature;
	int16_t weatherConditionCode = currentWeather.weatherConditionCode;

	display.setFont(&DSEG7_Classic_Regular_39);
	int16_t x1, y1;
	uint16_t w, h;
	display.getTextBounds(String(temperature), 0, 0, &x1, &y1, &w, &h);
	if (159 - w - x1 > 87) {
		display.setCursor(159 - w - x1, 150);
	} else {
		display.setFont(&DSEG7_Classic_Bold_25);
		display.getTextBounds(String(temperature), 0, 0, &x1, &y1, &w, &h);
		display.setCursor(159 - w - x1, 136);
	}
	display.println(temperature);
	display.drawBitmap(165, 110, celsius, 26, 20, GxEPD_BLACK);
	const unsigned char *weatherIcon;

	// https://openweathermap.org/weather-conditions
	if (weatherConditionCode > 801) {
		// Cloudy
		weatherIcon = cloudy;
	} else if (weatherConditionCode == 801) {
		// Few Clouds
		weatherIcon = cloudsun;
	} else if (weatherConditionCode == 800) {
		// Clear
		weatherIcon = sunny;
	} else if (weatherConditionCode >= 700) {
		// Atmosphere
		weatherIcon = atmosphere;
	} else if (weatherConditionCode >= 600) {
		// Snow
		weatherIcon = snow;
	} else if (weatherConditionCode >= 500) {
		// Rain
		weatherIcon = rain;
	} else if (weatherConditionCode >= 300) {
		// Drizzle
		weatherIcon = drizzle;
	} else if (weatherConditionCode >= 200) {
		// Thunderstorm
		weatherIcon = thunderstorm;
	} else
		return;

	display.drawBitmap(145, 158, weatherIcon, WEATHER_ICON_WIDTH, WEATHER_ICON_HEIGHT, GxEPD_BLACK);
}

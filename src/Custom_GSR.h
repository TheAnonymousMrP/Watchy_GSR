#ifndef CUSTOM_GSR_H
#define CUSTOM_GSR_H

#ifndef WATCH_GSR_H
#include "Watchy_GSR.h"
#endif

namespace Weather {
    static uint8_t intervalCounter = 30;
    enum class tempScale {
        KELVIN     = 0,
        CELSIUS    = 1,
        FAHRENHEIT = 2,
    };
    const String scaleRequestStrings[3] = {"standard", "metric", "imperial"};
    const int    scaleDisplayChars[3]   = {U'°', U'℃', U'℉'};
    enum class conditionCategory {
        LOCAL        = 0,
        CLEAR        = 1,
        THUNDERSTORM = 2,
        DRIZZLE      = 3,
        RAIN         = 5,
        SNOW         = 6,
        ATMOSPHERE   = 7,
        CLOUDS       = 8
    };
    const int conditionDisplayChars[9] = {U'?',    U'☀', U'⛈',    U'🌦',
                                          U'🌧', U'❄', U'🌫', U'☁'};

    // Weather Settings - uses https://openweathermap.org/
    const String    cityID = "2634739";
    const String    APIKey = "13770b1d27e38e286fb8ce6bed5c1f02";
    const String    URL = "http://api.openweathermap.org/data/2.5/weather?id=";
    const tempScale requestScale   = tempScale::CELSIUS;
    const String    lang           = "en";
    const uint8_t   updateInterval = 30;

    struct Data {
        int8_t    temperature   = 0;
        int16_t   conditionCode = 0;
        tempScale scale         = scale;
        // String  weatherDescription = "Local";
        String display = "";
    };
} // namespace Weather

static const String NTP_SERVER{"uk.pool.ntp.org"};

class CustomGSR : public WatchyGSR {
  public:
    void InsertAddWatchStyles();
    void InsertInitWatchStyle(uint8_t StyleID);
    void InsertDrawWatchStyle(uint8_t StyleID);

    String InsertNTPServer();
    void   InsertOnMinute();
    void   InsertOnWiFi();
    void   InsertWiFiEnding();
    // void   drawTime() { WatchyGSR::drawTime(); };
    void drawYear();
    void drawWeather();

  private:
    uint8_t CustomStyle;
    uint8_t CustomStyle2;
    uint8_t CustomStyle3;

    bool          weatherRequest = false;
    Weather::Data currentWeather;

    void weatherCounter();

    Weather::Data getLocalWeather(Weather::tempScale scale);

    Weather::Data getOnlineWeather(String cityID, Weather::tempScale scale,
                                   String lang, String url, String apiKey);

    String MakeFormattedHour(uint8_t Hour);

    // Copies of private base methods
    void drawData(String dData, byte Left, byte Bottom, WatchyGSR::DesOps Style,
                  byte Gutter, bool isTime = false, bool PM = false);
    void setFontFor(String O, const GFXfont * Normal, const GFXfont * Small,
                    const GFXfont * Smaller, byte Gutter = 5);
};
#endif
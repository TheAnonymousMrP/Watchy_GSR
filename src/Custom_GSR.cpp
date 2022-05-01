#ifndef CUSTOM_GSR_H
#include "Custom_GSR.h"
#endif

// Copy from Watchy_GSR.cpp
struct Designing final {
    struct MenuPOS {
        byte            Gutter;      // 3
        byte            Top;         // MenuTop 72
        byte            Header;      // HeaderY 97
        byte            Data;        // DataY 138
        const GFXfont * Font;        // Menu Font.
        const GFXfont * FontSmall;   // Menu Font.
        const GFXfont * FontSmaller; // Menu Font.
    } Menu;
    struct FacePOS {
        const unsigned char * Bitmap;          // Null
        const unsigned char * SleepBitmap;     // Null
        byte                  Gutter;          // 4
        byte                  Time;            // TimeY 56
        byte                  TimeHeight;      // 45
        uint16_t              TimeColor;       // Font Color.
        const GFXfont *       TimeFont;        // Font.
        WatchyGSR::DesOps     TimeStyle;       // dCENTER
        byte                  TimeLeft;        // Only for dSTATIC
        byte                  Day;             // DayY 101
        byte                  DayGutter;       // 4
        uint16_t              DayColor;        // Font Color.
        const GFXfont *       DayFont;         // Font.
        const GFXfont *       DayFontSmall;    // Font.
        const GFXfont *       DayFontSmaller;  // Font.
        WatchyGSR::DesOps     DayStyle;        // dCENTER
        byte                  DayLeft;         // Only for dSTATIC
        byte                  Date;            // DateY 143
        byte                  DateGutter;      // 4
        uint16_t              DateColor;       // Font Color.
        const GFXfont *       DateFont;        // Font.
        const GFXfont *       DateFontSmall;   // Font.
        const GFXfont *       DateFontSmaller; // Font.
        WatchyGSR::DesOps     DateStyle;       // dCENTER
        byte                  DateLeft;        // Only for dSTATIC
        byte                  Year;            // YearY 186
        uint16_t              YearColor;       // Font Color.
        const GFXfont *       YearFont;        // Font.
        WatchyGSR::DesOps     YearStyle;       // dCENTER
        byte                  YearLeft;        // Only for dSTATIC
    } Face;
    struct StatusPOS {
        byte WIFIx; // NTPX 5
        byte WIFIy; // NTPY 193
        byte BATTx; // 155
        byte BATTy; // 178
    } Status;
};

struct CustomDesigning {
    struct MenuPOS : Designing::MenuPOS {
    } Menu;
    struct FacePOS : Designing::FacePOS {
        byte              Weather;            // DateY 143
        uint16_t          WeatherColor;       // Font Color.
        const GFXfont *   WeatherFont;        // Font.
        const GFXfont *   WeatherFontSmall;   // Font.
        const GFXfont *   WeatherFontSmaller; // Font.
        WatchyGSR::DesOps WeatherStyle;       // dCENTER
        byte              WeatherLeft;        // Only for dSTATIC
    } Face;
    struct StatusPOS : Designing::StatusPOS {
    } Status;
} CustomDesign;

// Copy from Watchy_GSR.cpp
void CustomGSR::drawData(String dData, byte Left, byte Bottom,
                         WatchyGSR::DesOps Style, byte Gutter, bool isTime,
                         bool PM) {
    uint16_t w, Width, Height, Ind;
    int16_t  X, Y;

    display.getTextBounds(dData, Left, Bottom, &X, &Y, &Width, &Height);

    Bottom = constrain(Bottom, Gutter, 200 - Gutter);
    switch (Style) {
    case WatchyGSR::dLEFT: Left = Gutter; break;
    case WatchyGSR::dRIGHT:
        Left = constrain(200 - (Gutter + Width), Gutter, 200 - Gutter);
        break;
    case WatchyGSR::dSTATIC:
        Left = constrain(Left, Gutter, 200 - Gutter);
        break;
    case WatchyGSR::dCENTER:
        Left =
            constrain(4 + ((196 - (Gutter + Width)) / 2), Gutter, 200 - Gutter);
        break;
    };
    display.setCursor(Left, Bottom);
    display.print(dData);

    if (isTime && PM) {
        if (Style == WatchyGSR::dRIGHT)
            Left = constrain(Left - 12, Gutter, 200 - Gutter);
        else
            Left = constrain(Left + Width + 6, Gutter, 190);
        display.drawBitmap(Left, Bottom - CustomDesign.Face.TimeHeight,
                           PMIndicator, 6, 6, ForeColor());
    }
}

void CustomGSR::setFontFor(String O, const GFXfont * Normal,
                           const GFXfont * Small, const GFXfont * Smaller,
                           byte Gutter) {
    int16_t  x1, y1;
    uint16_t w, h;
    byte     wi = (200 - (2 * Gutter));
    display.setFont(Normal);
    display.getTextBounds(O, 0, 0, &x1, &y1, &w, &h);
    if (w > wi) {
        display.setFont(Small);
        display.getTextBounds(O, 0, 0, &x1, &y1, &w, &h);
    }
    if (w > wi) {
        display.setFont(Smaller);
        display.getTextBounds(O, 0, 0, &x1, &y1, &w, &h);
    }
}



void CustomGSR::InsertInitWatchStyle(uint8_t StyleID) {
    //if (StyleID == CustomStyle || StyleID == CustomStyle2) {
        CustomDesign.Menu.Top                = 72;
        CustomDesign.Menu.Header             = 25;
        CustomDesign.Menu.Data               = 66;
        CustomDesign.Menu.Gutter             = 3;
        CustomDesign.Menu.Font               = &aAntiCorona12pt7b;
        CustomDesign.Menu.FontSmall          = &aAntiCorona11pt7b;
        CustomDesign.Menu.FontSmaller        = &aAntiCorona10pt7b;
        CustomDesign.Face.Bitmap             = nullptr;
        CustomDesign.Face.SleepBitmap        = nullptr;
        CustomDesign.Face.Gutter             = 4;
        CustomDesign.Face.Time               = 56;
        CustomDesign.Face.TimeHeight         = 45;
        CustomDesign.Face.TimeColor          = ForeColor();
        CustomDesign.Face.TimeFont           = &aAntiCorona36pt7b;
        CustomDesign.Face.TimeLeft           = 0;
        CustomDesign.Face.TimeStyle          = WatchyGSR::dCENTER;
        CustomDesign.Face.Day                = 101;
        CustomDesign.Face.DayColor           = ForeColor();
        CustomDesign.Face.DayFont            = &aAntiCorona16pt7b;
        CustomDesign.Face.DayFontSmall       = &aAntiCorona15pt7b;
        CustomDesign.Face.DayFontSmaller     = &aAntiCorona14pt7b;
        CustomDesign.Face.DayLeft            = 0;
        CustomDesign.Face.DayStyle           = WatchyGSR::dCENTER;
        CustomDesign.Face.Date               = 143;
        CustomDesign.Face.DateColor          = ForeColor();
        CustomDesign.Face.DateFont           = &aAntiCorona15pt7b;
        CustomDesign.Face.DateFontSmall      = &aAntiCorona14pt7b;
        CustomDesign.Face.DateFontSmaller    = &aAntiCorona13pt7b;
        CustomDesign.Face.DateLeft           = 0;
        CustomDesign.Face.DateStyle          = WatchyGSR::dCENTER;
        CustomDesign.Face.Year               = 186;
        CustomDesign.Face.YearColor          = ForeColor();
        CustomDesign.Face.YearFont           = &aAntiCorona16pt7b;
        CustomDesign.Face.YearLeft           = 0;
        CustomDesign.Face.YearStyle          = WatchyGSR::dCENTER;
        CustomDesign.Status.WIFIx            = 5;
        CustomDesign.Status.WIFIy            = 193;
        CustomDesign.Status.BATTx            = 155;
        CustomDesign.Status.BATTy            = 178;

        CustomDesign.Face.Weather            = 186;
        CustomDesign.Face.WeatherColor       = ForeColor();
        CustomDesign.Face.WeatherFont        = &aAntiCorona16pt7b;
        CustomDesign.Face.WeatherLeft        = 0;
        CustomDesign.Face.WeatherStyle       = WatchyGSR::dRIGHT;
    //}
}

void CustomGSR::InsertAddWatchStyles() {
    CustomStyle = AddWatchStyle("Custom");
    CustomStyle2 = AddWatchStyle("Custom 2");
    CustomStyle3 = AddWatchStyle("Custom 3");
    
}
void CustomGSR::InsertDrawWatchStyle(uint8_t StyleID) {
        Serial.println(StyleID);
        Serial.println(CustomStyle);
        Serial.println(CustomStyle2);
        Serial.println(CustomStyle3);
    if (StyleID == CustomStyle2) {
        drawTime();
        drawDay();
        drawYear();
        // drawDate();
    }
    else {
        drawTime();
        drawDay();
        //drawYear();
        //drawDate();
    }
}

String CustomGSR::InsertNTPServer() { return NTP_SERVER; }

void CustomGSR::InsertOnMinute() { 
    //weatherCounter(); 
    };

void CustomGSR::InsertOnWiFi() {
    using namespace Weather;
    if (weatherRequest) {
        currentWeather =
            getOnlineWeather(cityID, requestScale, lang, URL, APIKey);
        endWiFi();
    }
}

void CustomGSR::InsertWiFiEnding() { weatherRequest = false; }

void CustomGSR::weatherCounter() {
    using namespace Weather;
    if (intervalCounter < 0) {
        intervalCounter = updateInterval; //-1 on first run
    }

    if (intervalCounter >= updateInterval) {
        intervalCounter = 0;
        if (currentWiFi() == WL_CONNECTED) {
            weatherRequest = true;
            AskForWiFi();
        } else {
            currentWeather = getLocalWeather(Weather::requestScale);
        }

    } else {
        intervalCounter++;
    }
}

Weather::Data CustomGSR::getLocalWeather(Weather::tempScale scale) {
    using namespace Weather;
    Data request;
    switch (scale) {
    case tempScale::KELVIN:
        request.temperature = SBMA.readTemperature() + 273.15;
        break;
    case tempScale::CELSIUS:
        request.temperature = SBMA.readTemperature();
        break;
    case tempScale::FAHRENHEIT: request.temperature = SBMA.readTemperatureF();
    }
    request.scale = scale;

    auto scaleChar =
        Weather::scaleDisplayChars[static_cast<int>(currentWeather.scale)];
    auto conditionChar = Weather::conditionDisplayChars[0];
    request.display =
        String(currentWeather.temperature, 0) + scaleChar + " " + conditionChar;
    return request;
};

Weather::Data CustomGSR::getOnlineWeather(String             cityID,
                                          Weather::tempScale scale, String lang,
                                          String url, String apiKey) {
    using namespace Weather;
    Data request;
    request.scale == scale;
    HTTPClient http;
    http.setConnectTimeout(3000); // 3 second max timeout
    String weatherQueryURL = url + cityID + String("&units=") +
                             scaleRequestStrings[static_cast<int>(scale)] +
                             String("&lang=") + lang + String("&appid=") +
                             apiKey;
    http.begin(weatherQueryURL.c_str());
    int httpResponseCode = http.GET();
    if (httpResponseCode == 200) {
        String  payload        = http.getString();
        JSONVar responseObject = JSON.parse(payload);
        request.temperature    = int(responseObject["main"]["temp"]);
        request.conditionCode  = int(responseObject["weather"][0]["id"]);
        // request.weatherDescription = responseObject["weather"][0]["main"];

        conditionCategory conCat;
        switch (request.conditionCode) {
            using c = conditionCategory;
        case 200 ... 202:
        case 210 ... 212:
        case 221:
        case 230 ... 232: conCat = c::THUNDERSTORM; break;
        case 300 ... 302:
        case 310 ... 314:
        case 321: conCat = c::DRIZZLE; break;
        case 500 ... 504:
        case 511:
        case 520 ... 522:
        case 531: conCat = c::RAIN; break;
        case 600 ... 602:
        case 611 ... 616:
        case 620 ... 622: conCat = c::SNOW; break;
        case 700:
        case 711:
        case 721:
        case 731:
        case 741:
        case 751:
        case 761:
        case 762:
        case 771:
        case 781: conCat = c::ATMOSPHERE; break;
        case 800: conCat = c::CLEAR; break;
        case 801 ... 804: conCat = c::CLOUDS; break;
        default: conCat = c::LOCAL; break;
        }

        char scaleChar =
            scaleDisplayChars[static_cast<int>(currentWeather.scale)];
        auto conditionChar =
            Weather::conditionDisplayChars[static_cast<int>(conCat)];
        request.display =
            String(request.temperature, 0) + scaleChar + " " + conditionChar;
    } else {
        // http error
        request = getLocalWeather(scale);
    }
    http.end();

    return request;
}

void CustomGSR::drawYear() {
    // String O = "butts";
    // display.setFont(CustomDesign.Face.YearFont);
    // display.setTextColor(CustomDesign.Face.YearColor);
    // drawData(O, CustomDesign.Face.YearLeft, CustomDesign.Face.Year,
    //          CustomDesign.Face.YearStyle, CustomDesign.Face.Gutter);
    WatchyGSR::drawYear();
}

void CustomGSR::drawWeather() {
    String O = currentWeather.display;
    setFontFor(O, CustomDesign.Face.WeatherFont, CustomDesign.Face.WeatherFontSmall,
               CustomDesign.Face.WeatherFontSmaller, CustomDesign.Face.Gutter);
    display.setTextColor(CustomDesign.Face.WeatherColor);
    drawData(O, CustomDesign.Face.WeatherLeft, CustomDesign.Face.Weather,
             CustomDesign.Face.WeatherStyle, CustomDesign.Face.Gutter);
}

String CustomGSR::MakeFormattedHour(uint8_t Hour) {
    return (Hour < 10 ? "0" : "") + MakeHour(Hour);
}

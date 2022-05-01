#ifndef CUSTOM_GSR_H
#include "Custom_GSR.h"
#endif
#ifndef WATCHY_GSR_H
#include "Watchy_GSR.h"
#endif

#define LOCALTEMP true

CustomGSR watchy;

void setup(){
  Serial.begin(115200);
  Serial.println("Am I working?");
  watchy.init();
}

void loop(){}

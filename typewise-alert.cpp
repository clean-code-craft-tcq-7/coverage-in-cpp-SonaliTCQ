#include "typewise-alert.h"
#include <stdio.h>
#include <iostream>
#include <map>

std::map<CoolingType, Limit> CoolingLim;

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
	if (value < lowerLimit) {
		return TOO_LOW;
	}
	if (value > upperLimit) {
		return TOO_HIGH;
	}
	return NORMAL;
}


BreachType classifyTemperatureBreach(
		CoolingType coolingType, double temperatureInC) {
	int lowerLimit = 0;
	int upperLimit = 0;

	CoolingLim[PASSIVE_COOLING] = { PAS_LOW_LIM, PAS_UPP_LIM };
	CoolingLim[HI_ACTIVE_COOLING] = { HI_LOW_LIM, HI_UPP_LIM };
	CoolingLim[MED_ACTIVE_COOLING] = { MED_LOW_LIM, MED_UPP_LIM };

	lowerLimit = CoolingLim[coolingType].lowerlimit;
	upperLimit = CoolingLim[coolingType].upperlimit;
  
  
  return inferBreach(temperatureInC, lowerLimit, upperLimit);
}


void checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreach(
    batteryChar.coolingType, temperatureInC
  );

  switch(alertTarget) {
    case TO_CONTROLLER:
      sendToController(breachType);
      break;
    case TO_EMAIL:
      sendToEmail(breachType);
      break;
  }
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  switch(breachType) {
    case TOO_LOW:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too low\n");
      break;
    case TOO_HIGH:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too high\n");
      break;
    case NORMAL:
      break;
  }
}

#include "typewise-alert.h"
#include <stdio.h>
#include <iostream>
#include <map>
#include<sstream>
#include <string>


using namespace std;

std::map<CoolingType, mapLimit> CoolingLim;
std::map<BreachType, std::string> SendBreach;

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
	
	int *email_controller;
  	BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
	
  	switch(alertTarget) {
    case TO_CONTROLLER:
      sendToCont_interface_check();			// for test code
	sendToController(breachType);
      break;
    case TO_EMAIL:
      *email_controller = sendToMail_interface_check();		// for test code
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
	std::cout << "To: %s\n" << *recepient << '\n';
	
	SendBreach[TOO_LOW] = {"Hi, the temperature is too low\n"};
	SendBreach[TOO_HIGH] = {"Hi, the temperature is too high\n"};
	SendBreach[NORMAL] = {};

	std::cout << SendBreach[breachType].c_str();
	
	
}

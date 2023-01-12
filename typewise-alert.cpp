#include "typewise-alert.h"
#include <stdio.h>
#include <iostream>
#include <map>
#include<sstream>

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

string sendToController(BreachType breachType) {
	string alertmsg;
	std::ostringstream msg;
	const unsigned short header = 0xfeed;
	msg << "%x : %x\n", header, breachType;
	string alertmsg = msg.str();
	cout << alertmsg << endl;
	return alertmsg;
	
}

void sendToEmail(BreachType breachType, char *) {
	
	char buffOut[200];
	
  	
	const char* recepient = "a.b@c.com";
	std::cout << "To: %s\n" << *recepient << '\n';
	
	SendBreach[TOO_LOW] = {"Hi, the temperature is too low\n"};
	SendBreach[TOO_HIGH] = {"Hi, the temperature is too high\n"};
	SendBreach[NORMAL] = {};

	std::cout << SendBreach[breachType].c_str();
	
	
	
}

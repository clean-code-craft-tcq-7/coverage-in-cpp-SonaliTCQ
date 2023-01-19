#pragma once
#include<map>
#include<iostream>

using namespace std;

typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING
} CoolingType;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH
} BreachType;

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL
} AlertTarget;

typedef struct {
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;

typedef struct{
int lowerlimit;
int upperlimit;
} mapLimit;

#define PAS_LOW_LIM 0
#define PAS_UPP_LIM 35
#define HI_LOW_LIM 0
#define HI_UPP_LIM 45
#define MED_LOW_LIM 0
#define MED_UPP_LIM 40

void checkAndAlert(
  AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC, string msg_controller);

void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);

int sendToCont_interface_check();
int sendToMail_interface_check();

extern int *msg_controller;
extern int *email_controller;

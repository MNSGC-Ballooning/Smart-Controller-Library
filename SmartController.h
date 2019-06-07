#ifndef SMARTCONTROLLER_H_INCLUDED
#define SMARTCONTROLLER_H_INCLUDED

#include <Arduino.h>


class SmartController
{
public:
/***********Variables********/
    char response;
    char Data;
    String DataMSG;
    unsigned long CutTimer;
    unsigned long DataTimer;
    bool newTempChar;
    int CutStatuses[5]={0,0,0,0,0};
    
/***********Character Arrays************/
    const char CutCommands[2]={'A','B'};  //SEND, cut command. Can add more
    const char CutConfirms[2]={'Z','X'};  //RECIEVE, indicates confirmed cut
    const char CutAcknowledged[2]={'a','b'}; //SEND, to stop cut confirm spam in smarts 
    const char TempRequests[2]={'O','P'}; //SEND, to request temperatures
    const char TempStart[2]={'T','C'};    //RECIEVE, indicates start of temp send
    const char TempConfirms[2]={'Y','V'}; //RECIEVE, indicates end of temp send
/***************************************/

/********Functions********/
    String Response(); //Call in loop
    String GetData(char id);  //Call from Response to get data string
    void RequestTemp(int SmartUnit); //Call in main
    void Cut(int SmartUnit,bool Condition); //Call with Condition=true to cut
    //constructor
    SmartController(int SmartNumber, HardwareSerial &print, float TimeAllowed);
    //ONLY NEED TO USE Constructor, Response(), RequestTemp(), and Cut() in main
private:
    int SmartCount; //Number of attached smarts
    HardwareSerial* Xbee; //Xbee serial
    float TimeAllotted;


};












#endif // SMARTCONTROLLER_H_INCLUDED


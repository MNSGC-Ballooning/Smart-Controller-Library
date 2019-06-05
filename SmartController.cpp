#include "SmartController.h"
#include <Arduino.h>





//Constructor
SmartController::SmartController(int SmartNumber, HardwareSerial &print){
  
//For setting up Xbee
Xbee = &print;
/*******Initializing variables********/
newTempChar=true;
CutTimer=0;
DataTimer=0;
SmartCount=SmartNumber; //Number of smart units attached



/************************************/


}






/*************Response Function***************/
String SmartController::Response(){

if(Xbee->available()>0){
    response=Xbee->read();

for (int i=0;i<SmartCount;i++){

   //Temp sending check
   if (response==TempStart[i]){

    DataTimer=millis();
    DataMSG=String(CutCommands[i])+" Temp: ";
    response='0';
    return GetData(TempConfirms[i]);
   }
}
for (int i=0;i<SmartCount;i++){
   //Cut confirmation check
    if (response==CutConfirms[i] && CutStatuses[i]==0){
     
     DataMSG=String(CutCommands[i])+" Cut";
     CutStatuses[i]=1;
     response='0';
     
     //MAKE BETTER, is just sending to stop cut confirm spam
     Xbee->print(CutAcknowledged[i]);
     Xbee->print(CutAcknowledged[i]);
     Xbee->print(CutAcknowledged[i]);
     Xbee->print(CutAcknowledged[i]);
     
     return DataMSG;
   }
}
   }

response='0';
return ""; //If dont have to log, will return ""
}

/*************Request Temp Function***********/
void SmartController::RequestTemp(int SmartUnit){
Xbee->print(TempRequests[SmartUnit-1]);
}

/*********Get Data Function*************/
String SmartController::GetData(char id) {  //in unlikely event that temp send takes more than 2 seconds, break

while(true && millis()-DataTimer<=500){

    if(Xbee->available()>0){
    Data=Xbee->read();
    }
    if (Data==id){
        DataTimer=millis();
        Data='/';
        newTempChar=true;
        return DataMSG;  //ADD GPS TIMESTAMP

    }
  if(Data=='/'){
    newTempChar=true;
    }
  else if(newTempChar && Data!='/')
  {
    DataMSG=DataMSG+String(Data);
    newTempChar=false;
  }
}
return "Took too long"; //if longer than 2 seconds
}

/**********Cut Command*****************/
void SmartController::Cut(int SmartUnit,bool Condition){ ///Call repeatedly until cut confirmed
if (Condition && CutStatuses[SmartUnit-1]==0)
{
  if (millis()-CutTimer>200){
  Xbee->print(CutCommands[SmartUnit-1]);
  CutTimer=millis();
}
}
}

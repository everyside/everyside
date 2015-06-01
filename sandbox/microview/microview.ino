#include <MicroView.h>          // include MicroView library
#include <SoftwareSerial.h>

#define rxPin 3
#define txPin 2

//MicroViewWidget *widget;        // create widget pointer
MicroViewWidget *widget2;       // create widget pointer

SoftwareSerial xbee(rxPin, txPin); // RX, TX

String PREFIX_RATE = "r:";
String PREFIX_SENSITIVITY = "s:";
int sensitivity = 5; // send a sensor reading only if it has changed by >= the sensitivity (lower is more sensitive)
unsigned long minTimeThresholdMillis = 1000 * 0; //send a sensor reading no more often than every 5 seconds

int sensorPin = A1;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
int lastSentSensorValue = 0;
unsigned long lastSentTime = 0;
String inputString = "";

void setup()
{
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  
  digitalWrite(sensorPin, HIGH);      // Internal Pull-up
  pinMode(sensorPin, INPUT);          // make pin as INPUT
  uView.begin();                      // start MicroView
  uView.clear(PAGE);                  // clear page
  //widget = new MicroViewSlider(5, 0, 0, 1024);    // make widget as Slider
  widget2 = new MicroViewSlider(0, 20, 0, 1024, WIDGETSTYLE1);
  drawLables();
  uView.display();                    // display the content in the screen buffer
  
  xbee.begin(9600);
  xbee.println("\n---Connected MicroView via XBee network.---\n");
}

void loop()
{
 
  bool received = false;
  String msg;
  if(xbee.available() > 0){
    while( xbee.available()>0){
      char inChar = xbee.read();
      if(inChar == '\n' || inChar == '\r'){
        
        if(inputString.length() > 0){
          received = true;
          if(inputString.startsWith(PREFIX_SENSITIVITY)){
            
            inputString.remove(0,PREFIX_SENSITIVITY.length());
            sensitivity = inputString.toInt();
            
            msg = "\n--->Sensitivity set to ";
            msg.concat(sensitivity);
          }else if(inputString.startsWith(PREFIX_RATE)){
            
            inputString.remove(0,PREFIX_RATE.length());
            minTimeThresholdMillis = inputString.toInt();
            
            msg = "\n--->Rate set to ";
            msg.concat(minTimeThresholdMillis);
          }else{
            msg = "\n--->Unknown command : ";
            msg.concat(inputString);
          }
          inputString = "";
        }
      }else if(inputString.length() < 20){
        inputString.concat(inChar);
      }else{
        inputString = "";
      }
    }
  }
  if(received){
    xbee.println(msg);
  }
  sensorValue = analogRead(sensorPin);    // read sensorPin
  sendIfWorthIt();
  //widget->setValue(sensorValue);          // set value of sensorPin to widget
  
  
  uView.display();                        // display the content in the screen buffer
}

void drawLables() {
  uView.clear(PAGE);
  uView.setCursor(0,0);
  //uView.print(" Everyside");
}

void sendIfWorthIt() {
  int delta = abs(sensorValue - lastSentSensorValue);
  if(delta >= sensitivity){
    widget2->setValue(sensorValue);         // set value of sensorPin to widget 
    
    unsigned long now = millis();
    if(now - minTimeThresholdMillis > lastSentTime){
        lastSentSensorValue = sensorValue;
        lastSentTime = now;
        xbee.println(sensorValue);
    }
  }	
}


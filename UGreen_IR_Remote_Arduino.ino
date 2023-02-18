
#include <Arduino.h>
#define DISABLE_CODE_FOR_RECEIVER // Saves 450 bytes program memory and 269 bytes RAM if receiving functions are not used.
//#define SEND_PWM_BY_TIMER         // Disable carrier PWM generation in software and use (restricted) hardware PWM.
//#define USE_NO_SEND_PWM           // Use no carrier PWM, just simulate an active low receiver signal. Overrides SEND_PWM_BY_TIMER definition

#include "PinDefinitionsAndMore.h" // Define macros for input and output pin etc.
#include <IRremote.hpp>
#include <SPI.h>
#include <Ethernet.h>

#define DEBUG 1

byte mac[] = { 0x01, 0xAD, 0xBE, 0xEF, 0xFE, 0xEE }; //physical mac address
byte ip[] = { 192, 168, 3, 237 }; // IP address in LAN – need to change according to your Network address
byte gateway[] = { 192, 168, 3, 1 }; // internet access via router
byte subnet[] = { 255, 255, 255, 0 }; //subnet mask
EthernetServer server(80); //server port

String readString;

void setup(){
    pinMode(LED_BUILTIN, OUTPUT);
    IrSender.begin(DISABLE_LED_FEEDBACK); // Start with IR_SEND_PIN as send pin and disable feedback LED at default feedback LED pin

    if(DEBUG) 
    {
      Serial.begin(115200);
    }

   
    //start Ethernet
    Ethernet.begin(mac, ip, gateway, subnet);
    server.begin();
}

uint8_t sCommand = 0x47;
//uint8_t sCommands[] = {};
uint8_t sRepeats = 0;

void loop(){
    // Create a client connection
    EthernetClient client = server.available();
    if (client) {
        while (client.connected()) {
            if (client.available()) {
                
                char c = client.read();
                
                //read char by char HTTP request
                if (readString.length() < 30) {

                    //store characters to string
                    readString += c;
                }

                //if HTTP request has ended– 0x0D is Carriage Return \n ASCII
                if (c == 0x0D) {
                    // control arduino pin
                    if(readString.indexOf("/run/") > -1) //checks for /run/(index) url
                    {
                        if(DEBUG)
                        {
                        Serial.print(readString);
                        Serial.print("\n"); 
                        Serial.print(readString.length());
                        Serial.print("\n"); 
                        Serial.print(readString.substring(9,readString.length()-10));
                        Serial.print("\n");

                        }

                        String runID = readString.substring(9,readString.length()-10);
                        int runIDint = 0;

                        

                        
                        if(runID.endsWith("/")){
                          runIDint = runID.substring(0, runID.length()-1).toInt();
                          if(DEBUG) Serial.print("With /");
                          if(DEBUG) Serial.print("\n"); 
                          }
                          else
                          {
                            runIDint = runID.toInt();
                            if(DEBUG) Serial.print("Without /");
                            if(DEBUG) Serial.print("\n"); 
                            }

                        if(DEBUG)
                        {
                        Serial.print("ID int: ");
                        Serial.print(runIDint);
                        Serial.print("\n"); 
                        }

                        //run irSend
                        mySendIR(sCommand);

                        client.println("HTTP/1.1 200 OK"); //send 200 back
                        client.println("Content-Type: text/html");
                        client.println();
    
                        client.stop();
                    }
                    else
                    {
                        client.println("HTTP/1.1 403 Forbidden"); //send erreur request
                        client.println("Content-Type: text/html");
                        client.println();
    
                        client.stop();
                      }

                    //clearing string for next read
                    readString="";

                }
            }
        }
    }
}

void mySendIR(uint8_t _cmd){
      /*
     * Print current send values
     */
    Serial.println();
    Serial.print(F("Send now: address=0x00, command=0x"));
    Serial.print(sCommand, HEX);
    Serial.print(F(", repeats="));
    Serial.print(sRepeats);
    Serial.println();

    Serial.println(F("Send standard NEC with 8 bit address"));
    Serial.flush();

    // Receiver output for the first loop must be: Protocol=NEC Address=0x102 Command=0x34 Raw-Data=0xCB340102 (32 bits)
    IrSender.sendNEC(0x00, sCommand, sRepeats);

    sRepeats++;
    
    // clip repeats at 3
    if (sRepeats > 3) {
        sRepeats = 3;
    }
  }

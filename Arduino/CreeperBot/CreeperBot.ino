// Includes
#include <WiServer.h>
#include <string.h>
#include <Servo.h> 

// Wireless configuration parameters
unsigned char local_ip[]    = { 192,168,0,10 };      // IP address of WiShield
unsigned char gateway_ip[]  = { 192.168,0,1 };       // router or gateway IP address
unsigned char subnet_mask[] = { 255,255,255,0 };     // subnet mask for the local network
char ssid[]                 = {"Robot"};             // max 32 bytes
unsigned char security_type = 0;                     // 0 - open; 1 - WEP; 2 - WPA; 3 - WPA2

// WPA/WPA2 passphrase (UNUSED)
const char PROGMEM security_passphrase[]  = { "12345678"};   // max 64 characters

// WEP 128-bit keys (UNUSED)
//const unsigned char PROGMEM wep_keys[] = { 
//    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d,   // Key 0
//    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   // Key 1
//    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   // Key 2
//    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00    // Key 3
//};
const unsigned char PROGMEM wep_keys[] = {};

// Wireless mode
#define WIRELESS_MODE_INFRA   1
#define WIRELESS_MODE_ADHOC   2
unsigned char wireless_mode = WIRELESS_MODE_INFRA;

// Required for the WiShiled library
unsigned char ssid_len;
unsigned char security_passphrase_len;

//-- Constants for the right motor
const int MOTOR_RIGHT      = 5;
const int MOTOR_RIGHT_FW   = 180;    //-- Move the right motor forward
const int MOTOR_RIGHT_BW   = 0;  //-- Move the right motor backward
const int MOTOR_RIGHT_STOP = 90;   //-- Stop the right motor

//-- Constants for the left motor
const int MOTOR_LEFT      = 6;
const int MOTOR_LEFT_FW   = 0;  //-- Move the left motor forward
const int MOTOR_LEFT_BW   = 180;    //-- Move the left motor backward
const int MOTOR_LEFT_STOP = 90;   //-- Stop the left motor

bool strobe = 0;
bool strobe_state = 0;
unsigned char previous_movement=5;
 
//-- The two motors are servos that can turn freely 
Servo rm;  //-- Right motor
Servo lm;  //-- Left motor

void setup() 
{
	WiServer.init(sendPage);
	rm.attach(MOTOR_RIGHT);
	lm.attach(MOTOR_LEFT);
    pinMode(4, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
}

void loop()
{
      
	// Run WiServer
    if(strobe)
    {
        if(strobe_state)
        {
            digitalWrite(4, LOW);
            strobe_state=0;
        }
        else
        {
            digitalWrite(4, HIGH);
            strobe_state=1;
        }
    }
    
    for(unsigned char i=0; i<10 ; i++)
    {
        WiServer.server_task();
        delay(5);
    }
        
	
	
}

void robot_action(unsigned char movement)
{
    //movement -> 1 = Front
    //            2 = Back
    //            3 = Right
    //            4 = Left
    //            5 = Stop
    //            6 = Light on
    //            7 = Light off
    //            8 = Light Strobe
    //            9 = Eyes on
    //            10 = Eyes off
    
    switch(movement)
    {
        case 1:
            rm.write(MOTOR_RIGHT_FW);
        	lm.write(MOTOR_LEFT_FW);
            break;
        case 2:
            rm.write(MOTOR_RIGHT_BW);
        	lm.write(MOTOR_LEFT_BW);
            break;
        case 3:
            lm.write(MOTOR_LEFT_FW);
        	rm.write(MOTOR_RIGHT_BW);
            break;
        case 4:
            lm.write(MOTOR_LEFT_BW);
        	rm.write(MOTOR_RIGHT_FW);
            break;
        case 5:
            rm.write(MOTOR_RIGHT_STOP);
        	lm.write(MOTOR_LEFT_STOP);
            break;
        case 6:
            digitalWrite(4, HIGH);
            break;
        case 7:
            digitalWrite(4, LOW);
            strobe = 0;
            break;
        case 8:
            strobe = 1;
            break;
        case 9:
          digitalWrite(7, HIGH);
          digitalWrite(8, HIGH);
          break;
       case 10:
          digitalWrite(7, LOW);
          digitalWrite(8, LOW);
          break;
    }
}




void OurPage(void)
{
    WiServer.print("<html><head><title>Robot</title></head>");

    WiServer.print("<body><center>Control !<center>\n<center>");
    
    WiServer.print("<a href=?Front>Front</a></br>");
    WiServer.print("<a href=?Back>Back</a></br>");
    WiServer.print("<a href=?Right>Right</a></br>");
    WiServer.print("<a href=?Left>Left</a></br>");
    WiServer.print("<a href=?Stop>Stop</a></br>");
    WiServer.print("<a href=?LightOn>Light On</a></br>");
    WiServer.print("<a href=?LightOff>Light Off</a></br>");
    WiServer.print("<a href=?EyesOn>Eyes On</a></br>");
    WiServer.print("<a href=?EyesOff>Eyes Off</a></br>");
    WiServer.print("<a href=?LightStrobe>Light Strobe</a></br>");

    WiServer.print("</html> ");    
}


// This is our page serving function that generates web pages
boolean sendPage(char* URL_Received) 
{
    String URL_String = URL_Received;      // Just convert the chat* receivedto a String object
    
    if (URL_String == "/?Front")
    {
        robot_action(1);
        previous_movement=1;
    }
    else if(URL_String == "/?Back")
    {
        robot_action(2);
        previous_movement=2;
    }
    else if(URL_String == "/?Right")
    {
        robot_action(3);
        delay(100);
        robot_action(previous_movement);
    }
    else if(URL_String == "/?Left")
    {
        robot_action(4);
         delay(100);
        robot_action(previous_movement);
    } 
    else if(URL_String == "/?Stop")
    {
        robot_action(5);
        previous_movement=5;
    }
    else if(URL_String == "/?LightOn")
    {
        robot_action(6);
    }
    else if(URL_String == "/?LightOff")
    {
        robot_action(7);
    }
    else if(URL_String == "/?LightStrobe")
    {
      robot_action(8);
    }
    else if(URL_String == "/?EyesOn")
    {
        robot_action(9);
    }
    else if(URL_String == "/?EyesOff")
    {
        robot_action(10);
    }
    else if(URL_String.substring(0,8) == "/?Degree=")
    {
        
    }
    else
    {
        // unknown URL
    }
  
    OurPage();
    
    return true;
}

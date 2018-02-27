 /*
 *  Wireless UDP DD with ESP82666
 *  - arush15june 05/01/2018 
 *                FORKED 26/02/2018
 * 
 */

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "DifferentialDrive.h"

ADC_MODE(ADC_VCC);

// Helper Functions

void InfoStr(String type, String Message) {
  String infostr = "[";
  infostr += type;
  infostr += "]";
  infostr += " ";
  infostr += Message;

  Serial.println(infostr);
}

// DD Config
// DifferentialDrive( pins[rightMotorEnable, rightMotorDirF, rightMotorDirB,leftMotorEnable, leftMotorDirF, leftMotorDirB], rightDefaultSpeed, leftDefaultSpeed )

#define rightMotorEnable 0
#define rightMotorDirF 8
#define rightMotorDirB 9

#define leftMotorEnable 0
#define leftMotorDirF 10
#define leftMotorDirB 11

#define rightDefaultSpeed 255
#define leftDefaultSpeed 255

// WiFI Consts

const char* ssid_AP = "GoodBoiBot";
const char* password_AP = "goodboi";
IPAddress apIP(192, 168, 12, 24);
IPAddress netMsk(255, 255, 255, 0);

const char* ssid_WIFI = "Charge-Fi"; // Your Home WLAN SSID
const char* password_WIFI = "19951999"; // Your Home WLAN Password

WiFiUDP Udp;
unsigned int localUdpPort = 4242; // UDP Port to listen on
char incomingPacket[255]; // Incoming Packet Buffer
char replyPacket[] = "Recieved : "; // Generic Reply Packet

int DD_pins[] = {rightMotorEnable, rightMotorDirF, rightMotorDirB,leftMotorEnable, leftMotorDirF, leftMotorDirB};
DifferentialDrive dd(DD_pins, rightDefaultSpeed, leftDefaultSpeed);

void setup() {
    Serial.begin(115200);
    Serial.println();
    InfoStr("Boot","Booted Device");
    WiFi.mode(WIFI_AP_STA);

    // Connect to Home WLAN
    if(WiFi.begin(ssid_WIFI, password_WIFI)) InfoStr("WiFi","Connected to Home WiFi");
    else InfoStr("WiFi", "Home WiFi Not Found");
    
    // Serve a WiFi Access Point̥
    WiFi.softAPConfig(apIP, apIP, netMsk);
    WiFi.softAP(ssid_AP, password_AP);
    InfoStr("AP", "WiFi AP Initialized");
    InfoStr("AP", String(ssid_AP)+" "+String(password_AP));
    InfoStr("AP", String(apIP));

    // Begin UDP Service̥
    Udp.begin(localUdpPort);
    InfoStr("UDP", "Service Initialized");

}

void loop() {
    int packetSize = Udp.parsePacket();

    if(packetSize) {
        InfoStr("UDP", "Recieved Packet");
        int len = Udp.read(incomingPacket, 255);
        if(len > 0) {
            incomingPacket[len] = 0;
        }
        InfoStr("UDP", incomingPacket);

        switch(incomingPacket[0]) {
            case 'F' :  dd.forward();
                        break;
            
            case 'L' :  dd.left();
                        break;

            case 'B' :  dd.backward();
                        break;

            case 'R' :  dd.right();
                        break;

            case 'S' :  dd.stop();
                        break;

            default :  dd.stop();
                            break;
                
        }

        Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
        Udp.write(replyPacket);
        Udp.endPacket();


    }

}
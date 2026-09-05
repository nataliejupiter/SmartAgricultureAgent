#include <Arduino.h>


#define RX2 16
#define TX2 17


void setup()
{

    Serial.begin(115200);


    Serial2.begin(
        9600,
        SERIAL_8N1,
        RX2,
        TX2
    );


    Serial.println("ESP32 LoRa RX start");

}



void loop()
{

    while(Serial2.available())
    {

        char c = Serial2.read();


        Serial.print(c);

    }


}
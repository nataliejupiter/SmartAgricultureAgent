#include <Arduino.h>
#include <WiFi.h>
#include "PubSubClient.h"
#include <HTTPClient.h>

/* 数据帧定义 */
#define FRAME_HEADER 0xAF
#define FRAME_TAIL   0xFE
#define DATA_LEN     10

// 串口引脚定义
#define RX2 16
#define TX2 17

uint8_t buffer[DATA_LEN];
uint8_t myIndex = 0;
bool receiving = false;

/* WIFI */
#define WIFI_SSID   "lily"
#define WIFI_PASSWD "yishichangan"

/* 阿里云三元组 */
#define PRODUCT_KEY   "k0tepWizkpx"
#define DEVICE_NAME   "esp32"
#define DEVICE_SECRET "cc37996578d4ddca1df24270d7a3c763"
#define REGION_ID     "cn-shanghai"

/* 云服务器接口 */
#define SERVER_URL  "http://8.152.218.172:8000/api/env-data"
// 建议换成你自己设的长随机字符串
#define API_KEY     "yishichangan"

/* MQTT */
#define MQTT_SERVER   PRODUCT_KEY".iot-as-mqtt."REGION_ID ".aliyuncs.com"
#define MQTT_PORT     1883
#define MQTT_USRNAME  DEVICE_NAME"&"PRODUCT_KEY

#define CLIENT_ID     "k0tepWizkpx.esp32|securemode=2,signmethod=hmacsha256,timestamp=1774878678525|"
#define MQTT_PASSWD   "f180e9e9b4d3b2b2b917e2e9733fc5712d01686214c2532da91a661670894d8e"

/* 使用标准物模型 Topic */
#define ALINK_BODY_FORMAT "{\"id\":\"esp32\",\"version\":\"1.0\",\"method\":\"thing.event.property.post\",\"params\":%s}"
#define ALINK_TOPIC_PROP_POST "/sys/" PRODUCT_KEY "/" DEVICE_NAME "/thing/event/property/post"

unsigned long lastMs = 0;
bool newDataReady = false; //避免发旧数据

WiFiClient espClient;
PubSubClient client(espClient);

// 检查串口是否能正常通信
// void setup() {
//    Serial.begin(115200); // 调试串口
//    Serial2.begin(115200, SERIAL_8N1, RX2, TX2); // 与外设通信
//    Serial.println("Hello World"); 
// }
// void loop() {
//    if (Serial2.available()) {
//        String data = Serial2.readStringUntil('\n');
//        Serial.println(data);
//    }
// }

/* 环境数据 */
uint16_t temperature = 0;
uint16_t waterLevel = 0;
uint16_t humidity = 0;
uint16_t ph = 0;
uint16_t lightIntensity = 0;
uint16_t CO2 = 1141;

/* 解析数据 */
void parseData(uint8_t *data)
{
    temperature = (data[0] << 8) | data[1];
    waterLevel = (data[2] << 8) | data[3];
    humidity = (data[4] << 8) | data[5];
    ph = (data[6] << 8) | data[7];
    lightIntensity = (data[8] << 8) | data[9];

    Serial.println("====== Parsed Data ======");
    Serial.print("Temperature: "); Serial.println(temperature);
    Serial.print("WaterLevel : "); Serial.println(waterLevel);
    Serial.print("Humidity   : "); Serial.println(humidity);
    Serial.print("pH         : "); Serial.println(ph);
    Serial.print("lightIntensity: "); Serial.println(lightIntensity);
    Serial.print("CO2           : "); Serial.println(CO2);
    Serial.println("========================");

    newDataReady = true;  // 关键
}

/* 串口接收 */
void receiveData(void)
{
    while (Serial2.available())
    {
        uint8_t byte = Serial2.read();

        if (!receiving)
        {
            if (byte == FRAME_HEADER)
            {
                receiving = true;
                myIndex = 0;
                Serial.println("Serial2 receive data successfully!");
            }
        }
        else
        {
            if (myIndex == 0)
            {
                if (byte != DATA_LEN)
                    receiving = false;
                myIndex++;
            }
            else if (myIndex >= 1 && myIndex <= DATA_LEN)
            {
                buffer[myIndex - 1] = byte;
                myIndex++;
            }
            else if (myIndex == DATA_LEN + 1)
            {
                if (byte == FRAME_TAIL)
                    parseData(buffer);
                else
                    Serial.println("Frame tail error!");

                receiving = false;
            }
        }
    }
}

/* WIFI */
void wifiInit()
{
    WiFi.begin(WIFI_SSID, WIFI_PASSWD);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("WiFi not Connect");
    }
    Serial.println("WiFi Connected");
}

/* MQTT连接（避免死循环） */
void mqttCheckConnect()
{
    if (!client.connected())
    {
        Serial.println("Connecting to MQTT...");
        if (client.connect(CLIENT_ID, MQTT_USRNAME, MQTT_PASSWD))
        {
            Serial.println("MQTT Connected!");
        }
        else
        {
            Serial.print("MQTT Connect err:");
            Serial.println(client.state());
        }
    }
}

/* 上传环境数据 */
void mqttIntervalPost()
{
    char param[128];
    char jsonBuf[256];

    snprintf(param, sizeof(param),
             "{\"CurrentTemperature\":%d,\"WaterLevel\":%d,\"RelativeHumidity\":%d,\"SoilPH\":%d,\"SoilMoisture\":%d,\"LightLux\":%d,\"CO2Value\":%d}",
             temperature, waterLevel, humidity, ph, 0, lightIntensity, CO2);

    snprintf(jsonBuf, sizeof(jsonBuf), ALINK_BODY_FORMAT, param);

    Serial.println("Publish:");
    Serial.println(jsonBuf);

    if (client.publish(ALINK_TOPIC_PROP_POST, jsonBuf))
    {
        Serial.println("Publish success");
    }
    else
    {
        Serial.println("Publish failed");
    }
}

/* 发送到云服务器 */
bool postToServer()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        wifiInit();
    }

    HTTPClient http;
    http.setTimeout(5000);

    if (!http.begin(SERVER_URL))
    {
        Serial.println("HTTP begin failed");
        return false;
    }

    http.addHeader("Content-Type", "application/json");
    http.addHeader("X-API-KEY", API_KEY);

    char jsonBuf[256];
    snprintf(jsonBuf, sizeof(jsonBuf),
             "{\"device_id\":\"esp32_01\",\"temperature\":%u,\"water_level\":%u,\"humidity\":%u,\"ph\":%u,\"soil_moisture\":%u,\"LightLux\":%u,\"CO2Value\":%u}",
             temperature, waterLevel, humidity, ph, 0, lightIntensity, CO2);

    Serial.println("POST payload:");
    Serial.println(jsonBuf);

    int httpCode = http.POST((uint8_t *)jsonBuf, strlen(jsonBuf));
    String resp = http.getString();

    Serial.print("HTTP code: ");
    Serial.println(httpCode);

    if (resp.length() > 0)
    {
        Serial.println("Server response:");
        Serial.println(resp);
    }

    http.end();

    return (httpCode >= 200 && httpCode < 300);
}

/* setup */
void setup()
{
    Serial.begin(115200);
    Serial2.begin(9600, SERIAL_8N1, RX2, TX2); 

    wifiInit();
    client.setServer(MQTT_SERVER, MQTT_PORT);
}

/* loop */
void loop()
{
    receiveData();

    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("WiFi reconnecting...");
        wifiInit();
    }

    mqttCheckConnect();
    client.loop();

    if (newDataReady && millis() - lastMs >= 20000) // 每20秒采集一次
    {
        lastMs = millis();

        Serial.println("=== Start Upload ===");

        mqttIntervalPost();

        bool ok = postToServer();

        if (ok)
        {
            Serial.println("HTTP upload success");
        }
        else
        {
            Serial.println("HTTP upload failed");
        }

        Serial.println("=== Upload End ===");
        newDataReady = false;
    }
}
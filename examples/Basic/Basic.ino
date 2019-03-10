/*
 *
 * 1. Install HTTPClientESP32Ex library from https://github.com/mobizt/HTTPClientESP32Ex
 *
 * 2. Install the Arduino ESP32 filesystem uploader plugin in Arduino from
 * https://github.com/me-no-dev/arduino-esp32fs-plugin
 * 
 * 3. From Arduino IDE, select Tools - > ESP32 Sketch Data Upload (Serial Monitor Window need to be close)
 * This will upload sewing.jpg in data folder inside Basic examples folder to device and use in 
 * lineNotify.sendLineImageSPIF(client,"This image from device", "/sewing.jpg");
 * 
 * 4. Change the WIFI_SSID, WIFI_PASSWORD and LINE_TOKEN in sketch.
 * 
 * 4. Compile and upload sketch 
 * 
 */

#include <WiFi.h>
#include "FS.h"
#include "SPIFFS.h"
#include "SD.h"
#include "LineNotifyESP32.h"

//Demo image data
#include "image.h"

#define WIFI_SSID "YOUR_WIFI_AP"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"
#define LINE_TOKEN "YOUR_LINE_NOTIFY_TOKEN"

HTTPClientESP32Ex http;

bool sdOK = false;

void setup()
{

  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(200);
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  //Write demo image to SD card

  if (SD.begin())
  {
    sdOK = true;

    File file = SD.open("/test.jpg", FILE_WRITE);

    int len = sizeof(dummyImageData);
    int pos = 0;

    while (len)
    {
      size_t toWrite = len;
      if (toWrite > 512)
      {
        toWrite = 512;
      }
      file.write(dummyImageData + pos, toWrite);
      len -= toWrite;
      pos += toWrite;
    }

    file.close();
  }

  //Init Line notify with token
  lineNotify.init(LINE_TOKEN);

  uint8_t status;

  status = lineNotify.sendLineMessage(http, "Hello!");
  if (status == LineNotifyESP32::LineStatus::SENT_COMPLETED)
  {
    Serial.println("Send text message completed");
    Serial.println("Text message limit: " + String(lineNotify.textMessageLimit()));
    Serial.println("Text message remaining: " + String(lineNotify.textMessageRemaining()));
    Serial.println("Image message limit: " + String(lineNotify.imageMessageLimit()));
    Serial.println("Image message remaining: " + String(lineNotify.imageMessageRemaining()));
  }
  else if (status == LineNotifyESP32::LineStatus::SENT_FAILED)
    Serial.println("Send text message was failed!");
  else if (status == LineNotifyESP32::LineStatus::CONNECTION_FAILED)
    Serial.println("Connection to LINE sevice faild!");
  Serial.println();

  status = lineNotify.sendLineImageData(http, "This is the image from memory", "image.jpg", dummyImageData, sizeof(dummyImageData));
  if (status == LineNotifyESP32::LineStatus::SENT_COMPLETED)
  {
    Serial.println("send image data completed");
    Serial.println("Text message limit: " + String(lineNotify.textMessageLimit()));
    Serial.println("Text message remaining: " + String(lineNotify.textMessageRemaining()));
    Serial.println("Image message limit: " + String(lineNotify.imageMessageLimit()));
    Serial.println("Image message remaining: " + String(lineNotify.imageMessageRemaining()));
  }
  else if (status == LineNotifyESP32::LineStatus::SENT_FAILED)
    Serial.println("Send image data was failed!");
  else if (status == LineNotifyESP32::LineStatus::CONNECTION_FAILED)
    Serial.println("Connection to LINE sevice faild!");
  Serial.println();

  status = lineNotify.sendLineSticker(http, "Goodbye", 2, 157);
  if (status == LineNotifyESP32::LineStatus::SENT_COMPLETED)
  {
    Serial.println("Send sticker completed");
    Serial.println("Text message limit: " + String(lineNotify.textMessageLimit()));
    Serial.println("Text message remaining: " + String(lineNotify.textMessageRemaining()));
    Serial.println("Image message limit: " + String(lineNotify.imageMessageLimit()));
    Serial.println("Image message remaining: " + String(lineNotify.imageMessageRemaining()));
  }
  else if (status == LineNotifyESP32::LineStatus::SENT_FAILED)
    Serial.println("Send sticker was failed!");
  else if (status == LineNotifyESP32::LineStatus::CONNECTION_FAILED)
    Serial.println("Connection to LINE sevice faild!");
  Serial.println();

  status = lineNotify.sendLineImageURL(http, "This is image I found on web.", "https://cdn.pixabay.com/photo/2017/05/17/18/35/sewing-2321532_640.jpg");
  if (status == LineNotifyESP32::LineStatus::SENT_COMPLETED)
  {
    Serial.println("Send image URL completed");
    Serial.println("Text message limit: " + String(lineNotify.textMessageLimit()));
    Serial.println("Text message remaining: " + String(lineNotify.textMessageRemaining()));
    Serial.println("Image message limit: " + String(lineNotify.imageMessageLimit()));
    Serial.println("Image message remaining: " + String(lineNotify.imageMessageRemaining()));
  }
  else if (status == LineNotifyESP32::LineStatus::SENT_FAILED)
    Serial.println("Send image URL failed!");
  else if (status == LineNotifyESP32::LineStatus::CONNECTION_FAILED)
    Serial.println("Connection to LINE sevice faild!");
  Serial.println();

  status = lineNotify.sendLineImageSPIF(http, "This image from device", "/sewing.jpg");
  if (status == LineNotifyESP32::LineStatus::SENT_COMPLETED)
  {
    Serial.println("Send image from SPIFS file completed");
    Serial.println("Text message limit: " + String(lineNotify.textMessageLimit()));
    Serial.println("Text message remaining: " + String(lineNotify.textMessageRemaining()));
    Serial.println("Image message limit: " + String(lineNotify.imageMessageLimit()));
    Serial.println("Image message remaining: " + String(lineNotify.imageMessageRemaining()));
  }
  else if (status == LineNotifyESP32::LineStatus::SENT_FAILED)
    Serial.println("Send image from SPIFS was failed!");
  else if (status == LineNotifyESP32::LineStatus::CONNECTION_FAILED)
    Serial.println("Connection to LINE sevice faild!");
  Serial.println();

  if (sdOK)
  {
    status = lineNotify.sendLineImageSD(http, "This image from SD card", "/test.jpg");
    if (status == LineNotifyESP32::LineStatus::SENT_COMPLETED)
    {
      Serial.println("Send image from SD card completed");
      Serial.println("Text message limit: " + String(lineNotify.textMessageLimit()));
      Serial.println("Text message remaining: " + String(lineNotify.textMessageRemaining()));
      Serial.println("Image message limit: " + String(lineNotify.imageMessageLimit()));
      Serial.println("Image message remaining: " + String(lineNotify.imageMessageRemaining()));
    }
    else if (status == LineNotifyESP32::LineStatus::SENT_FAILED)
      Serial.println("Send image from SD card was failed!");
    else if (status == LineNotifyESP32::LineStatus::CONNECTION_FAILED)
      Serial.println("Connection to LINE sevice faild!");
    Serial.println();
  }
}

void loop()
{
}

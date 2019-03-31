/*
   This example uses OV2640 Camera connected to ESP32

   1. Install HTTPClientESP32Ex library from https://github.com/mobizt/HTTPClientESP32Ex

   2. Change the WIFI_SSID, WIFI_PASSWORD and LINE_TOKEN in sketch.

   3. Compile and upload sketch

*/

#include <WiFi.h>
#include "FS.h"
#include "SPIFFS.h"
#include "LineNotifyESP32.h"
#include "src/OV2640.h"

#define WIFI_SSID "YOUR_WIFI_AP"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"
#define LINE_TOKEN "YOUR_LINE_NOTIFY_TOKEN"

HTTPClientESP32Ex http;
OV2640 cam;

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

  //Change to match your pin configuration between OV2640 Camera and ESP32 connection
  //This config is for ThaiEasyElec's Camera Expansion for ESPino32 (OV2640)
  camera_config_t camera_config;
  camera_config.ledc_channel = LEDC_CHANNEL_0;
  camera_config.ledc_timer = LEDC_TIMER_0;
  camera_config.pin_d0 = 33;
  camera_config.pin_d1 = 39;
  camera_config.pin_d2 = 36;
  camera_config.pin_d3 = 32;
  camera_config.pin_d4 = 34;
  camera_config.pin_d5 = 35;
  camera_config.pin_d6 = 04;
  camera_config.pin_d7 = 15;
  camera_config.pin_xclk = 13;
  camera_config.pin_pclk = 12;
  camera_config.pin_vsync = 14;
  camera_config.pin_href = 27;
  camera_config.pin_sscb_sda = 21;
  camera_config.pin_sscb_scl = 22;
  camera_config.pin_reset = 25;
  camera_config.xclk_freq_hz = 10000000;

  /*
 * For M5Stack ESP32 Camera (OV2640)
 * 

  camera_config.ledc_channel = LEDC_CHANNEL_0;
  camera_config.ledc_timer = LEDC_TIMER_0;
  camera_config.pin_d0 = 17;
  camera_config.pin_d1 = 35;
  camera_config.pin_d2 = 34;
  camera_config.pin_d3 = 5;
  camera_config.pin_d4 = 39;
  camera_config.pin_d5 = 18;
  camera_config.pin_d6 = 36;
  camera_config.pin_d7 = 19;
  camera_config.pin_xclk = 27;
  camera_config.pin_pclk = 21;
  camera_config.pin_vsync = 22;
  camera_config.pin_href = 26;
  camera_config.pin_sscb_sda = 25;
  camera_config.pin_sscb_scl = 23;
  camera_config.pin_reset = 15;
  camera_config.xclk_freq_hz = 20000000;
  */

  camera_config.pixel_format = CAMERA_PF_JPEG;
  camera_config.frame_size = CAMERA_FS_SVGA;

  cam.init(camera_config);

  delay(100);

  cam.run();

  lineNotify.init(LINE_TOKEN);

  uint8_t status = lineNotify.sendLineImageData(http, "This is the image camera", "image.jpg", cam.getfb(), cam.getSize());
  if (status == LineNotifyESP32::LineStatus::SENT_COMPLETED)
  {
    Serial.println("send image data from camera completed");
    Serial.println("Text message limit: " + String(lineNotify.textMessageLimit()));
    Serial.println("Text message remaining: " + String(lineNotify.textMessageRemaining()));
    Serial.println("Image message limit: " + String(lineNotify.imageMessageLimit()));
    Serial.println("Image message remaining: " + String(lineNotify.imageMessageRemaining()));
  }
  else if (status == LineNotifyESP32::LineStatus::SENT_FAILED)
    Serial.println("Send image data from camera was failed!");
  else if (status == LineNotifyESP32::LineStatus::CONNECTION_FAILED)
    Serial.println("Connection to LINE sevice faild!");
  Serial.println();
}

void loop()
{
}

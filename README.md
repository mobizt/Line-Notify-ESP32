# LINE Notify Arduino Library for ESP32 version 1.0.1

This Arduino library allows ESP32 to send LINE Notify message, sticker, SD card image and camera image.

The library was test and work well with ESP32s based module.

Copyright (c) 2019 K. Suwatchai (Mobizt).





## New library is available

The new library for ESP8266 and ESP32 Line Notify is available at
https://github.com/mobizt/ESP-Line-Notify





## Tested Devices

This following devices were tested and work well.

 * Sparkfun ESP32 Thing
 * NodeMCU-32
 * WEMOS LOLIN32


 
## Features

* Support sending text, sticker, Flash image, SD card image, and camera image.

* Able to show remang each message type quota.


## Dependencies

Required HTTPClientESP32Ex library to be installed. https://github.com/mobizt/HTTPClientESP32Ex



## Installing


Click on **Clone or download** dropdown at the top of repository, select **Download ZIP** and save file on your computer.

From Arduino IDE, goto menu **Sketch** -> **Include Library** -> **Add .ZIP Library...** and choose **Line-Notify-ESP32-master.zip** that previously downloaded.

Go to menu **Files** -> **Examples** -> **Line-Notify-ESP32-master** and choose one from examples



## Usages


See [full examples](https://github.com/mobizt/Line-Notify-ESP32/tree/master/examples) for all features usages.



## All Supported Functions


**The LINE Notify Service's credentials initialization.**

param *`token`* - LINE Notify token String.

```C++
init(const String &token);
```


   
    

**Set the LINE Notify token.**

param *`token`* - LINE Notify token string.

```C++
void setToken(const String &token);
```




**Send text message.**
   
param *`client`* - SSL WiFi client from WiFiClientSecure initialization.

param *`msg`* - The text message String to be send.
    
return *`The LineStatus structed value`*, SENT_COMPLETED = 0, SENT_FAILED = 1, CONNECTION_FAILED = 2.

```C++
uint8_t sendLineMessage(HTTPClientESP32Ex &http, const String &msg);
```




**Send text message with sticker.**

param *`client`* - SSL WiFi client from WiFiClientSecure initialization.

param *`msg`* - The text message String to be send.

param *`stickerPackageId`* - Sticker Package ID number to send, see https://devdocs.line.me/files/sticker_list.pdf for STKPKGID.

param *`stickerId`* - Sticker ID number to send, see https://devdocs.line.me/files/sticker_list.pdf for STKID.

return *`The LineStatus structed value`*, SENT_COMPLETED = 0, SENT_FAILED = 1, CONNECTION_FAILED = 2.

```C++
uint8_t sendLineSticker(HTTPClientESP32Ex &http, const String &msg, uint16_t stickerPackageId, uint16_t stickerId);
```




**Send Image message. The image data from flash memory or EEPROM**

param *`client`* - SSL WiFi client from WiFiClientSecure initialization.

param *`msg`* - The text message String to be send.

param *`fileName`* - The user's specified file name String.

param *`imageData`* - The byte data of image from memory or EEPROM.

param *`imageLength`* - The byte length of image data.

return *`The LineStatus structed value`*, SENT_COMPLETED = 0, SENT_FAILED = 1, CONNECTION_FAILED = 2.

```C++
uint8_t sendLineImageData(HTTPClientESP32Ex &http, const String &msg, const String &fileName, const uint8_t *imageData, size_t imageLength);
```




**Send Image message. The image data from web URL.**

param *`client`* - SSL WiFi client from WiFiClientSecure initialization.

param *`msg`* - The text message String to be send.

param *`imageURL`* - The image URL String.

return *`The LineStatus structed value`*, SENT_COMPLETED = 0, SENT_FAILED = 1, CONNECTION_FAILED = 2.

```C++
uint8_t sendLineImageURL(HTTPClientESP32Ex &http, const String &msg, const String &imageURL);
```




**Send Image message. The image data from SPI Flash File.**

param *`client`* - SSL WiFi client from WiFiClientSecure initialization.

param *`msg`* - The text message String to be send.

param *`filePath`* - The image file name and path String inside SPIF.

return *`The LineStatus structed value`*, SENT_COMPLETED = 0, SENT_FAILED = 1, CONNECTION_FAILED = 2.

```C++
uint8_t sendLineImageSPIF(HTTPClientESP32Ex &http, const String &msg, const String &filePath);
```




**Send Image message. The image data from SD card File.**

param *`client`* - SSL WiFi client from WiFiClientSecure initialization.

param *`msg`* - The text message String to be send.

param *`filePath`* - The image file name and path String inside SD card.

return *`The LineStatus structed value`*, SENT_COMPLETED = 0, SENT_FAILED = 1, CONNECTION_FAILED = 2.

```C++
uint8_t sendLineImageSD(HTTPClientESP32Ex &http, const String &msg, const String &filePath);
```




**Get the text message limit.**

return *`The limit count of sending text message.`*

```C++
uint16_t textMessageLimit(void);
```




**Get the image message limit.**

return *`The limit count of sending image message.`*

```C++
uint16_t imageMessageLimit(void);
```




**Get the remaining count of sending text message.**

return *`The remaining count of sending text message.`*

```C++
uint16_t textMessageRemaining(void);
```




**Get the remaining count of sending image message.**

return *`The remaining count of sending image message.`*

```C++
uint16_t imageMessageRemaining(void);
```



**End Line Notify.**

```C++
void end(void);
```


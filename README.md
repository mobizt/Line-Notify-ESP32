# LINE Notify Arduino Library for ESP32

This library provides ESP32 to perform REST API call to LINE Notify service to post the several message types. 

The library was test and work well with ESP32s based module.

Copyright (c) 2019 K. Suwatchai (Mobizt).

## Tested Devices

This library works well in the following tested devices.

 * Wemos D1 Mini
 * NodeMCU
 
## Features

Complete Firebase's REST API requests.

Able send text, sticker and image message to LINE Notify services.


## Dependencies
Required HTTPClientESP32Ex library to be installed. 
https://github.com/mobizt/HTTPClientESP32Ex


## Supported functions

```c++
   /**
   * The LINE Notify Service's credentials initialization.
   * \param token - Your LINE Notify token string (constant chars array).
   */
    void init(const char* token);
	
   /**
   * The LINE Notify Service's credentials initialization.
   * \param token - Your LINE Notify token String.
   */
    void init(const String token);
	
   /**
   * Set the LINE Notify token string.
   * \param token - Your LINE Notify token string (constant chars array).
   */
    void set_token(const char* token);
	
   /**
   * Set the LINE Notify token string.
   * \param token - Your LINE Notify token String.
   */
    void set_token(const String token);
	
   /**
   * Send text message.
   * \param client - SSL WiFi client from WiFiClientSecure initialization.
   * \param msg - The text message to be send (constant chars array).
   */
    uint8_t sendLineMessage(WiFiClientSecure &client, const char* msg);
	
	
   /**
   * Send text message.
   * \param client - SSL WiFi client from WiFiClientSecure initialization.
   * \param msg - The text message String to be send.
   */
    uint8_t sendLineMessage(WiFiClientSecure &client, const String msg);
	
   /**
   * Send text message with sticker.
   * \param client - SSL WiFi client from WiFiClientSecure initialization.
   * \param msg - The text message to be send (constant chars array).
   * \param stickerPackageId - Sticker Package ID number to send, 
   * see https://devdocs.line.me/files/sticker_list.pdf for STKPKGID
   * \param stickerId - Sticker ID number to send, see 
   * https://devdocs.line.me/files/sticker_list.pdf for STKID
   */
    uint8_t sendLineSticker(WiFiClientSecure &client, const char* msg, uint16_t  stickerPackageId, uint16_t stickerId);
	
   /**
   * Send text message with sticker.
   * \param client - SSL WiFi client from WiFiClientSecure initialization.
   * \param msg - The text message String to be send.
   * \param stickerPackageId - Sticker Package ID number to send, 
   * see https://devdocs.line.me/files/sticker_list.pdf for STKPKGID
   * \param stickerId - Sticker ID number to send, see 
   * https://devdocs.line.me/files/sticker_list.pdf for STKID
   */
    uint8_t sendLineSticker(WiFiClientSecure &client, const String msg, uint16_t  stickerPackageId, uint16_t stickerId);
	
   /**
   * Send Image message. The image data from flash memory or EEPROM
   * \param client - SSL WiFi client from WiFiClientSecure initialization.
   * \param msg - The text message to be send (constant chars array).
   * \param fileName - The user's specified file name (constant chars array).
   * \param imageData - The byte data of image from memory or EEPROM.
   * \param imageLength - The byte length of image data.   
   */
    uint8_t sendLineImageData(WiFiClientSecure &client, const char* msg, const char* fileName, uint8_t* imageData, size_t imageLength);
    
   /**
   * Send Image message. The image data from flash memory or EEPROM
   * \param client - SSL WiFi client from WiFiClientSecure initialization.
   * \param msg - The text message String to be send.
   * \param fileName - The user's specified file name String.
   * \param imageData - The byte data of image from memory or EEPROM.
   * \param imageLength - The byte length of image data.   
   */
    uint8_t sendLineImageData(WiFiClientSecure &client, const String msg, const String fileName, uint8_t* imageData, size_t imageLength);
    
   /**
   * Send Image message. The image data from web URL
   * \param client - SSL WiFi client from WiFiClientSecure initialization.
   * \param msg - The text message to be send (constant chars array).
   * \param imageURL - The image URL (constant chars array).
   */
	uint8_t sendLineImageURL(WiFiClientSecure &client, const char* msg, const char* imageURL);
	
   /**
   * Send Image message. The image data from web URL
   * \param client - SSL WiFi client from WiFiClientSecure initialization.
   * \param msg - The text message String to be send.
   * \param imageURL - The image URL String.
   */
	uint8_t sendLineImageURL(WiFiClientSecure &client, const String msg, const String imageURL);
	
	
   /**
   * Send Image message. The image data from SPI Flash File
   * \param client - SSL WiFi client from WiFiClientSecure initialization.
   * \param msg - The text message to be send (constant chars array).
   * \param filePath - The image file name and path inside SPIF (constant chars array).
   */
    uint8_t sendLineImageSPIF(WiFiClientSecure &client, const char* msg, const char* filePath);
	
   /**
   * Send Image message. The image data from SPI Flash File
   * \param client - SSL WiFi client from WiFiClientSecure initialization.
   * \param msg - The text message String to be send.
   * \param filePath - The image file name and path String inside SPIF.
   */
    uint8_t sendLineImageSPIF(WiFiClientSecure &client, const String msg, const String filePath);


```
## Installing

Click on Clone or download dropdown at the top of repository, select Download ZIP and save zip file to your computer.

From Arduino IDE, goto menu Sketch -> Include Library -> Add .ZIP Library... and choose Line-Notify-ESP32-master.zip from last download.

Go to menu Files -> Examples -> Line-Notify-ESP32-master and choose one from examples

## Usages

```c++

See the examples

```

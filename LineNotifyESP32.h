/*
 * LINE Notify Arduino Library for ESP32
 *
 * This library provides ESP32 to perform REST API call to LINE Notify service to post the several message types.
 *
 * The library was test and work well with ESP32s based module.
 * 
 * The MIT License (MIT)
 * Copyright (c) 2019 K. Suwatchai (Mobizt)
 * 
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
 * The MIT License (MIT)
 * Copyright (c) 2019 K. Suwatchai (Mobizt)
 * 
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#ifndef LineNotifyESP32_H
#define LineNotifyESP32_H

#include <Arduino.h>
#include <WiFiClientSecure.h>
#include <WiFi.h>
#include "FS.h"
#include "SPIFFS.h"
#include <HTTPClientESP32Ex.h>


class LineNotifyESP32 {
  
  public:
  
  struct LineStatus {
      static const uint8_t SENT_COMPLETED = 0;
      static const uint8_t SENT_FAILED = 1;
      static const uint8_t CONNECTION_FAILED = 2;
   };
   
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
    void setToken(const char* token);
  
   /**
   * Set the LINE Notify token string.
   * \param token - Your LINE Notify token String.
   */
    void setToken(const String token);
  
   /**
   * Send text message.
   * \param client - SSL WiFi client from WiFiClientSecure initialization.
   * \param msg - The text message to be send (constant chars array).
   * \return The LineStatus struct value, SENT_COMPLETED = 0, SENT_FAILED = 1, CONNECTION_FAILED = 2.
   */
    uint8_t sendLineMessage(HTTPClientESP32Ex &http, const char* msg);
  
  
   /**
   * Send text message.
   * \param client - SSL WiFi client from WiFiClientSecure initialization.
   * \param msg - The text message String to be send.
   * \return The LineStatus struct value, SENT_COMPLETED = 0, SENT_FAILED = 1, CONNECTION_FAILED = 2.
   */
    uint8_t sendLineMessage(HTTPClientESP32Ex &http, const String msg);
  
   /**
   * Send text message with sticker.
   * \param client - SSL WiFi client from WiFiClientSecure initialization.
   * \param msg - The text message to be send (constant chars array).
   * \param stickerPackageId - Sticker Package ID number to send, 
   * see https://devdocs.line.me/files/sticker_list.pdf for STKPKGID
   * \param stickerId - Sticker ID number to send, see 
   * https://devdocs.line.me/files/sticker_list.pdf for STKID
   * \return The LineStatus struct value, SENT_COMPLETED = 0, SENT_FAILED = 1, CONNECTION_FAILED = 2.
   */
    uint8_t sendLineSticker(HTTPClientESP32Ex &http, const char* msg, uint16_t  stickerPackageId, uint16_t stickerId);
  
   /**
   * Send text message with sticker.
   * \param client - SSL WiFi client from WiFiClientSecure initialization.
   * \param msg - The text message String to be send.
   * \param stickerPackageId - Sticker Package ID number to send, 
   * see https://devdocs.line.me/files/sticker_list.pdf for STKPKGID
   * \param stickerId - Sticker ID number to send, see 
   * https://devdocs.line.me/files/sticker_list.pdf for STKID
   * \return The LineStatus struct value, SENT_COMPLETED = 0, SENT_FAILED = 1, CONNECTION_FAILED = 2.
   */
    uint8_t sendLineSticker(HTTPClientESP32Ex &http, const String msg, uint16_t  stickerPackageId, uint16_t stickerId);
  
   /**
   * Send Image message. The image data from flash memory or EEPROM
   * \param client - SSL WiFi client from WiFiClientSecure initialization.
   * \param msg - The text message to be send (constant chars array).
   * \param fileName - The user's specified file name (constant chars array).
   * \param imageData - The byte data of image from memory or EEPROM.
   * \param imageLength - The byte length of image data.
   * \return The LineStatus struct value, SENT_COMPLETED = 0, SENT_FAILED = 1, CONNECTION_FAILED = 2.
   */
    uint8_t sendLineImageData(HTTPClientESP32Ex &http, const char* msg, const char* fileName, uint8_t* imageData, size_t imageLength);
    
   /**
   * Send Image message. The image data from flash memory or EEPROM
   * \param client - SSL WiFi client from WiFiClientSecure initialization.
   * \param msg - The text message String to be send.
   * \param fileName - The user's specified file name String.
   * \param imageData - The byte data of image from memory or EEPROM.
   * \param imageLength - The byte length of image data.   
   * \return The LineStatus struct value, SENT_COMPLETED = 0, SENT_FAILED = 1, CONNECTION_FAILED = 2.
   */
    uint8_t sendLineImageData(HTTPClientESP32Ex &http, const String msg, const String fileName, uint8_t* imageData, size_t imageLength);
    
   /**
   * Send Image message. The image data from web URL
   * \param client - SSL WiFi client from WiFiClientSecure initialization.
   * \param msg - The text message to be send (constant chars array).
   * \param imageURL - The image URL (constant chars array).
   * \return The LineStatus struct value, SENT_COMPLETED = 0, SENT_FAILED = 1, CONNECTION_FAILED = 2.
   */
  uint8_t sendLineImageURL(HTTPClientESP32Ex &http, const char* msg, const char* imageURL);
  
   /**
   * Send Image message. The image data from web URL
   * \param client - SSL WiFi client from WiFiClientSecure initialization.
   * \param msg - The text message String to be send.
   * \param imageURL - The image URL String.
   * \return The LineStatus struct value, SENT_COMPLETED = 0, SENT_FAILED = 1, CONNECTION_FAILED = 2.
   */
  uint8_t sendLineImageURL(HTTPClientESP32Ex &http, const String msg, const String imageURL);
  
  
   /**
   * Send Image message. The image data from SPI Flash File
   * \param client - SSL WiFi client from WiFiClientSecure initialization.
   * \param msg - The text message to be send (constant chars array).
   * \param filePath - The image file name and path inside SPIF (constant chars array).
   * \return The LineStatus struct value, SENT_COMPLETED = 0, SENT_FAILED = 1, CONNECTION_FAILED = 2.
   */
    uint8_t sendLineImageSPIF(HTTPClientESP32Ex &http, const char* msg, const char* filePath);
  
   /**
   * Send Image message. The image data from SPI Flash File
   * \param client - SSL WiFi client from WiFiClientSecure initialization.
   * \param msg - The text message String to be send.
   * \param filePath - The image file name and path String inside SPIF.
   * \return The LineStatus struct value, SENT_COMPLETED = 0, SENT_FAILED = 1, CONNECTION_FAILED = 2.
   */
    uint8_t sendLineImageSPIF(HTTPClientESP32Ex &http, const String msg, const String filePath);
	
   /**
   * Get the text message limit
   * \return The limit count of sending text message.
   */
    uint16_t textMessageLimit(void);
	
   /**
   * Get the image message limit
   * \return The limit count of sending image message.
   */
    uint16_t imageMessageLimit(void);
	
   /**
   * Get the remaining count of sending text message
   * \return The remaining count of sending text message.
   */
    uint16_t textMessageRemaining(void);

   /**
   * Get the remaining count of sending image message
   * \return The remaining count of sending image message.
   */
    uint16_t imageMessageRemaining(void);

  private:
    const char LINE_HOST[100] = "notify-api.line.me";
    const uint16_t LINE_PORT = 443;
    const char HEADER_BOUNDARY[50] = "{BOUNDARY}";
    const char USER_AGENT[30] = "ESP32";
    const uint16_t LINE_TIMEOUT = 5000;
    char LINE_TOKEN[50];
    const char newline[10] = "\r\n";
	int _textLimit;
	int _imageLimit;
	int _textRemaining;
	int _imageRemaining;
    
    int send_request_header(HTTPClientESP32Ex &http, const char* token, size_t contentLength);
    void set_multipart_header(char* data, const char* arg);
    void set_multipart_boundary(char* data);
    bool waitLineResponse(HTTPClientESP32Ex &http);
    void getContentType(const char* filename, char* buf);
    void strcat_c (char *str, char c);
    int strpos(const char *haystack, const char *needle, int offset);
    int rstrpos(const char *haystack, const char *needle, int offset);
    char* rstrstr(const char* haystack, const char* needle);
    char* replace_char(char* str, char in, char out);

  
};



extern LineNotifyESP32 lineNotify;


#endif

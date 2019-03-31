/*
 * LINE Notify Arduino Library for ESP32 version 1.0.1
 * 
 * March 10, 2019
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

#ifndef LineNotifyESP32_CPP
#define LineNotifyESP32_CPP

#include "LineNotifyESP32.h"

LineNotifyESP32::LineNotifyESP32(){};

LineNotifyESP32::~LineNotifyESP32()
{
  end();
};


void LineNotifyESP32::end()
{
  std::string().swap(_token);
};

void LineNotifyESP32::init(const String &token)
{
  SPIFFS.begin(true);
  _token = token.c_str();
}

void LineNotifyESP32::setToken(const String &token)
{
  _token = token.c_str();
}

int LineNotifyESP32::send_request_header(HTTPClientESP32Ex &http, const std::string &token, size_t contentLength)
{
  std::string data = "";
  char *val = new char[10];
  memset(val, 0, 10);

  data = ESP32_LINE_NOTIFY_STR_5;
  data += ESP32_LINE_NOTIFY_STR_4;

  data += ESP32_LINE_NOTIFY_STR_6;
  data += ESP32_LINE_NOTIFY_STR_4;

  data += ESP32_LINE_NOTIFY_STR_7;
  data += token;
  data += ESP32_LINE_NOTIFY_STR_4;

  data += ESP32_LINE_NOTIFY_STR_8;
  data += ESP32_LINE_NOTIFY_STR_2;
  data += ESP32_LINE_NOTIFY_STR_4;

  data += ESP32_LINE_NOTIFY_STR_9;
  data += ESP32_LINE_NOTIFY_STR_3;
  data += ESP32_LINE_NOTIFY_STR_4;

  data += ESP32_LINE_NOTIFY_STR_10;
  data += ESP32_LINE_NOTIFY_STR_4;

  data += ESP32_LINE_NOTIFY_STR_11;
  data += ESP32_LINE_NOTIFY_STR_1;
  data += ESP32_LINE_NOTIFY_STR_4;

  data += ESP32_LINE_NOTIFY_STR_12;
  data += ESP32_LINE_NOTIFY_STR_4;

  data += ESP32_LINE_NOTIFY_STR_13;
  data += ESP32_LINE_NOTIFY_STR_4;

  data += ESP32_LINE_NOTIFY_STR_14;
  itoa(contentLength, val, 10);
  data += val;
  data += ESP32_LINE_NOTIFY_STR_4;
  data += ESP32_LINE_NOTIFY_STR_4;

  int res = http.http_sendRequest(data.c_str(), "");

  std::string().swap(data);
  delete[] val;

  return res;
}

void LineNotifyESP32::set_multipart_header(std::string &data, const std::string &arg)
{

  data += ESP32_LINE_NOTIFY_STR_24;
  data += ESP32_LINE_NOTIFY_STR_2;
  data += ESP32_LINE_NOTIFY_STR_4;

  if (arg == ESP32_LINE_NOTIFY_STR_19 || arg == ESP32_LINE_NOTIFY_STR_20 || arg == ESP32_LINE_NOTIFY_STR_21 || arg == ESP32_LINE_NOTIFY_STR_22 || arg == ESP32_LINE_NOTIFY_STR_23)
  {
    data += ESP32_LINE_NOTIFY_STR_18;
    data += arg;
    data += ESP32_LINE_NOTIFY_STR_25;
    data += ESP32_LINE_NOTIFY_STR_4;
    data += ESP32_LINE_NOTIFY_STR_4;
  }
  else
  {
    data += ESP32_LINE_NOTIFY_STR_16;
    data += arg;
    data += ESP32_LINE_NOTIFY_STR_25;
    data += ESP32_LINE_NOTIFY_STR_4;

    data += ESP32_LINE_NOTIFY_STR_17;
    getContentType(arg, data);
    data += ESP32_LINE_NOTIFY_STR_4;
    data += ESP32_LINE_NOTIFY_STR_4;
  }
}

void LineNotifyESP32::set_multipart_boundary(std::string &data)
{
  data += ESP32_LINE_NOTIFY_STR_24;
  data += ESP32_LINE_NOTIFY_STR_2;
  data += ESP32_LINE_NOTIFY_STR_24;
  data += ESP32_LINE_NOTIFY_STR_4;
}

uint8_t LineNotifyESP32::sendLineMessage(HTTPClientESP32Ex &http, const String &msg)
{
  std::string uri = ESP32_LINE_NOTIFY_STR_15;

  http.http_begin(ESP32_LINE_NOTIFY_STR_1, LINE_PORT, uri.c_str(), (const char *)NULL);

  std::string textHeader = "";
  set_multipart_header(textHeader, ESP32_LINE_NOTIFY_STR_19);
  textHeader += msg.c_str();
  textHeader += ESP32_LINE_NOTIFY_STR_4;
  set_multipart_boundary(textHeader);

  send_request_header(http, _token.c_str(), textHeader.length());
  http.http_sendRequest("", textHeader.c_str());

  std::string().swap(textHeader);
  std::string().swap(uri);

  if (waitLineResponse(http))
    return LineNotifyESP32::LineStatus::SENT_COMPLETED;
  else
    return LineNotifyESP32::LineStatus::SENT_FAILED;
}

uint8_t LineNotifyESP32::sendLineSticker(HTTPClientESP32Ex &http, const String &msg, uint16_t stickerPackageId, uint16_t stickerId)
{
  std::string uri = ESP32_LINE_NOTIFY_STR_15;

  http.http_begin(ESP32_LINE_NOTIFY_STR_1, LINE_PORT, uri.c_str(), (const char *)NULL);

  char *val = new char[20];
  std::string textHeader = "";

  set_multipart_header(textHeader, ESP32_LINE_NOTIFY_STR_19);
  textHeader += msg.c_str();
  textHeader += ESP32_LINE_NOTIFY_STR_4;

  set_multipart_header(textHeader, ESP32_LINE_NOTIFY_STR_20);
  memset(val, 0, 20);
  itoa(stickerPackageId, val, 10);
  textHeader += val;
  textHeader += ESP32_LINE_NOTIFY_STR_4;

  set_multipart_header(textHeader, ESP32_LINE_NOTIFY_STR_21);
  memset(val, 0, 20);
  itoa(stickerId, val, 10);
  textHeader += val;
  textHeader += ESP32_LINE_NOTIFY_STR_4;

  set_multipart_boundary(textHeader);

  delete[] val;

  if (send_request_header(http, _token, textHeader.length()) == 0)
  {

    http.http_sendRequest("", textHeader.c_str());

    std::string().swap(textHeader);
    std::string().swap(uri);

    if (waitLineResponse(http))
      return LineNotifyESP32::LineStatus::SENT_COMPLETED;
    else
      return LineNotifyESP32::LineStatus::SENT_FAILED;
  }

  std::string().swap(textHeader);
  std::string().swap(uri);

  return HTTPC_ERROR_CONNECTION_REFUSED;
}

uint8_t LineNotifyESP32::sendLineImageData(HTTPClientESP32Ex &http, const String &msg, const String &fileName, const uint8_t *imageData, size_t imageLength)
{

  std::string uri = ESP32_LINE_NOTIFY_STR_15;

  http.http_begin(ESP32_LINE_NOTIFY_STR_1, LINE_PORT, uri.c_str(), (const char *)NULL);

  std::string textHeader = "";
  std::string imageHeader = "";
  std::string boundary = "";

  set_multipart_header(textHeader, ESP32_LINE_NOTIFY_STR_19);
  textHeader += msg.c_str();
  textHeader += ESP32_LINE_NOTIFY_STR_4;

  set_multipart_header(imageHeader, fileName.c_str());

  set_multipart_boundary(boundary);

  uint32_t contentLength = textHeader.length() + imageHeader.length() + imageLength + boundary.length();

  if (send_request_header(http, _token, contentLength) == 0)
  {

    http.http_sendRequest("", textHeader.c_str());
    http.http_sendRequest("", imageHeader.c_str());

    size_t chunkSize = 512;

    size_t byteRead = 0;

    WiFiClient *tcp = http.http_getStreamPtr();

    while (byteRead < imageLength)
    {
      if (byteRead + chunkSize < imageLength)
      {
        tcp->write(imageData, chunkSize);
        imageData += chunkSize;
        byteRead += chunkSize;
      }
      else
      {
        tcp->write(imageData, imageLength - byteRead);
        imageData += chunkSize;
        byteRead = imageLength;
      }
      yield();
    }

    http.http_sendRequest("", ESP32_LINE_NOTIFY_STR_4);
    http.http_sendRequest("", boundary.c_str());

    std::string().swap(textHeader);
    std::string().swap(imageHeader);
    std::string().swap(boundary);
    std::string().swap(uri);

    if (waitLineResponse(http))
      return LineNotifyESP32::LineStatus::SENT_COMPLETED;
    else
      return LineNotifyESP32::LineStatus::SENT_FAILED;
  }

  std::string().swap(textHeader);
  std::string().swap(imageHeader);
  std::string().swap(boundary);
  std::string().swap(uri);

  return HTTPC_ERROR_CONNECTION_REFUSED;
}

uint8_t LineNotifyESP32::sendLineImageURL(HTTPClientESP32Ex &http, const String &msg, const String &imageURL)
{

  std::string uri = ESP32_LINE_NOTIFY_STR_15;

  http.http_begin(ESP32_LINE_NOTIFY_STR_1, LINE_PORT, uri.c_str(), (const char *)NULL);

  std::string textHeader = "";

  set_multipart_header(textHeader, ESP32_LINE_NOTIFY_STR_19);
  textHeader += msg.c_str();
  textHeader += ESP32_LINE_NOTIFY_STR_4;

  set_multipart_header(textHeader, ESP32_LINE_NOTIFY_STR_22);
  textHeader += imageURL.c_str();
  textHeader += ESP32_LINE_NOTIFY_STR_4;

  set_multipart_header(textHeader, ESP32_LINE_NOTIFY_STR_23);
  textHeader += imageURL.c_str();
  textHeader += ESP32_LINE_NOTIFY_STR_4;

  set_multipart_boundary(textHeader);

  if (send_request_header(http, _token, textHeader.length()) == 0)
  {

    http.http_sendRequest("", textHeader.c_str());

    std::string().swap(textHeader);
    std::string().swap(uri);

    if (waitLineResponse(http))
      return LineNotifyESP32::LineStatus::SENT_COMPLETED;
    else
      return LineNotifyESP32::LineStatus::SENT_FAILED;
  }
  std::string().swap(textHeader);
  std::string().swap(uri);
  return HTTPC_ERROR_CONNECTION_REFUSED;
}

uint8_t LineNotifyESP32::sendLineImageFile(HTTPClientESP32Ex &http, const String &msg, const String &filePath, bool internal)
{
  bool fileExisted = false;

  if (internal)
    fileExisted = SPIFFS.exists(filePath);
  else
  {
    if (!sdTest())
      return LineNotifyESP32::LineStatus::SENT_FAILED;
    
    fileExisted = SD.exists(filePath);
  }

  if (fileExisted)
  {
    std::string textHeader = "";
    std::string imageHeader = "";
    std::string boundary = "";

    File file;

    if (internal)
      file = SPIFFS.open(filePath, "r");
    else
      file = SD.open(filePath, "r");

    uint32_t imageLength = file.size();

    std::string uri = ESP32_LINE_NOTIFY_STR_15;

    http.http_begin(ESP32_LINE_NOTIFY_STR_1, LINE_PORT, uri.c_str(), (const char *)NULL);

    set_multipart_header(textHeader, ESP32_LINE_NOTIFY_STR_19);
    textHeader += msg.c_str();
    textHeader += ESP32_LINE_NOTIFY_STR_4;

    set_multipart_header(imageHeader, filePath.c_str());

    set_multipart_boundary(boundary);

    uint32_t contentLength = textHeader.length() + imageHeader.length() + imageLength + boundary.length();

    if (send_request_header(http, _token, contentLength) == 0)
    {

      http.http_sendRequest("", textHeader.c_str());

      http.http_sendRequest("", imageHeader.c_str());

      size_t chunkSize = 512;
      uint8_t chunk[chunkSize];
      size_t byteRead = 0;

      WiFiClient *tcp = http.http_getStreamPtr();

      while (byteRead < imageLength)
      {
        memset(chunk, 0, sizeof chunk);
        if (byteRead + chunkSize < imageLength)
        {
          file.read(chunk, chunkSize);
          tcp->write(chunk, chunkSize);
          byteRead += chunkSize;
        }
        else
        {
          file.read(chunk, imageLength - byteRead);
          tcp->write(chunk, imageLength - byteRead);
          byteRead = imageLength;
          break;
        }
        yield();
      }

      file.close();

      http.http_sendRequest("", ESP32_LINE_NOTIFY_STR_4);
      http.http_sendRequest("", boundary.c_str());

      std::string().swap(textHeader);
      std::string().swap(imageHeader);
      std::string().swap(boundary);
      std::string().swap(uri);

      if (waitLineResponse(http))
        return LineNotifyESP32::LineStatus::SENT_COMPLETED;
      else
        return LineNotifyESP32::LineStatus::SENT_FAILED;
    }

    std::string().swap(textHeader);
    std::string().swap(imageHeader);
    std::string().swap(boundary);
    std::string().swap(uri);

    return HTTPC_ERROR_CONNECTION_REFUSED;
  }
}

uint8_t LineNotifyESP32::sendLineImageSPIF(HTTPClientESP32Ex &http, const String &msg, const String &filePath)
{
  return sendLineImageFile(http, msg, filePath, true);
}

uint8_t LineNotifyESP32::sendLineImageSD(HTTPClientESP32Ex &http, const String &msg, const String &filePath)
{
  return sendLineImageFile(http, msg, filePath, false);
}

bool LineNotifyESP32::sdTest()
{

  if (!SD.begin())
    return false;

  File file = SD.open(ESP32_LINE_NOTIFY_STR_43, FILE_WRITE);
  if (!file)
    return false;

  if (!file.write(32))
    return false;
  file.close();

  file = SD.open(ESP32_LINE_NOTIFY_STR_43);
  if (!file)
    return false;

  while (file.available())
  {
    if (file.read() != 32)
      return false;
  }
  file.close();

  SD.remove(ESP32_LINE_NOTIFY_STR_43);

  return true;
}

bool LineNotifyESP32::waitLineResponse(HTTPClientESP32Ex &http)
{

  std::string lineBuf = "";
  long dataTime = millis();
  char c;
  int p1, p2;

  int httpCode = -1000;
  _textLimit = 0;
  _textRemaining = 0;
  _imageLimit = 0;
  _imageRemaining = 0;

  WiFiClient *tcp = http.http_getStreamPtr();

  while (tcp->connected() && !tcp->available() && millis() - dataTime < http.tcpTimeout)
    delay(1);

  dataTime = millis();
  if (tcp->connected() && tcp->available())
  {
    while (tcp->available())
    {

      yield();

      c = tcp->read();
      lineBuf.append(1, c);

      if (c == '\n')
      {

        dataTime = millis();
        trim(lineBuf);

        p1 = lineBuf.find(ESP32_LINE_NOTIFY_STR_36);
        if (p1 != std::string::npos)
        {
          p2 = lineBuf.find(ESP32_LINE_NOTIFY_STR_37, p1 + strlen(ESP32_LINE_NOTIFY_STR_36));
          if (p2 != std::string::npos)
            httpCode = atoi(lineBuf.substr(p1 + strlen(ESP32_LINE_NOTIFY_STR_36), p2 - p1 - strlen(ESP32_LINE_NOTIFY_STR_36)).c_str());
        }
        else
        {

          p1 = lineBuf.find(ESP32_LINE_NOTIFY_STR_38);
          if (p1 != std::string::npos)
            _textLimit = atoi(lineBuf.substr(p1 + strlen(ESP32_LINE_NOTIFY_STR_38)).c_str());

          p1 = lineBuf.find(ESP32_LINE_NOTIFY_STR_39);
          if (p1 != std::string::npos)
            _imageLimit = atoi(lineBuf.substr(p1 + strlen(ESP32_LINE_NOTIFY_STR_39)).c_str());

          p1 = lineBuf.find(ESP32_LINE_NOTIFY_STR_40);
          if (p1 != std::string::npos)
            _textRemaining = atoi(lineBuf.substr(p1 + strlen(ESP32_LINE_NOTIFY_STR_40)).c_str());

          p1 = lineBuf.find(ESP32_LINE_NOTIFY_STR_41);
          if (p1 != std::string::npos)
            _imageRemaining = atoi(lineBuf.substr(p1 + strlen(ESP32_LINE_NOTIFY_STR_41)).c_str());
        }

        lineBuf.clear();
      }

      if (millis() - dataTime > http.tcpTimeout)
      {
        httpCode = HTTPC_ERROR_READ_TIMEOUT;
        break;
      }
    }
  }

  std::string().swap(lineBuf);

  return httpCode == HTTP_CODE_OK;
}

void LineNotifyESP32::getContentType(const std::string &filename, std::string &buf)
{
  int p1 = filename.find_last_of(ESP32_LINE_NOTIFY_STR_35);
  if (p1 != std::string::npos)
  {
    if (filename.find(ESP32_LINE_NOTIFY_STR_26, p1) != std::string::npos || filename.find(ESP32_LINE_NOTIFY_STR_27, p1) != std::string::npos)
    {
      buf += ESP32_LINE_NOTIFY_STR_28;
      return;
    }
    else if (filename.find(ESP32_LINE_NOTIFY_STR_29, p1) != std::string::npos)
    {
      buf += ESP32_LINE_NOTIFY_STR_30;
      return;
    }
    else if (filename.find(ESP32_LINE_NOTIFY_STR_31, p1) != std::string::npos)
    {
      buf += ESP32_LINE_NOTIFY_STR_32;
      return;
    }
    else if (filename.find(ESP32_LINE_NOTIFY_STR_33, p1) != std::string::npos)
    {
      buf += ESP32_LINE_NOTIFY_STR_34;
      return;
    }
  }
}

uint16_t LineNotifyESP32::textMessageLimit(void)
{
  return _textLimit;
}

uint16_t LineNotifyESP32::textMessageRemaining(void)
{
  return _textRemaining;
}

uint16_t LineNotifyESP32::imageMessageLimit(void)
{
  return _imageLimit;
}

uint16_t LineNotifyESP32::imageMessageRemaining(void)
{
  return _imageRemaining;
}

inline std::string LineNotifyESP32::trim(std::string &str)
{
  str.erase(0, str.find_first_not_of(' '));
  str.erase(str.find_last_not_of(' ') + 1);
  str.erase(std::remove(str.begin(), str.end(), '\r'), str.end());
  str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
  return str;
}

LineNotifyESP32 lineNotify = LineNotifyESP32();

#endif

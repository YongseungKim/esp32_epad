#include "Arduino.h"
#include "qrcode.h"
#include <Wire.h>
#include "Adafruit_EPD.h"

#define SCREEN_OFFSET_X     6
#define SCREEN_OFFSET_Y     -9
#define QRCODE_BLOCK        5
#define QRCODE_VERSION      5  
// Version 4: 33x33, max: 114,  33x5 = 99 pixel
// Version 5: 37x37, max: 154,  37*5 = 111 pixel
// Version 6: 41x41, max: 195,  41*5 = 123 pixel



#define EPD_CS 5
#define EPD_DC 17
#define SRAM_CS -1
#define EPD_RESET 16 // can set to -1 and share with microcontroller Reset!
#define EPD_BUSY 4  // can set to -1 to not use a pin (will wait a fixed delay)


// Uncomment the following line if you are using 1.54" EPD with SSD1608
// Adafruit_SSD1608 display(200, 200, EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);
// Uncomment the following line if you are using 1.54" EPD with SSD1681
Adafruit_SSD1681 display(200, 200, EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);

#define COLOR_BLACK EPD_BLACK
#define COLOR_WHITE EPD_WHITE

// Create the QR code
QRCode qrcode;

void testdrawtext(const char *text, uint16_t color);



void initTftLcd()
{
    display.begin();    
}

void drawTitle(String title){
    display.setCursor(10,25);
    display.setTextColor(COLOR_BLACK);
    display.print(title);
}

void drawQrCode(String message){
    uint8_t qrcodeData[qrcode_getBufferSize(QRCODE_VERSION)];
    // Start time
    uint32_t dt = millis();   
    qrcode_initText(&qrcode, qrcodeData, QRCODE_VERSION, 0, message.c_str());

    // Delta time
    dt = millis() - dt;

    Serial.print("QR Code Generation Time: ");
    Serial.print(dt);
    Serial.print("\n");  


    display.clearBuffer();    
    display.fillScreen(COLOR_BLACK);
    int offsetX = 20;
    int offsetY = 20;

    for (uint8_t y = 0; y < qrcode.size; y++)
    {
        offsetX = 0;
        for (uint8_t x = 0; x < qrcode.size; x++)
        {
            if (qrcode_getModule(&qrcode, x, y))
            {
                display.drawRect(SCREEN_OFFSET_X + x + offsetX, SCREEN_OFFSET_Y + y + offsetY, QRCODE_BLOCK, QRCODE_BLOCK, COLOR_WHITE);
                display.fillRect(SCREEN_OFFSET_X + x + offsetX, SCREEN_OFFSET_Y + y + offsetY, QRCODE_BLOCK, QRCODE_BLOCK, COLOR_WHITE);
            }
            
            offsetX += QRCODE_BLOCK - 1;
        }
        offsetY += QRCODE_BLOCK - 1;
    }
    display.display();
    // Bottom quiet zone
}


// void drawQrCode()
// {
//   uint8_t qrcodeData[qrcode_getBufferSize(3)];
//   qrcode_initText(&qrcode, qrcodeData, 3, 0, "HACK THE PLANET");
//   tft.fillScreen(ST77XX_WHITE);
//     int offsetX = 0;
//   int offsetY = 0;
//   for (uint8_t y = 0; y < qrcode.size; y++) {
//       offsetX = 0;
//       for (uint8_t x = 0; x < qrcode.size; x++) {
//         if (qrcode_getModule(&qrcode, x, y)){
//           tft.drawRect(SCREEN_OFFSET_X + x + offsetX, SCREEN_OFFSET_Y + y + offsetY, QRCODE_BLOCK, QRCODE_BLOCK, ST77XX_BLACK);
//           tft.fillRect(SCREEN_OFFSET_X + x + offsetX, SCREEN_OFFSET_Y + y + offsetY, QRCODE_BLOCK, QRCODE_BLOCK, ST77XX_BLACK);
//         }
//         offsetX+=QRCODE_BLOCK - 1;
//       }
//       offsetY+=QRCODE_BLOCK - 1;
//   }
// }

void testdrawtext(const char *text, uint16_t color)
{
  display.setCursor(0, 0);
  display.setTextColor(color);
  display.setTextWrap(true);
  display.print(text);
}

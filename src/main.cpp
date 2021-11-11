/***************************************************
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/
#include "Arduino.h"
#include "myQrCode.h"

String boxMsg = "https://yongseung.pythonanywhere.com/mail/reg/?b=A002-001B&p=0001&m=123456&n=홍길동";

// String boxMsg = "hello world";
void setup()
{
  Serial.begin(115200);
  //while (!Serial) { delay(10); }
  Serial.println("Adafruit EPD test");
  initTftLcd();   
  drawTitle("hello");

  delay(2000);

  drawQrCode(boxMsg);
}

void loop()
{
  //don't do anything!
}


#include <SPI.h>
#include "epd2in13b_V4.h"
#include "custom_images.h"
#include "epdpaint.h"

#define COLORED     0
#define UNCOLORED   1
unsigned char image[4000/4 + 50];

void paint() {
  // put your setup code here, to run once:
  Epd epd;

  if (epd.Init() != 0) {
    Serial.print("e-Paper init failed");
    return;
  }

  /* This clears the SRAM of the e-paper display */
  epd.ClearFrame();

  /**
    * Due to RAM not enough in Arduino UNO, a frame buffer is not allowed.
    * In this case, a smaller image buffer is allocated and you have to 
    * update a partial display several times.
    * 1 byte = 8 pixels, therefore you have to set 8*N pixels at a time.
    */
  Paint paint(image, 128, 63);    //width should be the multiple of 8

  paint.Clear(UNCOLORED);
  paint.DrawStringAt(8, 2, tagId.c_str(), &Font12, COLORED);
  
  epd.Display(image);//1
  
  paint.Clear(UNCOLORED);
  paint.DrawRectangle(2,2,50,50,COLORED);
  paint.DrawLine(2,2,50,50,COLORED);
  paint.DrawLine(2,50,50,2,COLORED);

  epd.Display(image);//2
  
  paint.Clear(UNCOLORED);
  paint.DrawCircle(25,25,20,COLORED);
  epd.Display(image);//3
  
  paint.Clear(UNCOLORED);
  epd.Display(image);//4
  
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(8, 20, tagId.c_str(), &Font12, COLORED);
  epd.Display(image);//5
  
  paint.Clear(UNCOLORED);
  paint.DrawFilledRectangle(52,2,100,50,COLORED);
  paint.DrawLine(52,2,100,50,UNCOLORED);
  paint.DrawLine(100,2,52,50,UNCOLORED);
  epd.Display(image);//6
  
  paint.Clear(UNCOLORED);
  paint.DrawFilledCircle(75,25,20,COLORED);
  epd.Display(image);//7
  
  paint.Clear(UNCOLORED);
  epd.Display(image);//8

  delay(2000);
  /* This displays an image */
  epd.DisplayFrame(stretched_people, NULL);

  /* Deep sleep */
  epd.Sleep();
}
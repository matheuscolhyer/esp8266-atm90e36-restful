
#include <SPI.h>
#include <Adafruit_GFX.h>                 // Pin connections are as follows - 
#include <Adafruit_SSD1306.h>             // (D5, D7, D3, D4, 12); 
                                          // (SCL,SDA,RES,DC, CS)

#define OLED_SDA   D7                     // MOSI
#define OLED_SCL   D5                     // CLK
#define OLED_DC    D4                     //
#define OLED_CS    12                     // no need of connecting, just use some pin number
#define OLED_RESET D3                     // RES

Adafruit_SSD1306 display(OLED_SDA,OLED_SCL, OLED_DC, OLED_RESET, OLED_CS);      
                                          // constructor to call OLED display using adafruit 
                                          // library

#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
static const unsigned char PROGMEM logo16_glcd_bmp[] =  
                                          // since i am using adafruit library, i have to 
                                          // display their logo
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };


void setup(){                
  display.begin(SSD1306_SWITCHCAPVCC);    // since i am using adafruit library, i have to 
                                          // display their logo
                                          // Init done
                                          // Show image buffer on the display hardware.
                                          // Since the buffer is intialized with an Adafruit 
                                          // splashscreen
                                          // internally, this will display the splashscreen.
  display.display();
  delay(150);
  display.clearDisplay();                 // Clear the buffer.
                                          // NOTE: You _must_ call display after making 
                                          // any drawing commands
                                          // to make them visible on the display hardware!
                                          // following OPTIONAL part is just to display 
                                          // the message only during the startup--- you can 
                                          // modify or just remove it 
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(25,11);
  display.print("Analisador DOS");
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setCursor(0,3);
  display.print("Analisando Energia usando ATM90E36 and ESP8266 NodeMCU");
  display.display();
  delay(4000);
  display.clearDisplay();
}

void displaytemp(float parametro, char unidade){  
                                                  // function to display parametro, takes 
                                                  // temperature and character C or F from 
                                                  // calling function void dispTemp(void)
  
  display.drawRect(1, 1, display.width()-1, display.height()-1, WHITE);   
                                                  
  display.setTextColor(WHITE);                    // draws the outer rectangular boundary on 
  display.setTextSize(2);                         // the screen
  display.setCursor(112,10);                      // i have white OLED display, you can use 
                                                  // other colors in case you have 
                                                  // multicolored display
  display.print(unidade);                         // Display mostra a unidade

  if(parametro >=100 || parametro < 0){           // i have reduced font size if temp goes 
    display.setTextSize(2);                       // in 3 digits or is -ve, keeps text in 
    display.setCursor(15,10);                     // center of display , it can be varied 
  }                                               // as per your taste
                                                  
  else if(parametro < 10 && parametro >= 0){      // some adjustments to keep text in center 
    display.setTextSize(3);                       // of display , it can be varied as per 
    display.setCursor(25,6);                      // your taste
  }
  else{
    display.setTextSize(3);                       // I have used large font to display 
    display.setCursor(10,6);                      // temperature, it can be varied as 
  }                                               // per your taste
  
  display.print(parametro);                       // finally prints the temperature on your 
  display.display();                              // OLED display
}

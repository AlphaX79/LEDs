#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define LED_PIN     6
#define LED_COUNT  300
#define BRIGHTNESS  200
Adafruit_NeoPixel ledy(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);


//PROTOTYPY FUNKCJI (DLA FUNKCJI O PARAMETRACH OPCJONALNYCH)
void  swiatlo_progres(uint32_t color, int wait=0,int mnoznik=1); //Argumenty (color, opoznienie(ms), mnoznik predkosci)
void wylacz(int wait,int mode,int mnoznik=1); //Argumenty ( tryb (0-nagly, 1- progresowe od tylu, 2-progresowe od przodu),opoznienie(ms),  mnoznik predkosci)
//@@@@@@@@@@@@@@@@@@@@@@@


const int buttonPin = 10; // JEZELI PIN 10 ma stan wysoki, to uruchom funkcje swiatlo_progres(), jezeli niski - wylacz()
int buttonState=0;



void setup() {


  ledy.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  ledy.show();            // Turn OFF all pixels ASAP
  ledy.setBrightness(BRIGHTNESS); // Set BRIGHTNESS to about 1/5 (max = 255)
  pinMode(buttonPin, INPUT); //PRZYDZIELENIE PINU 10 JAKO INPUT
}

void loop() {
 buttonState=digitalRead(buttonPin);
 uint32_t color = ledy.Color(0,0,0,255); //przejscie z rgbw na 32 bitowy zapis
 if(buttonState==HIGH)
 {
  swiatlo_progres(color,0,5); 
 }  
 if(buttonState==LOW)
 {
   wylacz(1,0,5);
 }
  //fala(25407); // KOLOR od 0 do 65535 -> Baleta barw HSV 

}

void  swiatlo_progres(uint32_t color, int wait,int mnoznik){
   for(int i=0; i<LED_COUNT;i++)
   {
   ledy.setPixelColor(i,color);
   if(i%mnoznik==0)ledy.show();
   delay(wait);
   }
   ledy.show();
  }

void  fala(uint16_t color){
   for(int i=0; i<256;i++) //zaswiecanie
   {
      for(int j=0;j<LED_COUNT;j++)
      {
        ledy.setPixelColor(j,ledy.ColorHSV(color,255,i));
      }
      if(i%8==0)ledy.show();
   }
   ledy.show();
   delay(2000); //czas pelnego swiatla (ms)
   for(int i=0; i<255;i++) //gaszenie 
   {
      for(int j=0;j<LED_COUNT;j++)
      {
        ledy.setPixelColor(LED_COUNT-j,ledy.ColorHSV(color,255,255-i));
      }
      if(i%8==0)ledy.show();
   }
   ledy.show();
   delay(100); //czas bez jakiegokolwiek swiatla
  }
void wylacz(int mode,int wait,int mnoznik)
{
  if(mode==1)
  {
    for(int i=0; i<=LED_COUNT;i++)
    {
      ledy.setPixelColor(LED_COUNT-i,ledy.Color(0,0,0));
      if(i%mnoznik==0)ledy.show();
      delay(wait);
    }
    ledy.show();
  }
  else if (mode==0){ledy.clear();}
  
}

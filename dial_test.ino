#include <FastLED.h>

//fast led stuff
#define LED_NUM 8
#define DATA_PIN 5
int led_index;
#define BRIGHT_LOW  20
#define BRIGHT_HIGH 100
CRGB colors[3] = {CRGB::Blue, CRGB::Red, CRGB::Green};
int color_index;
CRGB leds[LED_NUM];
//rotary encoder stuff
#define PIN_A 4
#define PIN_B 2
#define PIN_S 3
int a, b, last_a;

long int timer;
long int io_timer;

int switch_state;

void setup() 
{ 
    Serial.begin(9600);
    
    pinMode(PIN_A, INPUT);
    pinMode(PIN_B, INPUT);

    pinMode(PIN_S, INPUT);

    last_a = LOW;

    switch_state = LOW;

    FastLED.addLeds<SK6812, DATA_PIN, GRB>(leds, LED_NUM);
    
    led_index = 0;
    color_index = 0;

    timer = millis();
    io_timer = millis();

    set_color();
    set_brightness(BRIGHT_HIGH);

    Serial.println("Setup Complete");
}

void loop() 
{ 
  //waiting
      //set all leds to bright_low
    //wait for input  
  switch_state = digitalRead(PIN_S);
  if((switch_state == HIGH) && (millis() - timer > 200))
  {
    Serial.println("Button Pressed");
    set_color();
    timer = millis();
    switch_state = LOW;
  }
  
  
  //button press
  //all leds color = next color

  //rotary encoder
   
}

void set_color()
{
  if(color_index++ >= 3)
  {
      color_index = 0;
  }
  for(int i = 0; i < LED_NUM; i++)
  {
    leds[i] = colors[color_index];
  }
  FastLED.show();
}
void set_brightness(int num)
{
  FastLED.setBrightness(num);
  FastLED.show();
}
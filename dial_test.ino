#include <FastLED.h>

//fast led stuff
#define LED_NUM 8
#define DATA_PIN 5
int led_index;
#define BRIGHT_LOW  20
#define BRIGHT_HIGH 255

#define DIMMER_RATE 300

int colors[3] = {160, 96, 0};
int color_index;
int hues[1] = {255};
int hue_index = 0;
int bright_index;
CRGB leds[LED_NUM];
//rotary encoder stuff
#define PIN_A 4
#define PIN_B 2
#define PIN_S 3
int a, b, last_a;

long int timer;
long int io_timer;
long int dimmer_timer;

int switch_state;

void setup() 
{ 
    Serial.begin(9600);
    
    pinMode(PIN_A, INPUT);
    pinMode(PIN_B, INPUT);

    pinMode(PIN_S, INPUT);

    last_a = digitalRead(PIN_A);

    switch_state = LOW;

    FastLED.addLeds<SK6812, DATA_PIN, GRB>(leds, LED_NUM);
    FastLED.show();
    led_index = 0;
    color_index = 0;

    timer = millis();
    io_timer = millis();

    //set_brightness(BRIGHT_HIGH);
    
    Serial.println("Setup Complete");
}

void loop() 
{ 
  //rotary encoder
  a = digitalRead(PIN_A);
  if((a != last_a) && a == HIGH)
  {
    b = digitalRead(PIN_B);
    if(b != a)
    {
      //ccw
      Serial.println("CCW");

      led_index = (--led_index < 0) ? LED_NUM : led_index;
      Serial.println(led_index);
      mode_bright(led_index);
    }
    else
    {
      //cw
      Serial.println("CW");
      led_index = (++led_index >= LED_NUM) ? 0 : led_index;
      mode_bright(led_index);  
    }
    timer = millis();
  }
  last_a = a;  
  
  //re button
  if((digitalRead(PIN_S) == HIGH) && (millis() - timer > 250))
  {
    Serial.println("Button Pressed");
    set_color();
    timer = millis();
  }
  
  //reset to full brightness after action
  if(millis() - timer > 500)
  {
    bright_index = 255;
    set_brightness(bright_index);
  }
  //dimmer
  
  
}
void set_brightness(int bright)
{
  hsv2rgb_rainbow(CHSV(colors[color_index], hues[hue_index], bright), leds[0]); 
  set_all();
}
void set_all()
{
  fill_solid(leds, LED_NUM, leds[0]);
  FastLED.show();
}
void mode_bright(int start)
{
  //first one stays full brightness while others are subtracted
  hsv2rgb_rainbow(CHSV(colors[color_index], 255, 255), leds[start]); 
  int next, prev;
  for(int i = 1; i < (LED_NUM/2); i++)
  {
    if((next = start + i) >= LED_NUM)
    {
      next = i - (LED_NUM - start);
    }
    if((prev = start - i) < 0)
    {
      prev = LED_NUM - (i - start);
    }
    //if(start + i >= LED_NUM)
    int bright = 255/(2*i);
    hsv2rgb_rainbow(CHSV(colors[color_index], 255, bright), leds[next]); 
    hsv2rgb_rainbow(CHSV(colors[color_index], 255, bright), leds[prev]); 
  }
  if(LED_NUM%2 == 0)
  {
    //fadeLightBy(leds[start 
  }
  FastLED.show();
}
void set_color()
{
  Serial.println(color_index);
  if(++color_index >= 3)
  {
      color_index = 0;
  }
  //fill_solid(&leds, LED_NUM,  
  hsv2rgb_rainbow(CHSV(colors[color_index], 255, 255), leds[0]);
  set_all();
}
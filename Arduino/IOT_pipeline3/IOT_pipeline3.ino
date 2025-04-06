#include <LiquidCrystal_I2C.h>

#include  <Wire.h>

int l1=2, l2=3, l3=4, l4=5, l5=6;
int water_sensor = 8;
bool water_state = 0;

LiquidCrystal_I2C lcd(0x27,  20, 4);
String texts[4];

void setup()
{
  lcd.init();
  lcd.backlight();
  pinMode(l1, OUTPUT);
  pinMode(l2, OUTPUT);
  pinMode(l3, OUTPUT);
  pinMode(l4, OUTPUT);
  pinMode(l5, OUTPUT);
  pinMode(water_sensor, INPUT);
  Serial.begin(9600);
}

void loop()
{
  // LED
  if (Serial.available() > 0){
  	String request = Serial.readStringUntil('\n');
    request.trim();
    int separatorIndex = request.indexOf(":");
    if (separatorIndex != -1){
    	String label = request.substring(0, separatorIndex + 1); 
        String value = request.substring(separatorIndex + 1);
      
      	label.trim(); 
        value.trim();
      	label.toLowerCase();
      	
      if (label == "led:"){
        value.toLowerCase();
      	identify_led(value);
      } else if (label == "text:") {
        String text = value.substring(0, 20);
        add_text(text);
        print_texts_lcd();
      } else if (label == "get:") {
        value.toLowerCase();
        if (value == "texts") {
          send_texts_as_json();
        } 
      }
    }
  }

  // Water Sensor
  int water = digitalRead(water_sensor);
  if (water && !water_state) {
    Serial.println("Water Status: 1");
    water_state = !water_state;
  } else if (!water && water_state) {
    Serial.println("Water Status: 0");
    water_state = !water_state;
  }

}

void identify_led(String led){
  if (led == "l1"){
  	switch_led(l1);
  }
  else if (led == "l2"){
  	switch_led(l2);
  }
  else if (led == "l3"){
  	switch_led(l3);
  }
  else if (led == "l4"){
    switch_led(l4);
  }
  else if (led == "l5"){
  	switch_led(l5);
  } else {
  	Serial.println("invalid input");
  }
}


void switch_led(int led_pin){
  if (digitalRead(led_pin) == LOW){
  	digitalWrite(led_pin, HIGH);
  } else {
  	digitalWrite(led_pin, LOW);
  }
}

void add_text(String text) {
  texts[0] = texts[1];
  texts[1] = texts[2];
  texts[2] = texts[3];
  texts[3] = text;
}

void print_texts_lcd() {
  lcd.setCursor(0,0);
  lcd.print("                    ");
  lcd.setCursor(0,0);
  lcd.print(texts[0]);

  lcd.setCursor(0,1);
  lcd.print("                    ");
  lcd.setCursor(0,1);
  lcd.print(texts[1]);

  lcd.setCursor(0,2);
  lcd.print("                    ");
  lcd.setCursor(0,2);
  lcd.print(texts[2]);

  lcd.setCursor(0,3);
  lcd.print("                    ");
  lcd.setCursor(0,3);
  lcd.print(texts[3]);
}


void send_texts_as_json(){
  String json = "{\"texts\": [";
  for (int i = 0; i<4; i++){
    json += "\"" + texts[i] + "\"";
    if (i<3){
      json += ",";
    }
  }
  json += "]}";

  Serial.println(json);
}


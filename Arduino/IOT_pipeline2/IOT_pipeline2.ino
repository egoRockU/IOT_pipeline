int l1=2, l2=3, l3=4, l4=5, l5=6;
int water_sensor = 8;
bool water_state = 0;

void setup()
{
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
      	value.toLowerCase();
      	
      if (label == "led:"){
      	identify_led(value);
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

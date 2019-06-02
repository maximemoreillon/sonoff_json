void IO_setup(){

  Serial.println(F("[IO] IO initialization"));
  
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);

  // Initial state
  if(strcmp(relay_state,"ON") == 0) {
    turn_relay_on();
  }
  else {
    turn_relay_off();
  }
}

void turn_relay_on(){
  
  Serial.println(F("[IO] Turning Relay ON"));
  
  relay_state = "ON";
  
  // Send new state my MQTT
  MQTT_publish_state();

  // Update content of web page
  ws_update_state();
  
  long time_delta = millis() - off_time;
  if(time_delta < BACK_ON_MIN_PAUSE) {
    Serial.println(F("[IO] waiting before turning back on"));
    delay(BACK_ON_MIN_PAUSE - time_delta);
  }
  
  digitalWrite(RELAY_PIN, HIGH);
  digitalWrite(LED_PIN, LOW); // LED is active LOW
  
}

void turn_relay_off(){
  Serial.println(F("[IO] Turning Relay OFF"));
  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(LED_PIN, HIGH); // LED is active LOW
  relay_state = "OFF";
  off_time = millis();
  
  // Send new state my MQTT
  MQTT_publish_state();

  // Update content of web page
  ws_update_state();
}

void toggle_relay(){
  Serial.println(F("[IO] Toggling relay state"));
  if(strcmp(relay_state,"OFF") == 0){
    turn_relay_on();
  }
  else if(strcmp(relay_state,"ON") == 0){
    turn_relay_off();
  }
}

void read_button() {
  
  const long button_debounce_delay = 50;
  static int last_button_reading;
  static long last_button_reading_change_time;
  static int button_state = LOW; // Output
  
  int button_reading = digitalRead(BUTTON_PIN);

  // Check if reading changed
  if(button_reading != last_button_reading) {
    // Acknowledge button reading change
    last_button_reading = button_reading;
    
    // Record time of last button reading change
    last_button_reading_change_time = millis();
  }

  // Only acknowledge the button reading if state did not change for long enough
  if(millis()-last_button_reading_change_time > button_debounce_delay) {
    
    if(button_reading != button_state) {
      
      // Save reading as button state if state and reading don't match (prevents saving all the time)
      button_state = button_reading;

      // APPLICATION DEPENDENT FROM HERE
      if(button_state == LOW) {
        
        Serial.println(F("[IO] Button pressed"));

        // Toggle_relay state
        toggle_relay();        
      }
    }
  }
}

#include <Event.h>
#include <Timer.h>

#include <NewPing.h>
#include <AFMotor.h>
#include "Definition.h"



unsigned int move_range = 100; // 10 for test; 100 for use
unsigned long g_interval = 10*1000; 

Timer t;

void setup() {
  setup_serial();
  setup_motors;
  int tickEvent = t.every(2000, update_alarm);
}
void loop() {
  
  //alarm = is_alarm(); // if alarm return 1; else return 0
  alarm = 1;
  while (!alarm){  // alarm == 0, no alarm
    //print_sonar();
    Serial.println("Random Mode");
    print_human_sensor();
    //Serial.println("No alarm, run randomly");
    random_run();
    delay(move_range);   
    t.update();
  }
  
  unsigned long lastMill = millis();
  Serial.println(lastMill);
  
  while (alarm){ // alarm == 1, alarm!
    //print_sonar();
    Serial.println("Home Mode");
    print_human_sensor();
    //Serial.println("Alarm! go home puppy!");
    command = get_command();
    Serial.println(command);
    Serial.println(command == 'F');
    go_home(command);
    //delay(10); // delay 100 ms
    //alarm = is_alarm(); // update alarm
    unsigned long currentMill = millis();
    
    Serial.println("currentMill - LastMill: ");
    Serial.println(currentMill - lastMill);
    
    if (currentMill - lastMill < g_interval) alarm = 1;
    else alarm = 0;
    
  }
  //delay(1000);
}


  


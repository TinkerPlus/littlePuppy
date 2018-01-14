#include <NewPing.h>
#include <AFMotor.h>
#include "Definition.h"

void setup() {
  setup_serial();
  setup_motors;
}
void loop() {
  
  //alarm = is_alarm(); // if alarm return 1; else return 0
  alarm = 1;
  
  while (!alarm){  // alarm == 0, no alarm.
    //print_sonar();
    //print_human_sensor();
    //Serial.println("No alarm, run randomly");
    random_run();
    //alarm = is_alarm(); // update alarm.
    delay(1000); 
  }
  while (alarm){ // alarm == 1, alarm!
    //print_sonar();
    //print_human_sensor();
    //Serial.println("Alarm! go home puppy!");
    command = get_command();
    Serial.println(command);
    Serial.println(command == 'F');
    go_home(command);
    delay(100); // delay 100 ms
    //alarm = is_alarm(); // update alarm
  }
  //delay(1000);
}


  


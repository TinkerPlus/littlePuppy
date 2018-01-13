#include <NewPing.h>
#include <AFMotor.h>
#include "Definition.h"

void setup() {
  setup_serial();
  setup_motors;
}
void loop() {
  print_sonar();
  print_human_sensor();
  command =get_command();
  go_home(command); 
  delay(1000);
}


  


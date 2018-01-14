#include <AFMotor.h>

AF_DCMotor motoryou(3);//右轮马达接到m3上
AF_DCMotor motorzuo(4);//左轮马达接到m4上
void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");

  // turn on motor
  motorzuo.setSpeed(200);
  motoryou.setSpeed(200);
 
  motorzuo.run(RELEASE);
  motoryou.run(RELEASE);
}
void forward(uint8_t,uint8_t);//前进函数
void backward(uint8_t,uint8_t);//后退函数
void leftturn(uint8_t,uint8_t);//左转函数
void rightturn(uint8_t,uint8_t);//右转函数
void nowstop(uint8_t);//刹车即不动函数
void loop() {
<<<<<<< HEAD
  
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
=======
  uint8_t spd=200;
  uint8_t tim=200;
  forward(spd,tim);
  backward(spd,tim);
  leftturn(spd,tim);
  rightturn(spd,tim);
  nowstop(tim);
}
void forward(uint8_t spd=200,uint8_t tim=20)
{
  motorzuo.run(BACKWARD);
  motoryou.run(BACKWARD); 
  motorzuo.setSpeed(spd);    
  motoryou.setSpeed(spd); 
  delay(100*tim);
}
void backward(uint8_t spd=200,uint8_t tim=20)
{
  motorzuo.run(FORWARD);
  motoryou.run(FORWARD);
  motorzuo.setSpeed(spd);    
  motoryou.setSpeed(spd); 
  delay(100*tim);
}
void leftturn(uint8_t spd=200,uint8_t tim=20)
{
  motorzuo.run(FORWARD);
  motoryou.run(BACKWARD); 
  motorzuo.setSpeed(spd);    
  motoryou.setSpeed(spd); 
  delay(100*tim);
}
void rightturn(uint8_t spd=200,uint8_t tim=20)
{
  motoryou.run(FORWARD);
  motorzuo.run(BACKWARD); 
  motorzuo.setSpeed(spd);    
  motoryou.setSpeed(spd); 
  delay(100*tim);
}
void nowstop(uint8_t tim=20)
{
  motorzuo.run(RELEASE);
  motoryou.run(RELEASE); 
  delay(100*tim);
>>>>>>> 54ebe06ca523aed88c258ac47c15c11c16d67e2a
}


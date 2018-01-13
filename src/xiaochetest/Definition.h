#include <AFMotor.h>
#include <NewPing.h>


//prepare process
#define TRIGGER_PIN 14 // mean A0
#define ECHO_PIN 15 //mean A1
#define MAX_DISTANCE 200
#define HUMAN_PIN A2 // human sensor
#define bool int  // define type bool

// define some values
uint8_t spd=200;
uint8_t tim=20;
char command;

// initialize some instances
AF_DCMotor motoryou(3);//右轮马达接到m3上
AF_DCMotor motorzuo(4);//左轮马达接到m4上
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);// NewPing setup of pins
 
// define function header
void forward(uint8_t,uint8_t);//前进函数
void backward(uint8_t,uint8_t);//后退函数
void leftturn(uint8_t,uint8_t);//左转函数
void rightturn(uint8_t,uint8_t);//右转函数
void nowstop(uint8_t);//刹车即不动函数
void random_run(uint8_t, uint8_t); //random run without command from raspberrypi
bool is_danger(); // if puppy is too close to something
bool is_alarm();  // if people is close.
void print_sonar();
char get_command();
void random_run();
void setup_serial();
void setup_motors();

// funciton body
void setup_serial(){
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");
}
void setup_motors(){
    // turn on motor
  motorzuo.setSpeed(200);
  motoryou.setSpeed(200);
  motorzuo.run(RELEASE);
  motoryou.run(RELEASE);
}
void forward(uint8_t spd=200,uint8_t tim=20){
  if(is_danger()){
    leftturn(spd, tim);
    Serial.println("danger! turn left");
  }
  else{
    Serial.println("No danger, move forward");
    motorzuo.run(BACKWARD);
    motoryou.run(BACKWARD); 
    motorzuo.setSpeed(spd);    
    motoryou.setSpeed(spd); 
    delay(100*tim);
  }
}
void backward(uint8_t spd=200,uint8_t tim=20){
  motorzuo.run(FORWARD);
  motoryou.run(FORWARD);
  motorzuo.setSpeed(spd);    
  motoryou.setSpeed(spd); 
  delay(100*tim);
}
void leftturn(uint8_t spd=200,uint8_t tim=20){
  motorzuo.run(FORWARD);
  motoryou.run(BACKWARD); 
  motorzuo.setSpeed(spd);    
  motoryou.setSpeed(spd); 
  delay(100*tim);
}

void rightturn(uint8_t spd=200,uint8_t tim=20){
  motoryou.run(FORWARD);
  motorzuo.run(BACKWARD); 
  motorzuo.setSpeed(spd);    
  motoryou.setSpeed(spd); 
  delay(100*tim);
}

void nowstop(uint8_t tim=20){
  motorzuo.run(RELEASE);
  motoryou.run(RELEASE); 
  delay(100*tim);
}

bool is_danger(){
  if(sonar.ping_cm()<10)
    return 1;
  else
    return 0;
}

bool is_alarm(){
  int l_human_sensor = analogRead(HUMAN_PIN);
  if (l_human_sensor = 1023) return 1;
  else return 0;
}

void print_sonar(){
    Serial.print("Ping: ");
    Serial.print(sonar.ping_cm());
    Serial.println("cm");
}

void print_human_sensor(){
  Serial.print("Human sensor: ");
  Serial.println(analogRead(HUMAN_PIN));
}

char get_command(){
  char l_command; // l for local value
  if (Serial.available() > 0){
    l_command = Serial.read(); //p for paremeter
  }
  return l_command;
}
  
void go_home(char p_command){   //p for paremeter
  switch(p_command){
    case('L'): { leftturn(spd, tim); break;}
    case('R'): { rightturn(spd, tim); break;}
    case('F'): { forward(spd, tim); break;}
    case('B'): { backward(spd, tim); break;}
    case('S'): { nowstop(tim); break;}
    default: Serial.println("waiting for command");
  }
}



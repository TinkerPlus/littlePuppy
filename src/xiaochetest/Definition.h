#include <AFMotor.h>
#include <NewPing.h>


//prepare process
#define TRIGGER_PIN 14 // mean A0
#define ECHO_PIN 15 //mean A1
#define MAX_DISTANCE 200
#define HUMAN_PIN A2 // human sensor
//#define bool int  // define type bool

// define some values
uint8_t g_spd=200;  // g for global
uint8_t g_turn_spd = 150;
uint8_t g_tim=1; //1000 ms
uint8_t g_turn_tim = 1; //100 ms
char command = ' ';
bool alarm = 0;
bool danger = 0;
//long l_randNumer = -1; // for random run



// initialize some instances
AF_DCMotor motoryou(4);//右轮马达接到m3上
AF_DCMotor motorzuo(3);//左轮马达接到m4上
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);// NewPing setup of pins
 
 
 
 
 
// define function header

//// setup 
void setup_serial();
void setup_motors();
//// movement
void forward(uint8_t,uint8_t);//前进函数
void backward(uint8_t,uint8_t);//后退函数
void leftturn(uint8_t,uint8_t);//左转函数
void rightturn(uint8_t,uint8_t);//右转函数
void nowstop(uint8_t);//刹车即不动函数
void random_run(); //random run without command from raspberrypi
void go_home(char p_command);
//// sensor 
bool is_danger(); // if puppy is too close to something
bool is_alarm();  // if people is close.
//// communication
char get_command();
//// debug
void print_sonar();
void print_human_sensor();

// funciton body

//// setup
void setup_serial(){
  Serial.begin(115200);           
  Serial.println("Motor test!");
}
void setup_motors(){
  motorzuo.setSpeed(200);
  motoryou.setSpeed(200);
  motorzuo.run(RELEASE);
  motoryou.run(RELEASE);
}

//// movements
void forward(uint8_t p_spd=200,uint8_t p_tim=20){ // p for paremeter
    //Serial.println("No danger, move forward");
  motorzuo.run(BACKWARD);
  motoryou.run(BACKWARD); 
  motorzuo.setSpeed(p_spd + 30);   
  motoryou.setSpeed(p_spd);  
  delay(10*p_tim);
}
void backward(uint8_t p_spd=200,uint8_t p_tim=20){
  motorzuo.run(FORWARD);
  motoryou.run(FORWARD);
  motorzuo.setSpeed(p_spd + 20);    
  motoryou.setSpeed(p_spd); 
  delay(10*p_tim);
}
void leftturn(uint8_t p_turn_spd=200,uint8_t p_tim=20){
  motorzuo.run(FORWARD);
  motoryou.run(BACKWARD); 
  motorzuo.setSpeed(p_turn_spd);    
  motoryou.setSpeed(p_turn_spd); 
  delay(10*p_tim);
}
void rightturn(uint8_t p_turn_spd=200,uint8_t p_tim=20){
  motoryou.run(FORWARD);
  motorzuo.run(BACKWARD);
  motorzuo.setSpeed(p_turn_spd);    
  motoryou.setSpeed(p_turn_spd); 
  delay(10*p_tim);
}
void nowstop(uint8_t p_tim=20){
  motorzuo.run(RELEASE);
  motoryou.run(RELEASE); 
  delay(10*p_tim);
}
void random_run(){
  randomSeed(digitalRead(10));
  /* get a random num (0, 1, 2, 3, 4)
  switch case(num)
  0 for stop
  1 for forward
  2 for leftturn
  3 for rightturn
  4 for backward  */
  long l_randNumber = random(0,7); // l for local
  //Serial.print("Random number: ");
  //Serial.println(l_randNumber);
  long l_rand_spd = random(100, 300);
  long l_rand_tim = random(0, 20);
  Serial.println(l_rand_tim);
  Serial.println(l_rand_spd);
  switch(l_randNumber){
    case(0):{nowstop(); Serial.println("random num 0, stop");break;}  
    case(1):{forward(l_rand_spd, l_rand_tim);Serial.println("random num 1, forward"); break;}
    case(2):{forward(l_rand_spd, l_rand_tim);Serial.println("random num 1, forward"); break;}
    case(3):{leftturn(l_rand_spd, l_rand_tim);Serial.println("random num 2, leftturn"); break;} 
    case(4):{rightturn(l_rand_spd, l_rand_tim);Serial.println("random num 3, rightturn"); break;}   
    case(5):{backward(l_rand_spd, l_rand_tim);Serial.println("random num 4, backward"); break;}
    case(6):{backward(l_rand_spd, l_rand_tim);Serial.println("random num 4, backward"); break;}
  }
}
void go_home(char p_command){   //p for paremeter
  uint8_t l_turn_spd = 150;
  uint8_t l_spd = 200;
  uint8_t l_turn_tim = 2;  //40 ms
  uint8_t l_stop_tim = 2;
  
  switch(p_command){
    case('L'): { 
      leftturn(l_turn_spd, l_turn_tim);
      //rightturn(l_turn_spd, l_turn_tim);
      nowstop(l_stop_tim);
      break;
    }
    case('R'): { rightturn(l_turn_spd, l_turn_tim); /*nowstop(l_stop_tim);*/  break;}
    case('F'): { forward(g_spd, g_tim*100); break;}
    case('B'): { backward(g_spd, g_tim); break;}
    case('S'): { nowstop(g_tim); break;}
    //case('S'): { nowstop(tim); break;}
    //default: Serial.println("waiting for command");
  }
}

//// sensor
bool is_danger(){
  if(sonar.ping_cm()<10)
    return 1;
  else
    return 0;
}
bool is_alarm(){
  int alarmArrayNum = 3;
  int sensorArray[alarmArrayNum];
  for (int i=0; i<alarmArrayNum; i++){
    sensorArray[i] = analogRead(HUMAN_PIN);
  }
  //Serial.println(l_human_sensor);
  int res = 0;
  for (int i=0; i<alarmArrayNum; i++){
    if(sensorArray[i]==1023) res++;
  }
  if (res == alarmArrayNum) return 1;
  else return 0;
}
void update_alarm(){
  nowstop(10);
  alarm = is_alarm();
  nowstop(3);
}


//// communication
char get_command(){
  //char l_command = ' '; // l for local value
  if (Serial.available() > 0){
    command = Serial.read(); //p for paremeter
    Serial.print("Serial read: ");
    Serial.println(command);
  }
  return command;
}
//// debug
void print_sonar(){
  Serial.print("Ping: ");
  Serial.print(sonar.ping_cm());
  Serial.println("cm");
}
void print_human_sensor(){
  Serial.print("Human sensor: ");
  Serial.println(analogRead(HUMAN_PIN));
}

  



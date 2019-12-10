#include <virtuabotixRTC.h>
#include <Servo.h>

#define ACTIVE 10

#define TIME 1000
#define HOUR 0
#define POR 4


Servo servo;
//________________CLK,DAT,RST
virtuabotixRTC clock(8,7,6);

int schSize = 2;
int schedule[] = {600,1800};
int scheduleP[] = {5,3};
boolean scheduleF[] = {false,false};

int pulseTime = 500;

void setup(){
  
  Serial.begin(9600);
  //___SERVO PIN 9
  servo.attach(9);
  pinMode(ACTIVE,OUTPUT);

  writeSchedule();
  delay(1000);
  
  
}
  
void loop(){
  clock.updateTime();
  resetSchedule(); 
  loopSchedule();
  
  if(Serial.available()){
    String myBuffer = Serial.readString();    
      switch(myBuffer.charAt(0)){
          case 'P':
            pulse(1,pulseTime);
          break;
          case 'T':
            long value = (long)myBuffer.substring(1).toInt();
            updateClockTime((long)myBuffer.substring(1).toInt());
          break;
        }
  }
  delay(500);
}




int readTimeFormat(){
    return (clock.hours*100) + clock.minutes;
}

void loopSchedule(){
   for(int k = 0 ; k < schSize  ; k++){
      if(readTimeFormat() == schedule[k] && !scheduleF[k]){
          pulse(scheduleP[k],pulseTime);
          scheduleF[k] = true; 
      }
   }
}

void writeSchedule(){
   String mainBuffer = "";
    for(int k = 0 ; k < schSize ; k++){
      String subBuffer = "$F" + String(scheduleF[k]) + "T" + String(schedule[k]) + "P" + String(scheduleP[k]);
      mainBuffer += subBuffer;  
    }
    Serial.println(mainBuffer);
}

void resetSchedule(){
  if(readTimeFormat() == 0000){
    for(boolean flag : scheduleF){
      flag = false;  
    }
  }
}

void pulse(int n,int time){
  digitalWrite(ACTIVE,HIGH);
  for(int i = 0 ; i < n ; i++){
    servo.write(0);
    delay(time);
    servo.write(90);
    delay(time);
  }
  digitalWrite(ACTIVE,LOW);
}

void updateClockTime(long value){
    //h x 10000
    //m x 100
    //s x 1
    int h = value/10000;
    int m = (value - (long)h*10000)/100;
    int s = (value - (((long)h*10000)+m*100));
    //ss/mm/hh/dW/dM/mm/yyyy
    clock.setDS1302Time(s,m,h,1,0,0,0);
}

#include <Wire.h>
#define NXT 0x03  
volatile byte buf[8];
byte light[8];
char cmps[3];
byte I2Cbyte;  
int temp;
//*************************************************************************  
void setup()  
{
  Serial.begin(115200);  
  Wire.begin(0x03);                // join i2c bus with dev address 0x03
  Wire.onRequest(requestEvent); // register event
  Wire.onReceive(receiveData);
  pinMode(12, OUTPUT);
  digitalWrite(12,HIGH);
}  

//*************************************************************************  
  
void requestEvent() { 
  Wire.write(light,8);       
}

void receiveData(int byteCount)
{
  for(byte i = 0; i<byteCount;i++){
    buf[i] = Wire.read();   
  }
    
}
//*************************************************************************

void loop()  
{
  temp = analogRead(A0);
  if(temp>700){light[4]=255;}
  else{light[4]=map(temp,200,700,0,255);}
  
  temp = analogRead(A2);
  if(temp>700){light[3]=255;}
  else{light[3]=map(temp,200,700,0,255);}
  
  temp = analogRead(A6);
  if(temp>780){light[2]=255;}
  else{light[2]=map(temp,280,780,0,255);}
  
  temp = analogRead(A1);
  if(temp>750){light[1]=255;}
  else{light[1]=map(temp,250,750,0,255);}
  
  temp = analogRead(A3);
  if(temp>690){light[0]=255;}
  else{light[0]=map(temp,190,690,0,255);}
  
  Serial.write(1);
  if (Serial.available() > 4) {
    cmps[0] = Serial.read();
    cmps[1] = Serial.read();
    cmps[2] = Serial.read();
    light[6] = Serial.read();  
  }
  light[5] = cmps[1]; //pitch
  light[7] = cmps[0]; //angle
  //light[5] = 10;
  /*for(int i=0;i<5;i++){
    Serial.print(light[i]);
    Serial.print(" ");
  }
  Serial.println(" ");*/
}    

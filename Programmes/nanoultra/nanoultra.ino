#include <Wire.h>
#include <NewPing.h> 
#define TRIGGER_PIN  3
#define ECHO_PIN     2
#define MAX_DISTANCE 150
#define CMPS11 0x60  // Address of CMPS11 shifted right one bit for arduino wire library
#define ANGLE_8  1           // Register to read 8bit angle from
char cmps[3];
int test;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
void setup()
{
  Serial.begin(115200);  // Start serial port
  Wire.begin();
  delay(5);
  
} 


void CMPS(){
  unsigned char high_byte, low_byte, angle8;
  char pitch, roll, angle;
  unsigned int angle16;  
  Wire.beginTransmission(CMPS11);
  Wire.write(ANGLE_8);
  Wire.endTransmission();
  Wire.requestFrom(CMPS11,5);
  angle8 = Wire.read();               // Read back the 5 bytes
  high_byte = Wire.read();
  low_byte = Wire.read();
  pitch = Wire.read();
  roll = Wire.read();  
  angle16 = high_byte;                 // Calculate 16 bit angle
  angle16 <<= 8;
  angle16 += low_byte;
  angle = angle16/15-128; //plus 128 and mulltiply 15 on nxt
  cmps[0] = angle;
  cmps[1] = pitch;
  cmps[2] = roll;
 }

void loop(){
  CMPS();
  /*for(int i=0;i<3;i++){
    Serial.print(cmps[i]);
    Serial.print(" ",DEC);
  }
  Serial.println(" ");*/
  int X = sonar.ping_cm();
  if(Serial.available()) {
    int test = Serial.read();
    Serial.write(cmps[0]);
    Serial.write(cmps[1]);
    Serial.write(cmps[2]);
    Serial.write(lowByte(X));
    } 
}
 

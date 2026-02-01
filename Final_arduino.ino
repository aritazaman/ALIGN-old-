#include <Wire.h>

#include <MPU6050.h>

 

MPU6050 imu;

 

// change this number later to tune sensitivity

int SLOUCH_THRESHOLD = 15000;

 

void setup() {
  Serial.begin(9600);
  Wire.begin();

  imu.initialize();

  // Wake up the MPU6050
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  Serial.println(imu.testConnection() ? "MPU OK" : "MPU FAIL");

  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
}
 

void loop() {

  int16_t ax, ay, az;

  imu.getAcceleration(&ax, &ay, &az);

  // Serial.print("AY: ");
  // Serial.println(ay);

  
 

  // ay = forward/back tilt

  if (ay < 14500) {

    // GOOD posture → GREEN

    digitalWrite(4, LOW);

    digitalWrite(3, HIGH);

    Serial.println("SLOUCH");
  } else if (ay < 15500) {
    
    analogWrite(4, 75);

    digitalWrite(3, HIGH);
    Serial.println("GOOD");


  } else {

    // SLOUCHING → RED

    digitalWrite(4, HIGH);

    digitalWrite(3, LOW);
    Serial.println("GOOD");


  }

 

  delay(200);

}

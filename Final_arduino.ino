#include <Wire.h>

#include <MPU6050.h>

 

MPU6050 imu;

 

// tune this later

int SLOUCH_THRESHOLD = 14500;

 

void setup() {

  Serial.begin(9600);

  Wire.begin();

 

  imu.initialize();

 

  // Wake up MPU6050

  Wire.beginTransmission(0x68);

  Wire.write(0x6B);

  Wire.write(0);

  Wire.endTransmission(true);

 

  Serial.println(imu.testConnection() ? "MPU OK" : "MPU FAIL");

 

  pinMode(3, OUTPUT); // RED

  pinMode(4, OUTPUT); // GREEN

  pinMode(5, OUTPUT); // BLUE (unused for now)

  pinMode(6, OUTPUT); // VIBRATION

}

 

void loop() {

  int16_t ax, ay, az;

  imu.getAcceleration(&ax, &ay, &az);

 

 

  if (ay < 14500) {

    //  SLOUCHING

    digitalWrite(4, LOW);   // GREEN OFF

    digitalWrite(3, HIGH);  // RED ON

    digitalWrite(6, HIGH);  // VIBRATION ON

    Serial.println("SLOUCH");

 

  } else {

    //  GOOD POSTURE

    digitalWrite(4, HIGH);  // GREEN ON

    digitalWrite(3, LOW);   // RED OFF

    digitalWrite(6, LOW);   // VIBRATION OFF

    Serial.println("GOOD");

  }

 

  delay(200);

}

#include <Wire.h>

#define SLAVE_ADDRESS 0x04

int state = 0;
double temp;

int index = 0;

const char pinWritings[] = {2, 3, 4, 5, 6, 7, 8, 9};
int cmd = 0;

const char pinReadings[] = {A0, A1, A2, A3};
typedef struct {
  //byte address;
  int values[4];
} data;
data d;

void setup() {
  int i;
  //initialize all the pins for the Relays
  for (int i = 0; i < sizeof(pinWritings); i++)
  {
    pinMode(pinWritings[i], OUTPUT);
  }

  //d.address = SLAVE_ADDRESS;
  //d.address = byte(0x31);
  //initialize all the pins for the Relays
  for (int i = 0; i < sizeof(pinReadings); i++)
  {
    d.values[i] = 0x31 + i;
  }

  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  // initialize i2c as slave
  Wire.begin(SLAVE_ADDRESS);

  // define callbacks for i2c communication
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
  Serial.println("Ready!");
}

void loop() {
  delay(100);
  GetAnalog();
  //sendData();
}

// callback for received data
void receiveData(int byteCount) {

  while (Wire.available()) {
    cmd =  Wire.read();
    Serial.print("data received: ");
    Serial.println(cmd);
    setGPIO(cmd);
  }
}

// callback for sending data
void sendData() {
  int count;
  count = Wire.write((byte *)&d, sizeof(d));
  //Wire.send((uint8_t *)&var1, sizeof(var1));
  //Wire.send((uint8_t *)arr1, sizeof(arr1));
  //Wire.send((uint8_t *)&data, sizeof(data));
  Serial.print("Sensors ");
  Serial.print(" send: ");
  Serial.write((byte *)&d, sizeof(d));
  Serial.print(" count: ");
  Serial.println(count);
  /*
  int i;
  for (i = 0; i < sizeof(pinReadings); i++)
  {
    Wire.write(byte(readings[i]));
    Serial.print("Sensor ");
    Serial.print(i);
    Serial.print(" send: ");
    Serial.println(byte(readings[i]));
  }
  */
}

//Get the value of sensors for A0 to A3
void GetAnalog(void)
{
  int i = 0;
  for (i; i < sizeof(pinReadings); i++)
  {
    d.values[i] =  0xFF + i;//analogRead(pinReadings[i]);
    // apply the calibration to the sensor reading
    //d.values[i] = map(d.values[i], 0, 1023, 0, 255);
    // in case the sensor value is outside the range seen during calibration
    //d.values[i] = constrain(d.values[i], 0, 255);
    Serial.print("sensor ");
    Serial.print(i);
    Serial.print(" detected: ");
    Serial.println(d.values[i]);
    delay(1000);
  }
}

void setGPIO(int cmd)
{
  Serial.print(" Get command: ");
  Serial.println(cmd, BIN);
  int i;
  for (i = 0; i < sizeof(pinWritings); i = i + 1)
  {
    digitalWrite(pinWritings[i], (1 << i & cmd) >> i);
    Serial.print("Pin ");
    Serial.print(i);
    Serial.print(" setted: ");
    Serial.println((1 << i & cmd) >> i, BIN);
  }
}


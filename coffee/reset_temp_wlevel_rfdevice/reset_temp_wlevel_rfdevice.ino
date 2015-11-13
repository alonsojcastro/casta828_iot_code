#include <RFduinoGZLL.h>

#include <OneWire.h> 

device_t role = DEVICE2;

// pin for the Green Led
int LEDpin = 2;
int xpin = 2;
int xval = 0;

int DS18B20_Pin = 4; //DS18B20 Signal pin on digital 4

//Temperature chip i/o
OneWire ds(DS18B20_Pin); // on digital pin 4

const int sensorPin= 5;
int liquid_level;

double x;

void setup()
{
  Serial.begin(9600);
  pinMode(LEDpin, OUTPUT);
  pinMode(xpin, INPUT);
  pinMode(sensorPin, INPUT);//the liquid level sensor will be an input to the arduino
  RFduinoGZLL.txPowerLevel = 0;
  // start the GZLL stack
  RFduinoGZLL.begin(role);
}

void loop(){
  float temperature = getTemp();
  
  char xdata[2];   //declaring character array
  char mydata[16];
  String xstr;
  String mystr;

  xval = digitalRead(xpin);

  liquid_level= analogRead(sensorPin); //arduino reads the value from the liquid level sensor

//  xval = 0;
  xstr = String(xval);

  xstr.toCharArray(xdata, 2); //passing the value of the string to the character array
  mystr = "r" + xstr +","+String(int(temperature))+","+String(liquid_level);
  mystr.toCharArray(mydata, 16);
  Serial.println(mydata);
//  Serial.println(temperature);
//  Serial.println(liquid_level);//prints out liquid level sensor reading
  delay(100);//delays 100ms

  RFduinoGZLL.sendToHost(mydata, 16);
  delay(100);
}

float getTemp(){
 //returns the temperature from one DS18B20 in DEG Celsius

 byte data[12];
 byte addr[8];

 if ( !ds.search(addr)) {
   //no more sensors on chain, reset search
   ds.reset_search();
   return -1000;
 }

 if ( OneWire::crc8( addr, 7) != addr[7]) {
   Serial.println("CRC is not valid!");
   return -1000;
 }

 if ( addr[0] != 0x10 && addr[0] != 0x28) {
   Serial.print("Device is not recognized");
   return -1000;
 }

 ds.reset();
 ds.select(addr);
 ds.write(0x44,1); // start conversion, with parasite power on at the end

 byte present = ds.reset();
 ds.select(addr);  
 ds.write(0xBE); // Read Scratchpad

 
 for (int i = 0; i < 9; i++) { // we need 9 bytes
  data[i] = ds.read();
 }
 
 ds.reset_search();
 
 byte MSB = data[1];
 byte LSB = data[0];

 float tempRead = ((MSB << 8) | LSB); //using two's compliment
 float TemperatureSum = tempRead / 16;
 
 return TemperatureSum;
 
}

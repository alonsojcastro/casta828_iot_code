
#include <RFduinoGZLL.h>

device_t role = HOST;
char state = 0;
int LEDpin1 = 2; //green
int LEDpin2 = 4; //yellow
int LEDpin3 = 6; //red

void setup()
{
  Serial.begin(9600);
  pinMode(LEDpin1, OUTPUT);
  pinMode(LEDpin2, OUTPUT);
  pinMode(LEDpin3, OUTPUT);
  // start the GZLL stack
  RFduinoGZLL.begin(role);
}

void loop()
{
  //  digitalWrite(LEDpin,HIGH);

}

void on() {
  digitalWrite(LEDpin1, HIGH);
  digitalWrite(LEDpin2, HIGH);
  digitalWrite(LEDpin3, HIGH);
}
void off() {
  digitalWrite(LEDpin1, LOW);
  digitalWrite(LEDpin2, LOW);
  digitalWrite(LEDpin3, LOW);
}

void RFduinoGZLL_onReceive(device_t device, int rssi, char *data, int len)
{
  


  if (data[0] == 97) {
    digitalWrite(LEDpin1, (data[1]-48)); 
  }else if (data[0] == 98) {
    digitalWrite(LEDpin2, (data[1]-48));
  }else if (data[0] == 99) {
    digitalWrite(LEDpin3, (data[1]-48));
  }
  else{
    off();
  }
}

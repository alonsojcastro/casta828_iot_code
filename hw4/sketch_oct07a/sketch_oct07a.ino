#include <RFduinoGZLL.h>

/*
button-rfdevice_1.ino
 */
device_t role = DEVICE2;

// pin for the Green Led
int LEDpin = 6;
int xpin = 2;
int ypin = 4;
int xval = 0;
int yval = 1;
int xvalp = 0;
int yvalp = 1;
double x;
double y;


void setup()
{
  Serial.begin(9600);
  pinMode(LEDpin, OUTPUT);
  pinMode(xpin, INPUT);
  pinMode(ypin, INPUT);
  RFduinoGZLL.txPowerLevel = 0;
  // start the GZLL stack
  RFduinoGZLL.begin(role);
}

void loop()
{
  char xdata[2];   //declaring character array
  char ydata[4];
  char mydata[2];
  char myydata[4];
  String xstr;
  String ystr;
  String mystr;
  String myystr;

  xval = digitalRead(xpin);
  yval = digitalRead(ypin);

//  xval = 0;
// yval = 1;
  xstr = String(xval);
  ystr = String(yval);

  xstr.toCharArray(xdata, 2); //passing the value of the string to the character array
  mystr = xstr;
  mystr.toCharArray(mydata, 2);
  Serial.println(mydata);
  RFduinoGZLL.sendToHost(mydata, 2);
  delay(50);

  ystr.toCharArray(ydata, 4); //passing the value of the string to the character array
  myystr = ystr;
  myystr.toCharArray(myydata, 4);
  Serial.println(myydata);
  RFduinoGZLL.sendToHost(myydata, 4);
  delay(50);  
}

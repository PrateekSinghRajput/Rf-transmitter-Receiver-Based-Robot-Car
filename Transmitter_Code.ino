//Prateek
//www.prateeks.in

// Robot Transmitter programming
#include <VirtualWire.h>
const int transmit_pin = 12;

String str;
char cstr[100];
String message = "";
unsigned int mlength; // message length

// for joystick
int flag = 0;
int buttonf = 0;
int power = 7;
int button = 4;
int vrx = A2;
int vry = A1;

int xdata = 0;
int ydata = 0;
void setup()
{
  // Initialise the IO and ISR
  vw_set_tx_pin(transmit_pin);
  vw_setup(2000);       // Bits per sec
  Serial.begin(9600);

  pinMode(vrx, INPUT);
  pinMode(vry, INPUT);
  pinMode(power, OUTPUT);
  digitalWrite(power, HIGH);

  pinMode(button, INPUT);
  digitalWrite(button , HIGH);
}

void loop()
{
  control();

  if ( buttonf == 1)
  {
    xdata = analogRead(vrx);
    ydata = analogRead(vry);
    SendData(xdata, ydata, buttonf);
    //delay(100);
  }

  if (buttonf == 0)
  {
    SendData(0, 0, 0); // send 0 to the receiver.
    delay(100);
  }

}


void SendData( int xvalue, int yvalue, int buttonstatus)
{

  message = message + xvalue + "," + yvalue + "," + buttonstatus ;
  mlength = message.length(); // find the number of characters in a message.
  str = message;
  str.toCharArray(cstr, 100);
  vw_send((uint8_t *)cstr, mlength); //
  vw_wait_tx(); // Wait until the whole message is gone
  str = "";
  message = "";

}


void control()
{
  if (( digitalRead(button) == LOW ) && (buttonf == 0))
  {

    Serial.println(" Started");
    buttonf = 1;
    delay(1000);

  }

  if (( digitalRead(button) == LOW ) && (buttonf == 1))
  {

    Serial.println("ended");
    buttonf = 0;
    delay(1000);
  }
  digitalWrite(button , HIGH);
}

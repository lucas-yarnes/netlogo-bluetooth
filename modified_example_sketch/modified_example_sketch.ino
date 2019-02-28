#include <IRremote.h>
#include <IRremoteInt.h>

int counter = 0;    //we'll send this counter value over the Serial port to be read by NetLogo
int ledPin = 13;    //pin 13, which has an associated onboard LED
int ir_pin = 10;    //pin 10, which has an IR sensor connected

IRrecv receiver(ir_pin);
decode_results results;

void setup() {
  //start listening to the serial port at 9600 bps,
  //the baud rate expected by NetLogo's Arduino extension
  Serial.begin(9600);

  //does what it says...
  receiver.enableIRIn();

  //set up the LED pin to act as an output
  pinMode(ledPin, OUTPUT);
}

void loop() {

  if(receiver.decode(&results)) {
    switch(results.value) {
      case 0x338: //red
        Serial.print("IR,");
        Serial.print("S,");
        Serial.print("red");
        Serial.print(";");
        break;
      case 0xB38: //green
        Serial.print("IR,");
        Serial.print("S,");
        Serial.print("green");
        Serial.print(";");
        break;
      case 0x738: //yellow
        Serial.print("IR,");
        Serial.print("S,");
        Serial.print("yellow");
        Serial.print(";");
        break;
      case 0xF38: //blue
        Serial.print("IR,");
        Serial.print("S,");
        Serial.print("blue");
        Serial.print(";");
        break;
      case 0xA70: //center select
        Serial.print("IR,");
        Serial.print("S,");
        Serial.print("select");
        Serial.print(";");
        break;
      case 0x410: //3
        Serial.print("NUM,");
        Serial.print("D,");
        Serial.print("3");
        Serial.print(";");
        break;
      case 0xC10: //4
        Serial.print("NUM,");
        Serial.print("D,");
        Serial.print("4");
        Serial.print(";");
        break;
      case 0x210: //5
        Serial.print("NUM,");
        Serial.print("D,");
        Serial.print("5");
        Serial.print(";");
        break;
      case 0xA10: //6
        Serial.print("NUM,");
        Serial.print("D,");
        Serial.print("6");
        Serial.print(";");
        break;
      case 0x610: //7
        Serial.print("NUM,");
        Serial.print("D,");
        Serial.print("7");
        Serial.print(";");
        break;
      case 0xE10: //8
        Serial.print("NUM,");
        Serial.print("D,");
        Serial.print("8");
        Serial.print(";");
        break;
      case 0x110: //9
        Serial.print("NUM,");
        Serial.print("D,");
        Serial.print("9");
        Serial.print(";");
        break;
      default:
        Serial.print("IR,");
        Serial.print("S,");
        Serial.print("Button not yet defined");
        Serial.print(";");
        break;
    }
    delay(200);
    receiver.resume();
  }

  /*if (counter >= 100) {
    counter = 0;
  }
  counter++;

  //Write out our counter value
  Serial.print("C,");    // send a value named "C"       
  Serial.print("D,");    // specify it is a numeric ("Double") value
  Serial.print(counter);
  Serial.print(";");

  //Create and write out a random number from 0 to 10, with two digits of decimals.
  double rnum = random(1000) / 100.0;
  Serial.print("R,");         // send a value named "R"
  Serial.print("D,");         // specify it is a numeric ("Double") value
  Serial.print(rnum, 2);      // sending 2 digit accuracy
  Serial.print(";");

  Serial.print("GAME,");      // send a value named "GAME"
  Serial.print("S,");         // specify it is a String value
  if (counter % 3 != 2) {     // play a fun game
    Serial.print("DUCK");
  } else {
    Serial.print("GOOSE");
  }
  Serial.print(";");*/

  if (Serial.available() > 0) {
    int cmd = Serial.read();
    if (cmd == 48 || cmd == 0) {        //0 or ascii "0" sent with write-string
      digitalWrite(ledPin, LOW);        //turn the onboard LED associated with pin 13 off
    } else if (cmd == 49 || cmd == 1) { //1 or ascii "1" sent with write-string
      digitalWrite(ledPin, HIGH);       //turn the onboard LED associated with pin 13 on
    }
  }

  delay(300);  //1/5 second delay --> this could be removed or adjusted for more or less frequent cycles.
}

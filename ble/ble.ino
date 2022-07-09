#define BtPower 2
#define BtState A0
#include <SoftwareSerial.h>
SoftwareSerial mySerial(3, 5); // RX, TX

short interval = 0;
String Hold;

void setup() {
  // put your setup code here, to run once:
 pinMode(BtPower, OUTPUT);
 pinMode(BtState, INPUT);
 
 digitalWrite(BtPower, 1); // Turn on the bluetooth module
 
 Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  mySerial.begin(9600);
  delay(100);
}

void loop() {
  
 State();         //Query the state of the bluetooth module
 if (interval < 20){      // check if the state pin has not been "High" for over 1 sec
  Serial.println("NOT CONNECTED");   // Print message to the serial monitor
 }

 else if (interval >= 20){      // check if the state pin has been "High" for over 1 sec
  Serial.println("CONNECTED !!");       // Print message to the serial monitor
  mySerial.write("111111111111111111111111111111111111234");        // Send data via the bluetooth module to mobile phone.
 
 while (interval >= 20){        // Do the following while the state pin has been high for over 1 sec
  if (mySerial.available()) {         // check if there is a data sent from the mobile phone.
    
    while (mySerial.available() > 0){       // Do the following while there is still data in the buffer
        Hold += (char)mySerial.read();      // Read each recieved character and save them in a string
        delay(20);                          // Wait for 20 milliseconds.
      }
//    Hold.remove((Hold.length() - 2), 2);     // Uncomment this line if the recieved data ends with jargons.
      
      Serial.println(Hold);       // Print the recieved data on the serial monitor
      Hold = "";                  // Empty the space and get set for another incoing data
  }
  if (Serial.available()) {       // check if there is a message from the serial monitor
    mySerial.write(Serial.read());      // Send the message to the mobile phone via the bluetooth module
  }
  State();        //Query the state of the bluetooth module
 }
 
}
}

short State(){
  delay(50);
 if (digitalRead(BtState) == 1){
  interval += 1;
 }
 else if (digitalRead(BtState) == 0){
  interval = 0;
 }
}

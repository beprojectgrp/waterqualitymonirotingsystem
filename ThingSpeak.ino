
// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;
// defines variables
long duration;
int distance; 
String apiKey = "73L38IZ1WUHVE3E0";  //Change this key to your "Write API key"


void setup() {
  // put your setup code here, to run once: 
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(115200); // Starts the serial communication
  Serial.begin(115200);   // Arduino to ESP01 Communication
  connectWiFi();           // To connect to Wifi
 } 

void loop() { 
  // put your main code here, to run repeatedly:
  // Clears the trigPin
digitalWrite(trigPin, LOW);

delayMicroseconds(100);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);

delayMicroseconds(100);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance

distance= duration*0.034/2;   //(timeXspeedOfSound/2) 0.034=speedofsound of ultra, 2=formula for ultra cuz it travels and echo backs.

// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
if(distance>=199){
Serial.print("LOW");
}
else if(distance>=99){
Serial.print("Medium");
}
else if(distance>=25)
{
Serial.print("HIGH");
}
else{
 Serial.print("OVERFLOW"); 
}

  Serial.println("AT+CIPMUX=0\r\n");      // To Set MUX = 0
  delay(2000);                             // Wait for 2 sec

  // TCP connection 
  String cmd = "AT+CIPSTART=\"TCP\",\"";   // TCP connection with https://thingspeak.com server
  cmd += "184.106.153.149";                // IP addr of api.thingspeak.com
  cmd += "\",80\r\n\r\n";                  // Port No. = 80

  Serial.println(cmd);                    // Display above Command on PC
  Serial.println(cmd);                     // Send above command to Rx1, Tx1

  delay(20000);                            // Wait for 20 Sec

  if(Serial.find("ERROR"))                // If returns error in TCP connection
  { 
    Serial.println("AT+CIPSTART error");   // Display error msg to PC
    //return; 
  }

  // prepare GET string 
  String getStr = "GET /update?api_key=";   
  getStr += apiKey;
  getStr +="&field1=";
  getStr += distance; 
  getStr += "\r\n\r\n"; 

  Serial.println(getStr);                 // Display GET String on PC

  cmd = "AT+CIPSEND=";                    // send data length 
  cmd += String(getStr.length());
  cmd+="\r\n";

  Serial.println(cmd);                   // Display Data length on PC
  Serial.println(cmd);                  // Send Data length command to Tx1, Rx1
  
  delay(20000);                          // wait for 20sec

  if(Serial.find(">"))                    // If prompt opens //verify connection with cloud
  {
    Serial.println("connected to Cloud");  // Display confirmation msg to PC
    Serial.print(getStr);                 // Send GET String to Rx1, Tx1
  }
  else
  { 
    Serial.println("AT+CIPCLOSE\r\n");    // Send Close Connection command to Rx1, Tx1
    Serial.println("AT+CIPCLOSE");         // Display Connection closed command on PC
  } 
  
  // thingspeak free version needs 16 sec delay between updates 
  delay(16000);                            // wait for 16sec

 }

boolean connectWiFi() {               // Connect to Wifi Function
  Serial.println("AT+CWMODE=1\r\n"); // Setting Mode = 1 
  delay(100);                         // wait for 100 mSec

  String cmd = "AT+CWJAP=\"";         // Connect to WiFi
  cmd += "Arduino";                   // ssid_name
  cmd += "\",\"";
  cmd += "arduino123";                // password
  cmd += "\"\r\n";              
  
  Serial.println(cmd);                // Display Connect Wifi Command on PC
  Serial.println(cmd);               // send Connect WiFi command to Rx1, Tx1 
  
  delay(10000);                       // wait for 10 sec

  Serial.println("AT+CWJAP?");       // Verify Connected WiFi

  if(Serial.find("+CWJAP"))        
  {
    Serial.println("OK, Connected to WiFi.");         // Display Confirmation msg on PC
    return true;
  }
  else
  {
    Serial.println("Can not connect to the WiFi.");   // Display Error msg on PC
    return false;
  }
}

          // defines pins numbers
const int trigPin = 9;
const int echoPin = 10;
// defines variables
long duration;
int distance;
void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication
}
void loop() {
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

}

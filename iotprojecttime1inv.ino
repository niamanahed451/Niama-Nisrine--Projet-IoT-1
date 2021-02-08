// Load Wi-Fi library
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

//liaison firebase

#define FIREBASE_HOST "feurouge-4823b-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "K3YmNKJ2giPZYhKODsz32MNminZEJD2k7Wk9DqM6"

//Replace with your network credentials
const char* ssid     = "Salle VIP2";
const char* password = "VIP11VIP";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String ledrState = "off";
String ledvState = "off";
String ledoState = "off";

// Assign output variables to GPIO pins
const int ledr11 = 16;
const int ledv11 = 5;
const int ledo11 = 4;

const int ledr12 = 14;
const int ledv12 = 12;
const int ledo12 = 13;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(ledr11, OUTPUT);
  pinMode(ledv11, OUTPUT);
  pinMode(ledo11, OUTPUT);

   pinMode(ledr12, OUTPUT);
  pinMode(ledv12, OUTPUT);
  pinMode(ledo12, OUTPUT);

  // Set outputs to LOW
  digitalWrite(ledr11, LOW);
  digitalWrite(ledv11, LOW);
  digitalWrite(ledo11, LOW);

  digitalWrite(ledr12, LOW);
  digitalWrite(ledv12, LOW);
  digitalWrite(ledo12, LOW);
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

}

void loop(){
WiFiClient client = server.available();   // Listen for incoming clients

String redState = Firebase.getString("/Leds/Rouge");
String vertState = Firebase.getString("/Leds/Vert");
String orangeState = Firebase.getString("/Leds/Orange");
if (Firebase.failed()) {
      Serial.print("setting /message failed:");
      Serial.println(Firebase.error()); 
      return;
  }
if (Firebase.getString("/Leds/Rouge")== "on"){
while(true){
  digitalWrite(ledv11, HIGH);
  digitalWrite(ledv12, HIGH);
  Firebase.setString("/Leds/Vertinv", "on");
  digitalWrite(ledo11, LOW);
  digitalWrite(ledo12, LOW);
  Firebase.setString("/Leds/Orangeinv", "off");
  digitalWrite(ledr11, LOW);
  digitalWrite(ledr12, LOW);
  Firebase.setString("/Leds/Rougeinv", "off");
  delay(10000);

  
  digitalWrite(ledo11, HIGH);
  digitalWrite(ledo12, HIGH);
  Firebase.setString("/Leds/Orangeinv", "on");
  digitalWrite(ledr11, LOW);
  digitalWrite(ledr12, LOW);
  Firebase.setString("/Leds/Rougeinv", "off");
  digitalWrite(ledv11, LOW);
  digitalWrite(ledv12, LOW);
  Firebase.setString("/Leds/Vertinv", "off");
  delay(10000);

  digitalWrite(ledr11, HIGH);
  digitalWrite(ledr12, HIGH);
  Firebase.setString("/Leds/Rougeinv", "on");
  digitalWrite(ledv11, LOW);
  digitalWrite(ledv12, LOW);
  Firebase.setString("/Leds/Vertinv", "off");
  digitalWrite(ledo11, LOW);
  digitalWrite(ledo12, LOW);
  Firebase.setString("/Leds/Orangeinv", "off");
  delay(10000);
}
}

}

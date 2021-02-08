
// Declaration des LED
 
int LEDr1 = 16 ; //GPIO 16
int LEDo1 = 5;   //GPIO 5
int LEDv1 = 4;   //GPIO 4

int Bp2 = 0;

int buttonStateBp2 = 0; 

void setup() {
  
  pinMode(LEDr1, OUTPUT);
  pinMode(LEDo1, OUTPUT);
  pinMode(LEDv1, OUTPUT);

  Serial.begin(9600);
  
//Buttons
 
  pinMode(Bp2, INPUT);

}

void loop() {



  //rouge
  Serial.println("Feu1 Rouge");
  digitalWrite( LEDr1, HIGH);
  digitalWrite( LEDo1, LOW);
  digitalWrite( LEDv1, LOW);
  
  delay(30000);
  
// Orange  
 Serial.println("Feu1 Orange");
  digitalWrite( LEDr1, LOW);
  digitalWrite( LEDo1, HIGH);
  digitalWrite( LEDv1, LOW);
  
  delay(2000);


  //vert 

  Serial.println("Feu1 Vert");
  digitalWrite( LEDr1, LOW);
  digitalWrite( LEDo1, LOW);
  digitalWrite( LEDv1, HIGH);
  
  buttonStateBp2 = digitalRead(Bp2);
   if (buttonStateBp2 == HIGH) {
      delay(15000);
  } else {
      delay(30000);
  }




}


int val;// saves value of hall effect sensor
int avgVal;
int buttonone;
int newval;
int minValueChange=50;
int b1=2,b2=3,b3=4,b4=5,bsj=6;
void setup() {
  Serial.begin(9600);// opens serial port, sets data rate to 9600 bps
  attachInterrupt(digitalPinToInterrupt(b1),buttonPressed,RISING);
  pinMode (b2, INPUT);
  pinMode (b3, INPUT);
  pinMode (b4, INPUT);
  pinMode (bsj, INPUT);
}
void buttonPressed(){
  if (digitalRead(b1) == HIGH) {
  } else {
    Serial.println("button 1 clicked");                 
  }                
}

void loop() {
  newval=analogRead(A0);
  if (newval>val+minValueChange||newval<val-minValueChange){
      val = analogRead(A0);    // read the value from the sensor
      Serial.println(val);  
  }
        
}

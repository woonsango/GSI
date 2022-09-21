#define PIN_LED 7

unsigned int count ;

void setup() {
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, HIGH);
  count = 5 ;

}

void loop() {
  digitalWrite(PIN_LED, LOW);
  delay(1000);
  digitalWrite(PIN_LED, HIGH);
  while(count>0){
    delay(100);
    digitalWrite(PIN_LED,LOW);
    delay(100);
    digitalWrite(PIN_LED,HIGH);
    --count;
  }
  while(1){
    digitalWrite(PIN_LED,HIGH);
  }
  
}

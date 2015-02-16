byte i[5] = {
  B1101111, B1110111, B1111011, B1111101, B1111110};
byte j[7] = {
  B1000000, B0100000, B0010000, B0001000, B0000100, B0000010, B0000001};
int iMatriz;
int jMatriz;
boolean estado=0;
int pinLatch=6;
int pinReloj=9;
int pinDatos=5;
//millis
long tiempoIni=0, tiempoFin;
//SWITCHS
const int switch1Pin = 2;
const int switch2Pin = 3;
int switch1State = 0;
int switch2State = 0;
// RGB
const int ledPinR = 6;
const int ledPinG = 9;
const int ledPinB = 5;
int buzzerPin = 10;
//LDR
int LDRPin=A0;
int valorLDRini;
int LDRvalue=0;
// LM35
int LMPin=A1;
int LMvalue=0;
int valorLMini;
int temperatura=0;
// Joystick
int xjoyPin=A5;
int yjoyPin=A4;
int sjoyPin=13;
int xjoyValue=0;
int yjoyValue=0;
int sjoyValue=0;
// Acelerometer
int xacelPin=A2;
int yacelPin=A3;
int xacelValue=0;
int yacelValue=0;
//Distance Sensor
int trigPin=11;
int echoPin=12;
int distancia;
String zumbador;
String rgb;
String ldr;
String acelerometro;
String distance;
String lm35;
void setup() {
  attachInterrupt(0, salir ,RISING);
  // initialize the LED pin as an output:
  pinMode(ledPinR, OUTPUT);
  pinMode(ledPinG, OUTPUT);
  pinMode(ledPinB, OUTPUT);
  pinMode(pinLatch, OUTPUT);
  pinMode(pinDatos, OUTPUT);
  pinMode(pinReloj, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(switch1Pin, INPUT);
  pinMode(switch2Pin, INPUT);
  pinMode(sjoyPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  Serial.println("======Probando el LED RGB======");
  Serial.println("ASEGURESE DE TENER EL CONMUTADOR EN LA POSICION DEL LED RGB");
  Serial.println("Si puede ver la sucesion de colores(Rojo, Azul, Verde) pulse el boton derecho.");
  Serial.println(" De no ser asi, pulse el boton izquierdo");
  while(switch2State == LOW && switch1State == LOW){
    digitalWrite(ledPinG, LOW);
    digitalWrite(ledPinR, HIGH);
    tiempoIni=millis();
    while(tiempoFin-tiempoIni<500){
      tiempoFin=millis();
      switch2State=digitalRead(switch2Pin);
      if(switch2State == HIGH || switch1State == HIGH){
        break;
      }
    }
    if(switch2State == HIGH || switch1State == HIGH){
      break;
    }
    digitalWrite(ledPinR, LOW);
    digitalWrite(ledPinB, HIGH);
    tiempoIni=millis();
    while(tiempoFin-tiempoIni<500){
      tiempoFin=millis();
      switch2State=digitalRead(switch2Pin);
      if(switch2State == HIGH || switch1State == HIGH){
        break;
      }
    }
    if(switch2State == HIGH || switch1State == HIGH){
      break;
    }
    digitalWrite(ledPinB, LOW);
    digitalWrite(ledPinG, HIGH);
    tiempoIni=millis();
    while(tiempoFin-tiempoIni<500){
      tiempoFin=millis();
      switch2State=digitalRead(switch2Pin);
      if(switch2State == HIGH || switch1State == HIGH){
        break;
      }
    }
    if(switch2State == HIGH || switch1State == HIGH){
      break;
    }
  }
  digitalWrite(ledPinG, LOW);
  digitalWrite(ledPinR, LOW);
  digitalWrite(ledPinB, LOW);
  if(switch1State == HIGH){
    rgb = "#El LED RGB no funciona correctamente";
  }
  else{
    rgb ="#El LED RGB funciona correctamente";
  }
  while(switch2State == HIGH || switch1State == HIGH){
    switch1State=digitalRead(switch1Pin);
    switch2State=digitalRead(switch2Pin);
  }
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  Serial.println("======Probando el zumbador======");
  digitalWrite(buzzerPin, HIGH);
  delay(500);
  digitalWrite(buzzerPin, LOW);
  Serial.println("Si ha escuchado el pitido pulse el boton derecho.");
  Serial.println(" De no ser asi, pulse el boton izquierdo");
  while(switch2State == LOW && switch1State == LOW){
    switch2State=digitalRead(switch2Pin);
  }
  if(switch1State == HIGH){
    zumbador = "#El zumbador no funciona correctamente";
  }
  else{
    zumbador ="#El zumbador funciona correctamente";
  }
  while(switch2State == HIGH || switch1State == HIGH){
    switch1State=digitalRead(switch1Pin);
    switch2State=digitalRead(switch2Pin);
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  Serial.println("======Probando la LDR======");
  valorLDRini=analogRead(LDRPin);
  Serial.println("Tape el sensor LDR con la mano");
  LDRvalue=valorLDRini;
  Serial.println("Si no se detecta cambio en el sensor, pulse el boton izquierdo");
  switch1State=digitalRead(switch1Pin);
  while(valorLDRini-LDRvalue < 100 && switch1State == LOW){
    LDRvalue=analogRead(LDRPin);
  }
  if(switch1State == HIGH){
    ldr ="#El LDR no funciona correctamente";
  }
  else{
    ldr ="#El LDR funciona correctamente";
  }
  while(switch1State == HIGH){
    switch1State=digitalRead(switch1Pin);
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  Serial.println("======Probando la SENSOR DISTANCIA======");
  Serial.println("Mida la distancia del ancho de un folio A4");
  Serial.println("Si no se detecta cambio en el sensor, pulse el boton izquierdo");
  while((distancia < 17 || distancia > 23 )&& switch1State == LOW){
    digitalWrite(trigPin,LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    distancia=pulseIn(echoPin, HIGH);
    distancia = (0.017*distancia);
  }
  if(switch1State == HIGH){
    distance="#El sensor de distancia no funciona correctamente";
  }
  else{
    distance="#El sensor de distancia funciona correctamente";
  }
  while(switch1State == HIGH){
    switch1State=digitalRead(switch1Pin);
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  Serial.println("======Probando la LM35======");
  Serial.println("Suba la tempertura del sensor");
  Serial.println("Si no se detecta cambio en el sensor, pulse el boton izquierdo");
  valorLMini=analogRead(A1);
  valorLMini=0;
  valorLMini=analogRead(A1);
  while(LMvalue-valorLMini < 7 && switch1State == LOW){
    LMvalue=analogRead(LMPin);
  }
  if(switch1State == HIGH){
    lm35 ="#El LM35 no funciona correctamente";
  }
  else{
    lm35 ="#El LM35 funciona correctamente";
  }
  while(switch1State == HIGH){
    switch1State=digitalRead(switch1Pin);
  }
  Serial.println();
  Serial.println("Resultado final de la prueba: ");
  Serial.println(rgb);
  delay(10);
  Serial.println(zumbador);
  delay(10);
  Serial.println(ldr);
  delay(10);
  Serial.println(distance);
  delay(10);
  Serial.println(lm35);
  Serial.println("");
  Serial.println("======Por ultimo comprueba que el punto en la matriz se mueve acuerdo al joystic o acelerometro======");
  Serial.println("ASEGURESE DE TENER EL CONMUTADOR EN LA POSICION DE LA MATRIZ DE LED");
  Serial.println("Para cambiar entre acelerometro y joystic usa el boton izquierdo");
}
void loop(){
  if(switch1State==HIGH){
    estado=!estado;
    if(estado==1){
      Serial.println("Esta usando: ACELEROMETRO");
    }
    if(estado==0){
      Serial.println("Esta usando: JOYSTICK");
    }
    delay(500);
    switch1State=digitalRead(switch1Pin);
  }
  if(estado==0){
    xjoyValue=analogRead(xjoyPin);
    yjoyValue=analogRead(yjoyPin);
    iMatriz=((1024-xjoyValue)/160);
    jMatriz=(yjoyValue/120);
  }
  if(estado==1){
    xacelValue=analogRead(xacelPin);
    yacelValue=analogRead(yacelPin);
    iMatriz=((yacelValue-210)/40);
    jMatriz=((300-(xacelValue-210))/42);
  }
  if(iMatriz>5){
    iMatriz=5;
  }
  if(iMatriz<2){
    iMatriz=1;
  }
  if(jMatriz>7){
    jMatriz=7;
  }
  if(jMatriz<1){
    jMatriz=1;
  }
  digitalWrite(pinLatch, LOW);
  shiftOut(pinDatos, pinReloj, MSBFIRST, i[iMatriz-1]);
  shiftOut(pinDatos, pinReloj, MSBFIRST, j[jMatriz-1]);
  digitalWrite(pinLatch, HIGH);
}
void salir(){
  switch1State=HIGH;
}


const int ledR = 25;
const int ledG = 26;
const int ledB = 27;

const int trigPin = 14;
const int echoPin = 13;

bool objIdent = false;
unsigned long tempoInicio = 0;

void setColor(int R, int G, int B){
  analogWrite(ledR, R);
  analogWrite(ledG, G);
  analogWrite(ledB, B);
}

void setup(){
  Serial.begin(115200);

  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duracao = pulseIn(echoPin, HIGH, 30000);

  float distancia = duracao * 0.034 / 2;

  //Serial.println(distancia);

  if(distancia < 10){
    setColor(255, 0, 0);
    objIdent = false;
    //Serial.println(0);
  } else if (distancia < 30 && objIdent == false) {
    setColor(255, 255, 0);
    //Serial.println(1);
    objIdent = true;
    tempoInicio = millis();
  } else  if(distancia >= 30 && objIdent == true){
    setColor(0, 255, 0);
    long int tempoFim = millis();
    long int diferenca = tempoFim - tempoInicio;
    float vTempo = (float)diferenca / 1000;
    float velocidade = 10 / vTempo;

    Serial.println(tempoInicio);
    Serial.println(tempoFim);
    Serial.println(diferenca);
    Serial.println(vTempo, 6);

    Serial.print(velocidade, 6);
    Serial.println(" cm/s");

    objIdent = false;
  }

  
/*
  if(objIdent = false) {
    setColor(255, 0, 0);
  }

  if(distancia <= 10 && objIdent == false){
    objIdent = true;
    tempoInicio = millis();
    Serial.println("Objeto Identificado!");
    setColor(255, 255, 0);
  }

  if(distancia > 10 && objIdent == true){
    unsigned long duracao = millis() - tempoInicio;

    Serial.print("Duração de passagem: ");
    Serial.print(duracao);
    Serial.println(" ms");

    setColor(0, 255, 0);
    delay(1000);

    objIdent = false;
  }*/
  delay(500);
}
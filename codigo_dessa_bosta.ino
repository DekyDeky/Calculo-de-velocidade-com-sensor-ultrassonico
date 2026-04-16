  const int ledR = 25;
  const int ledG = 26;
  const int ledB = 27;
  
  const int trigPin = 14;
  const int echoPin = 13;

  float duracao, distancia = 0.0, ultimaDistancia = 0.0, difeDistancia;
  unsigned long tempoAtual = 0.0, ultimoTempo = 0.0;

  void setup() {
    
    Serial.begin(115200);
    
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    pinMode(ledR, OUTPUT);
    pinMode(ledG, OUTPUT);
    pinMode(ledB, OUTPUT);

  }

const unsigned long intervalo = 100; // ms

void loop() {
  tempoAtual = millis();
  float difeTempo = tempoAtual - ultimoTempo;

  if (difeTempo >= intervalo) {

    distancia = lerDistanciaFiltrada();

    float difeTempo = intervalo / 1000.0; // FIXO

    difeDistancia = distancia - ultimaDistancia;

    float velocidade = (difeDistancia / difeTempo) / 100;

    float velocidadeABS = abs(velocidade); 

    if(velocidadeABS < .75){
      setColor(0, 255, 0);
    }else if(velocidadeABS < 1.75){
      setColor(255, 255, 0);
    }else {
      setColor(255, 0, 0);
    }

    Serial.println(velocidade);

    ultimaDistancia = distancia;
    ultimoTempo = tempoAtual;
  }
}

  float lerDistanciaFiltrada() {
    float soma = 0;
    int n = 5;

    for(int i=0; i<n; i++){
      digitalWrite(trigPin, LOW);
      delayMicroseconds(5);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);

      long duracao = pulseIn(echoPin, HIGH, 30000);
      float d = duracao * 0.034 / 2;

      soma += d;
      delay(10);
    }

    return soma / n;
  }

  void setColor(int R, int G, int B){
    analogWrite(ledR, R);
    analogWrite(ledG, G);
    analogWrite(ledB, B);
  }
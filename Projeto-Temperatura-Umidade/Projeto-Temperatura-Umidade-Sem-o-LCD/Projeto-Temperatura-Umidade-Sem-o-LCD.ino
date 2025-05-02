#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <TimerOne.h>
#include <DHT_U.h>

#define DHTPIN 7 //Pino conectado ao DHT22
#define DHTTYPE DHT22
int ledPin = 8;
int chavePin = 2;

volatile bool startSystem = false;
volatile byte Proccess_count = 0;

float tempMin = 10.0;
float tempMax = 70.0;
float umidMin = 20.0;
float umidMax = 80;

float temperatura = 0;
float umidade = 0;

bool tempAlerta = false;
bool umidAlerta = false;

DHT dht(DHTPIN, DHTTYPE);


unsigned long tempoAgora = 0;
unsigned long sensorTempoAgora = 0;
bool ledState = LOW;
 

//unsigned long tempoAntes = 0;

void handlerflag(){
  startSystem = !startSystem;  
}

void handler(){
  Proccess_count++;
}

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(chavePin, INPUT_PULLUP);
  Serial.begin(9600);
  dht.begin();
  Timer1.initialize(1000000);
  attachInterrupt(digitalPinToInterrupt(chavePin), handlerflag, CHANGE);
  tempoAgora = millis();
  sensorTempoAgora = millis();
}

void Proccess0(){ 
 
  temperatura = dht.readTemperature();
  umidade = dht.readHumidity();
  
  if((millis() - sensorTempoAgora) > 2000){
     sensorTempoAgora = millis();
     Serial.print("Temperatura:");
     Serial.print(temperatura);
     Serial.print("C, Umidade:");
     Serial.println(umidade);
  }
}

void Proccess1(){
  

  if ((millis() - tempoAgora) > 3000) {
    tempoAgora = millis(); // Atualiza tempo só uma vez

    if (temperatura < tempMin || temperatura > tempMax) {
      tempAlerta = true;
    }

    if (umidade < umidMin || umidade > umidMax) {
      umidAlerta = true;
    }

    if (tempAlerta || umidAlerta) {
      Serial.println("Alerta de limite excedido:");
      if (tempAlerta) {
        Serial.println("- Temperatura fora dos limites!");
      }
      if (umidAlerta) {
        Serial.println("- Umidade fora dos limites!");
      }
      ledState = HIGH;
      digitalWrite(ledPin, ledState);
    } else {
      // Se estiver tudo OK, apaga o LED
      ledState = LOW;
      digitalWrite(ledPin, ledState);
    }

    // Validação do sensor
    if (isnan(temperatura) || isnan(umidade)) {
      Serial.println("Falha na leitura do sensor DHT!");
    }
  }
}


void loop() {
  //delay(200);
  if(startSystem == true){
    Timer1.attachInterrupt(handler);
    
      switch(Proccess_count){
        case 0: Proccess0();
                break;
        case 1: Proccess1();
                break;
        default: Proccess_count = 0;
                 break;
      }
  }

  //Serial.println("teste");
}

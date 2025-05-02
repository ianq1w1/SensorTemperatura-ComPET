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
float umidMax = 90;

float temperatura = 0;
float umidade = 0;
bool alertaTemp;
bool alertaUmid;

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

if((millis() - tempoAgora) > 3000){
  if(temperatura < tempMin || temperatura > tempMax){
      if((millis() - tempoAgora) > 2000){
        Serial.println("Limite de temperatura excedido");
        tempoAgora = millis();
        ledState = HIGH;
        digitalWrite(ledPin, ledState);
      }
  }else{
    digitalWrite(ledPin, LOW);
  }
}

if((millis() - tempoAgora) > 3000){
  if(umidade < umidMin || umidade > umidMax){
      if((millis() - tempoAgora) > 2000){
        Serial.println("Limite de Umidade excedido");
        tempoAgora = millis();
        ledState = HIGH;
        digitalWrite(ledPin, ledState);
      }
  }else{
    digitalWrite(ledPin, LOW);
  }   
  } 


  if (isnan(temperatura) || isnan(umidade)) {
    Serial.println("Falha na leitura do sensor DHT!");
    return;
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

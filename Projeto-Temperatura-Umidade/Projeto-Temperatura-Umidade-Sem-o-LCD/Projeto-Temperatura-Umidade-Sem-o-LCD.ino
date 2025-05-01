#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <TimerOne.h>
#include <DHT_U.h>

#define DHTPIN 7 //Pino conectado ao DHT22
#define DHTTYPE DHT22
int ledPin = 8;

volatile byte Proccess_count = 0;

float tempMin = 10.0;
float tempMax = 5.0;
float umidMin = 70.0;
float umidMax = 90;

float temperatura = 0;
float umidade = 0;
bool alertaTemp;
bool alertaUmid;

DHT dht(DHTPIN, DHTTYPE);


unsigned long tempoAgora = 0;
bool ledState = LOW;
//unsigned long tempoAntes = 0;

void handler(){
  Proccess_count++;
}

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  dht.begin();
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(handler);
  tempoAgora = millis();
}

void Proccess0(){ 
  temperatura = dht.readTemperature();
  umidade = dht.readHumidity();

  if((millis() - tempoAgora) > 5000){
     tempoAgora = millis();
     Serial.print("Temperatura:");
     Serial.print(temperatura);
     Serial.print("C, Umidade:");
     Serial.println(umidade);
  }
}

void Proccess1(){
//depois tentar corrigir esse delay (substituir com millis)
  if(temperatura < tempMin || temperatura > tempMax){
      if((millis() - tempoAgora) > 2000){
        Serial.println("Limite de temperatura excedido");
        tempoAgora = millis();
        ledState = !ledState;
        digitalWrite(ledPin, ledState);
      }
  }
 
  if(umidade < umidMin || umidade > umidMax){
      if((millis() - tempoAgora) > 2000){
        Serial.println("Limite de Umidade excedido");
        tempoAgora = millis();
        ledState = !ledState;
        digitalWrite(ledPin, ledState);
      }    
  } 
}

void loop() {
  //delay(200);

  switch(Proccess_count){
    case 0: Proccess0();
            break;
    case 1: Proccess1();
            break;
    default: Proccess_count = 0;
             break;
  }

  //Serial.println("teste");
}

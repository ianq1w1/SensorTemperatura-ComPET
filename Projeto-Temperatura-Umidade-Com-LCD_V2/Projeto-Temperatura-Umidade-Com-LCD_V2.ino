#include <DHT.h>
#include <LiquidCrystal.h>
#include <TimerOne.h>

#define DHTPIN 6 //Pino conectado ao DHT22
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// LCD: RS, EN, D4, D5, D6, D7
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

volatile bool startSystem = false;
volatile byte Proccess_count = 0;

float tempMin = 10.0;
float tempMax = 70.0;
float umidMin = 12.0;
float umidMax = 90;

unsigned long tempoAgora = 0;
unsigned long sensorTempoAgora = 0;

float temperatura = 0;
float umidade = 0;

bool abaixoTemp = false;
bool acimaTemp = false;
bool abaixoUmid = false;
bool acimaUmid = false;

#define LED_NORMAL 8
#define LED_ABAIXO 9
#define LED_ACIMA 10
#define CHAVE_PIN 2

void handlerflag(){
  startSystem = !startSystem;  
}

void handler(){
  Proccess_count++;
}

void setup() {
  //Pinos do LCD


  pinMode(LED_NORMAL, OUTPUT);
  pinMode(LED_ABAIXO, OUTPUT);
  pinMode(LED_ACIMA, OUTPUT);
  pinMode(CHAVE_PIN, INPUT_PULLUP);
  
  Serial.begin(9600);
  dht.begin();
  lcd.begin(16, 2);
  lcd.print("Iniciando...");
  delay(2000);
  lcd.clear();

  Timer1.initialize(1000000);
  attachInterrupt(digitalPinToInterrupt(CHAVE_PIN), handlerflag, CHANGE);
  tempoAgora = millis();
  sensorTempoAgora = millis();
}

void Proccess0(){ 
 
  temperatura = dht.readTemperature();
  umidade = dht.readHumidity();
  
  if((millis() - sensorTempoAgora) > 2000){
     sensorTempoAgora = millis();
     lcd.clear(); // <- Adicionado
      lcd.setCursor(0,0);
      lcd.print("T:");
      lcd.print(temperatura,1);
      lcd.print((char)223); //Simbolo do celsius
      lcd.print("C ");

      lcd.setCursor(0,1);
      lcd.print("U:");
      lcd.print(umidade,1);
      lcd.print("% ");
  }
}

void Proccess1(){
  
  if ((millis() - tempoAgora) > 3000) {
    tempoAgora = millis(); // Atualiza tempo só uma vez

    //VERIFICA TEMPERATURA
    if (temperatura < tempMin) {
      abaixoTemp = true;
    }else{
       abaixoTemp = false; 
    }
    if(temperatura > tempMax){
       acimaTemp = true;
    }else{
      acimaTemp = false;
    }

    //VERIFICA UMIDADE
    if (umidade < umidMin) {
       abaixoUmid = true;
    }else{
       abaixoUmid = false; 
    }
    if(umidade > umidMax){
       acimaUmid = true;
    }else{
      acimaUmid = false;
    }
    
    if (acimaUmid || acimaTemp) {
      Serial.println("Alerta de limite excedido:");
        lcd.clear(); // <- Adicionado
      if (acimaTemp) {
        lcd.setCursor(0,0);
        lcd.print("!TEMP acima!");
      }
      if (acimaUmid) {
        lcd.setCursor(0,1);
        lcd.print("!UMID acima!");
      }
      digitalWrite(LED_ACIMA, HIGH);
    }else{
      digitalWrite(LED_ACIMA, LOW);
    }

    if (abaixoUmid || abaixoTemp){
        lcd.clear(); // <- Adicionado
      if (abaixoUmid){
        lcd.setCursor(0,1);
        lcd.print("!UMID abaixo!");        
      }
      if (abaixoTemp){
        lcd.setCursor(0,0);
        lcd.print("!TEMP abaixo!");
      }
      digitalWrite(LED_ABAIXO, HIGH);
     } else {
      digitalWrite(LED_ABAIXO, LOW);
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

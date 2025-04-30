#include <DHT.h>
#include <LiquidCrystal.h>

#define DHTPIN 7 //Pino conectado ao DHT22
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal lcd(12, 11, 2, 3, 4, 5);

float tempMin = 10.0;
float tempMax = 70.0;
float umidMin = 12.0;
float umidMax = 90;

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.begin(16, 2);
  lcd.print("Iniciando...");
  delay(2000);
  lcd.clear;
}

void loop() {
  delay(2000);

  float temperatura = dht.readTemperature();
  float umidade = dht.readHumidity();

  bool alertaTemp (temperatura < tempMin || temperatura > tempMax);
  bool alertaUmid (umidade < umidMin || umidade > umidMax);

  Serial.print("Temperatura:");
  Serial.print(temperatura);
  Serial.print("C, Umidade:");
  Serial.println(umidade);

  if(alertaTemp){
    Serial.println("Limite de temperatura excedido");
  }

  if(alertaUmid){
    Serial.println("Limite de Umidade excedido");
  }

    lcd.setCursor(0,0);
  lcd.print("T:");
  lcd.print(temperatura,1);
  lcd.print((char)233); //Simbolo do celsius
  lcd.print("C ");

  if(alertaTemp){
    lcd.print("!TEMP!");
  }else{
    lcd.print(" ");
  }

  lcd.setCursor(0,1);
  lcd.print("T:");
  lcd.print(temperatura,1);
  lcd.print((char)233); //Simbolo do celsius
  lcd.print("C ");
  
  if(alertaUmid){
    lcd.print("!UMID!");
  }else{
    lcd.print(" ");
  }
}

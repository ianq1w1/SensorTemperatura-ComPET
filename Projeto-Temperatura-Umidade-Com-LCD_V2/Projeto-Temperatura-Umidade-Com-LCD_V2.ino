#include <DHT.h>
#include <LiquidCrystal.h>

#define DHTPIN 6 //Pino conectado ao DHT22
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// LCD: RS, EN, D4, D5, D6, D7
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

float tempMin = 10.0;
float tempMax = 70.0;
float umidMin = 12.0;
float umidMax = 90;

#define LED_NORMAL 8
#define LED_ABAIXO 9
#define LED_ACIMA 10

void setup() {
  //Pinos do LCD
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);

  pinMode(LED_NORMAL, OUTPUT);
  pinMode(LED_ABAIXO, OUTPUT);
  pinMode(LED_ACIMA, OUTPUT);
  
  Serial.begin(9600);
  dht.begin();
  lcd.begin(16, 2);
  lcd.print("Iniciando...");
  delay(2000);
  lcd.clear();
}

void loop() {
  delay(1000);

 float temperatura = dht.readTemperature();
 float umidade = dht.readHumidity();

  bool abaixoTemp = temperatura < tempMin;
  bool acimaTemp = temperatura > tempMax;
  bool abaixoUmid = umidade < umidMin;
  bool acimaUmid = umidade > umidMax;
  
  Serial.print("Temperatura:");
  Serial.print(temperatura);
  Serial.print("C, Umidade:");
  Serial.println(umidade);

  lcd.clear();
  
  if(abaixoTemp){
    Serial.println("Temperatura abaixo do ideal");
    lcd.setCursor(0,0);
    lcd.print("!TEMP abaixo!");
  }else if(acimaTemp){
    Serial.println("Temperatura acima do ideal");
    lcd.setCursor(0,0);
    lcd.print("!TEMP acima!");
  }else{
    lcd.setCursor(0,0);
    lcd.print("T:");
    lcd.print(temperatura,1);
    lcd.print((char)223); //Simbolo do celsius
    lcd.print("C ");
  }

  if(abaixoUmid){
    Serial.println("Umidade abaixo do ideal");
    lcd.setCursor(0,1);
    lcd.print("!UMID abaixo!");
  }else if(acimaUmid){
    Serial.println("Umidade acima do ideal");
    lcd.setCursor(0,1);
    lcd.print("!UMID acima!");
  }else {
    lcd.setCursor(0,1);
    lcd.print("U:");
    lcd.print(umidade,1);
    lcd.print("% ");
  }

  if(abaixoTemp || abaixoUmid){
    digitalWrite(LED_NORMAL, LOW);
    digitalWrite(LED_ABAIXO, HIGH);
    digitalWrite(LED_ACIMA, LOW);
  }else if(acimaTemp || acimaUmid){
    digitalWrite(LED_NORMAL, LOW);
    digitalWrite(LED_ABAIXO, LOW);
    digitalWrite(LED_ACIMA, HIGH);
  }else{
    digitalWrite(LED_NORMAL, HIGH);
    digitalWrite(LED_ABAIXO, LOW);
    digitalWrite(LED_ACIMA, LOW);
  }
}

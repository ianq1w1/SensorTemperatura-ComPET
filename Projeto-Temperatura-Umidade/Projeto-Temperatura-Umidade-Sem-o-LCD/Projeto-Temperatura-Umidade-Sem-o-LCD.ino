#include <DHT.h>

#define DHTPIN 7 //Pino conectado ao DHT22
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

float tempMin = 10.0;
float tempMax = 70.0;
float umidMin = 12.0;
float umidMax = 90;

void setup() {
  Serial.begin(9600);
  dht.begin();

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

}

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTTYPE DHT22

int DHTpin = 5;
DHT_Unified dht(DHTpin, DHTTYPE);
int chavepin = 7;
int ledpin = 12;
uint32_t delayMS;  


void setup() {
  pinMode(chavepin,INPUT_PULLUP);
  pinMode(ledpin, OUTPUT);


  Serial.begin(9600);                             // monitor serial 9600 bps
  dht.begin();                                    // inicializa a função
  Serial.println("Usando o Sensor DHT");
  sensor_t Sensor;
  dht.temperature().getSensor(&Sensor);           // imprime os detalhes do Sensor de Temperatura
  Serial.println("------------------------------------");
  Serial.println("Temperatura");
  Serial.print  ("Sensor:       "); Serial.println(Sensor.name);
  Serial.print  ("Valor max:    "); Serial.print(Sensor.max_value); Serial.println(" *C");
  Serial.print  ("Valor min:    "); Serial.print(Sensor.min_value); Serial.println(" *C");
  Serial.print  ("Resolucao:   "); Serial.print(Sensor.resolution); Serial.println(" *C");
  Serial.println("------------------------------------");
  dht.humidity().getSensor(&Sensor);            // imprime os detalhes do Sensor de Umidade
  Serial.println("------------------------------------");
  Serial.println("Umidade");
  Serial.print  ("Sensor:       "); Serial.println(Sensor.name);
  Serial.print  ("Valor max:    "); Serial.print(Sensor.max_value); Serial.println("%");
  Serial.print  ("Valor min:    "); Serial.print(Sensor.min_value); Serial.println("%");
  Serial.print  ("Resolucao:   "); Serial.print(Sensor.resolution); Serial.println("%");
  Serial.println("------------------------------------");
  delayMS = Sensor.min_delay / 1000;

}

void loop(){
  delay(delayMS);                               // atraso entre as medições
  sensors_event_t Evento;                        // inicializa o evento da Temperatura
  dht.temperature().getEvent(&Evento);           // faz a leitura da Temperatura
  if (isnan(Evento.temperature))                 // se algum erro na leitura
  {
    Serial.println("Erro na leitura da Temperatura!");
  }
  else                                          // senão
  {
    Serial.print("Temperatura: ");              // imprime a Temperatura
    Serial.print(Evento.temperature);
    Serial.println(" *C");
  }
  dht.humidity().getEvent(&Evento);              // faz a leitura de umidade
  if (isnan(Evento.relative_humidity))           // se algum erro na leitura
  {
    Serial.println("Erro na leitura da Umidade!");
  }
  else                                          // senão
  {
    Serial.print("Umidade: ");                  // imprime a Umidade
    Serial.print(Evento.relative_humidity);
    Serial.println("%");
  }
      

}

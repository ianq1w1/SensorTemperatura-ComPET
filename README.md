# Sensor de Temperatura IoT - ComPET/IFPE Campus Recife

Este projeto visa o monitoramento de temperatura e umidade em ambientes do **ComPET (Complexo de Pesquisa, Ensino e Tecnologia) do IFPE Campus Recife**, utilizando um sensor DHT22 e exibindo os dados em um display LCD.

## 🚀 Funcionalidades
- **Monitoramento em tempo real** de temperatura e umidade ambiental  
- **Exibição dos dados** em display LCD integrado  
- **Configuração personalizável** de limites (valores máximos e mínimos)  
- **Sistema IoT** para futura integração com plataformas de análise  

## 🛠️ Tecnologias e Componentes
| Componente/Tecnologia       | Descrição                                                                 |
|-----------------------------|---------------------------------------------------------------------------|
| **Microcontrolador**        | Arduino Mega 2560                                                         |
| **Sensor**                  | DHT22 (precisão de ±0.5°C e ±2% umidade) Range de -40°C - 80°C            |
| **Display**                 | LCD 16x2 com interface I2C                                               |
| **Linguagem**               | C++ (via Arduino IDE)                                                    |
| **Protocolo de Comunicação**| Porta Serial -> Gateway Java -> Plataforma demo.thingsboard.io           |

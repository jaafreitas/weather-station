# Sistema de monitoramento remoto do nível dos rios

## Introdução

Uma tromba-d'água no rio Perequê-Açú pegou de surpresa os habitantes da cidade de Paraty em 2009, quando o rio chegou a subir 1,5 metro além do nível normal devido a uma forte tempestade na nascente do rio na Serra da Bocaina.

Nos últimos anos, com o avanço da tecnologia e a popularização da eletrônica digital, os próprios cidadãos podem se tornar protagonistas de soluções para melhorias nas cidades. Para alertarmos sobre e até mesmo prevenirmos futuras catástrofes naturais como essa, desenvolvemos um sistema de monitoramento remoto do nível dos rios, para o qual foram considerados os seguintes aspectos:
* baixo custo de produção;
* solução modular;
* monitoramento remoto em tempo real;
* peças de fácil aquisição;
* redundância nos diversos módulos;
* facilidade de manutenção;
* solução de código aberto;
* boa relação entre custo e precisão da medição.

## Desenvolvimento

Para o monitoramento dos rios ser mais efetivo, precisamos distribuir diversos medidores do nível dos rios ao longo de sua trajetória, inclusive em lugares remotos com pouca infraestrutura disponível para a instalação. Dessa forma, uma solução onde os diversos pontos de medição conseguem funcionar de forma autônoma se faz necessária. Dado esta distribuição dos pontos de medição, dividimos a solução em dois módulos:
* estação de monitoramento;
* estações meteorológicas

A estação de monitoramento é responsável por receber todos os dados enviados pelas estações metereológicas, monitorar os dados e, caso detecte uma variação expressiva no nível do rio em qualquer um dos pontos onde fazemos o monitoramento, disparar um alerta geral para todas as estações.

Nas estações meteorológicas, fazemos a medição do nível do rio utilizando pelo menos dois métodos diferentes, transmitimos os dados da medição para a estação de monitoramento e disparamos um alarme caso o nível do rio esteja muito acima do esperado, ou caso alguma outra estação tenha reportado um alerta.

Atualmente temos disponível uma diversidade de opções para a implementação de estações meteorológicas com os requisitos que precisamos, podemos utilizar desde pequenos computadores como o Raspberry PI até microcontroladores Arduino. Além disso, temos diversos módulos que podem ser utilizados para a medição do nível do rio como sensores de distância ultrassônicos e infravermelho além de sensores de pressão atmosférica. Para transmissão de dados, temos opções como módulos tradicionais de radiofrequência até mesmo soluções de internet sem fio.

Fizemos diversos testes utilizando o microcontrolador Arduino Nano e o ESP8266, e acabamos optando pelo último por se tratar de uma solução mais moderna, com recursos interessantes como Wi-Fi integrado, disponibilidade de armazenamento de dados e com um custo similar ao do Arduino.

Para a medição do nível do rio, optamos por utilizar um sensor de pressão MPXH6300A. Este é um sensor de pressão absoluta, com sinal de saída analógico, compatível com sistemas baseados em microcontroladores como o que estamos utilizando. A medição é feita por diferença de pressão devido ao deslocamento da coluna de água dentro do cano que fica ligado ao sensor. Dessa forma, quanto mais alto o nível do rio, maior a pressão do ar dentro do cano, assim chegamos a uma boa aproximação dessa variação de forma indireta, barata e com baixo custo de manutenção, já que temos apenas o cano em contato com a água.

Este sensor é bastante sensível a tensão aplicada ao terminal de alimentação. Ele tem uma saída analógica e a fórmula para o cálculo da pressão depende da tensão, por isso, temos que garantir uma tensão constante e conhecida, preferencialmente por volta dos 5 volts com uma baixa variação.

Como medidor secundário do nível do rio, utilizamos um sensor de distância ultrassônico HC-SR04. Este sensor é capaz de medir distâncias de 2 centímetros até 4 metros, tem um baixo custo e é facilmente encontrado em lojas de componentes eletrônicos. Para que o sensor ultrassônico funcione bem, precisamos de uma superfície lisa para a reflexão do som. Sendo assim, colocamos o sensor na parte de cima de um cano com diversos furos para a livre circulação da água, apontando para a parte de baixo, onde temos um disco sobre a água que se move livremente de acordo com o nível do rio.

Para deixar a estação meteorológica mais completa, também utilizamos um sensor de temperatura e umidade do ar DHT11. Este sensor é facilmente encontrado em lojas de componentes eletrônicos, tem um custo baixo e uma baixa precisão, porém pode ser facilmente substituído por um de maior precisão caso esta coleta de dados se torne um ponto importante.

A comunicação da estação meteorológica com a estação de monitoramento acontece por Wi-Fi. Estamos utilizando para isso o protocolo de conexão MQTT, por se tratar de um arquitetura especialmente construída para a comunicação entre máquinas, de forma leve, segura e robusta, além de ter nativamente suporte a publicação e assinatura de mensagens de notificação.

Como nem sempre temos fácil acesso físico às estações meteorológicas, implementamos um módulo de atualização remoto. Dessa forma, quando necessitarmos de alguma atualização do programa instalado no microcontrolador, poderemos fazer esse processo à distância.

Todo o código fonte desenvolvido até o momento encontra-se disponível em https://github.com/jaafreitas/weather-station organizado da seguinte forma:
* monitor: código da estação de monitoramento desenvolvido em Python;
* station: código da estação meteorológica desenvolvido em C++/Arduino.

## Resultados

O sistema encontra-se em fase final de prototipagem e os testes estão sendo feitos em ambiente controlado. Até o momento, os resultados foram bastante positivos e conseguimos detectar variações do nível da água de acordo com o esperado. 

Nos testes temos utilizado uma mangueira que é submergida em um recipiente com água no qual, utilizando uma régua, fazemos a medição da imersão da mangueira e verificamos se é compatível com o que está sendo recebido pela estação de monitoramento.

## Próximos passos

Um ponto importante na arquitetura utilizada neste projeto é a sua modularidade. Dessa forma, temos planejado diversas expansões, como por exemplo:
* Módulo de comunicação de longo alcance por radio frequência;
* Retenção local das medições e mensagens de depuração;
* Módulo de aviso sonoro e/ou visual para estações em áreas habitadas;
* Sistema de energia solar fotovoltaica;
* Banco de dados com o histórico das medições de todas as estações;
* Página com informações dos dados históricos;
* Aplicativo com informações dos dados históricos e notificação de alarme das estações meteorológicas.

## Bibliografia

ESP8266 Overview. Disponível em <[http://espressif.com/en/products/hardware/esp8266ex/overview](http://espressif.com/en/products/hardware/esp8266ex/overview)>. Acesso em 31 de agosto de 2017.

Getting Started with the Arduino Nano. Disponível em <[https://www.arduino.cc/en/Guide/ArduinoNano](https://www.arduino.cc/en/Guide/ArduinoNano)>. Acesso em 31 de agosto de 2017.

Raspberry Pi. Disponível em <[https://en.wikipedia.org/wiki/Raspberry_Pi](https://en.wikipedia.org/wiki/Raspberry_Pi)>.  Acesso em 31 de agosto de 2017.

MPXH6300A datasheet. Disponível em <[https://www.digchip.com/datasheets/download_datasheet.php?id=3258881&part-number=MPXH6300A](https://www.digchip.com/datasheets/download_datasheet.php?id=3258881&part-number=MPXH6300A)>. Acesso em 31 de agosto de 2017.

HC-SR04 datasheet. Disponível em <[https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf](https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf)>. Acesso em 31 de agosto de 2017.

DHT11 datasheet. Disponível em <[http://www.micropik.com/PDF/dht11.pdf](http://www.micropik.com/PDF/dht11.pdf)>. Acesso em 31 de agosto de 2017.

MQTT 101 – How to Get Started with the lightweight IoT Protocol. Disponível em <[http://www.hivemq.com/blog/how-to-get-started-with-mqtt](http://www.hivemq.com/blog/how-to-get-started-with-mqtt)>. Acesso em 31 de agosto de 2017.

MQTT and ESP8266. Disponível em <[https://tuts.codingo.me/mqtt-and-esp8266](https://tuts.codingo.me/mqtt-and-esp8266)>. Acesso em 31 de agosto de 2017.

Introduction to Over the Air update. Disponível em <[http://esp8266.github.io/Arduino/versions/2.0.0/doc/ota_updates/ota_updates.html](http://esp8266.github.io/Arduino/versions/2.0.0/doc/ota_updates/ota_updates.html)>. Acesso em 31 de agosto de 2017.

Precise voltage measurement with the Arduino board. Disponível em <[http://www.skillbank.co.uk/arduino/measure.htm](http://www.skillbank.co.uk/arduino/measure.htm)>. Acesso em 31 de agosto de 2017.

Sistema de monitoramento remoto dos rios do município de Itajaí. Disponível em <[http://defesacivil.itajai.sc.gov.br/telemetria/telemetria.php](http://defesacivil.itajai.sc.gov.br/telemetria/telemetria.php)>. Acesso em 31 de agosto de 2017.

## Anexos

### 1. Imagem do protótipo:

#### ![](null)

### 2. Exemplo de informação de depuração da estação meteorológica:
<pre>
***** Station 2017.05.28.1839 (May 28 2017, 18:39:00) [ESP Core 2_3_0 (WeMos D1 mini)] *****

Starting WiFi Setup...
Access Point 402723 started at IP address 192.168.4.1
Connecting station 402723 to SSID chaos............... Ok.
IP address: 192.168.1.28
1970-01-01 00:00:08 NTP time sync... Ok.
2017-05-28 21:39:25 Starting Over the Air updater at http://192.168.1.28/firmware ... Ok.
2017-05-28 21:39:25 Attempting MQTT connection on iot.eclipse.org... Ok.
2017-05-28 21:39:25 -> station/402723/version: 2017.05.28.1838
2017-05-28 21:39:25 -> station/402723/uptime: 2017-05-28 21:39:25
2017-05-28 21:39:26 ++ station/402723/alarm
2017-05-28 21:39:26 -> station/402723/sensor/temperature: 25.00
2017-05-28 21:39:26 -> station/402723/sensor/humidity: 60.00
2017-05-28 21:39:26 -> station/402723/sensor/ultrasonic: 110.86
2017-05-28 21:39:27 -> station/402723/sensor/MPXH6300A: 93.70
2017-05-28 21:39:27 -> station/402723/sensor/ultrasonic: 110.82
2017-05-28 21:39:27 -> station/402723/sensor/MPXH6300A: 93.71
2017-05-28 21:39:27 <- station/402723/alarm: 0
2017-05-28 21:39:28 -> station/402723/sensor/ultrasonic: 110.79
2017-05-28 21:39:28 -> station/402723/sensor/MPXH6300A: 93.70
</pre>
### 3. Exemplo de informações recebidas a partir da comunicação MQTT:

![](null)

### 4. Teste de funcionamento do sensor de pressão MPXH6300A:
<pre>
Medidas extraídas a partir de puxada de ar no sensor:
value: 302 | volts: 1.48 | kPa: 93.94 | atm: 0.93
value: 295 | volts: 1.44 | kPa: 91.79 | atm: 0.91
value: 291 | volts: 1.42 | kPa: 90.56 | atm: 0.89
value: 288 | volts: 1.41 | kPa: 89.64 | atm: 0.88
value: 285 | volts: 1.39 | kPa: 88.72 | atm: 0.88
value: 283 | volts: 1.38 | kPa: 88.10 | atm: 0.87
value: 282 | volts: 1.38 | kPa: 87.80 | atm: 0.87

Medidas extraídas a partir de sopro de ar no sensor:
value: 302 | volts: 1.48 | kPa: 93.94 | atm: 0.93
value: 311 | volts: 1.52 | kPa: 96.71 | atm: 0.95
value: 319 | volts: 1.56 | kPa: 99.17 | atm: 0.98
value: 320 | volts: 1.56 | kPa: 99.48 | atm: 0.98
value: 323 | volts: 1.58 | kPa: 100.40 | atm: 0.99
value: 330 | volts: 1.61 | kPa: 102.55 | atm: 1.01

Medidas extraídas a partir de coluna de 28cm de água:
value: 302 | volts: 1.48 | kPa: 93.94 | atm: 0.93
value: 303 | volts: 1.48 | kPa: 94.25 | atm: 0.93
value: 304 | volts: 1.49 | kPa: 94.56 | atm: 0.93
value: 305 | volts: 1.49 | kPa: 94.87 | atm: 0.94
value: 306 | volts: 1.50 | kPa: 95.17 | atm: 0.94
value: 306 | volts: 1.50 | kPa: 95.17 | atm: 0.94
value: 307 | volts: 1.50 | kPa: 95.48 | atm: 0.94
value: 308 | volts: 1.51 | kPa: 95.79 | atm: 0.95
value: 309 | volts: 1.51 | kPa: 96.10 | atm: 0.95
value: 310 | volts: 1.52 | kPa: 96.40 | atm: 0.95
value: 311 | volts: 1.52 | kPa: 96.71 | atm: 0.95
value: 312 | volts: 1.52 | kPa: 97.02 | atm: 0.96
</pre>

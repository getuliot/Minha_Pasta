/*
     Q0482-Sketch.ino
     AUTOR:   BrincandoComIdeias
     LINK:    https://www.youtube.com/brincandocomideias ; https://cursodearduino.net/
     COMPRE:  https://www.arducore.com.br/
     SKETCH:  Data Logger com Envio ao Excel via Teclado (Para Arduino Leonardo ou Compatível)
     DATA:    20/07/2019
Atualizdo em 12.02.2021 por Getúlio Teruo Tateoki
   ******SOMENTE TEMPERATURA******
*/
//SENSOR DE TEMPERATURA E HUMIDADE RELATIVA
#include <dht.h>

//OBJETO PARA EMULADOR DE TECLADO (ARDUINO LEONARDO OU COMPATIVEL)
#include <Keyboard.h>

//CRIACAO DOS OBJETOS
dht DHT;

//PINAGEM DO CIRCUITO
#define pinPause 10
#define DHT22_PIN 4

//DECLARACAO DAS FUNCOES
void estadoPause();
void erroCritico();
void teclaEnter();
void teclaTAB();

//EXECUTADO QUANDO O ARDUINO FOR LIGADO
void setup() {
  //INICIO DOS PINOS
  pinMode(pinPause, INPUT_PULLUP);

  //INICIO DO EMULADOR DE TECLADO
  Keyboard.begin();
}

//EXECUTADO REPETIDAMENTE APÓS A EXECUCAO DO SETUP
void loop() {

  //PARA FACILITAR FUTURAS CARGAS
  if (!digitalRead(pinPause)) {
    estadoPause();
    return;
  }

  int chk = DHT.read22(DHT22_PIN);
  if (chk == DHTLIB_OK) {

/*
    String umidade_string;
    umidade_string = String(DHT.humidity, 2);
    umidade_string.replace(".", ",");

    Keyboard.print(umidade_string);
    teclaTAB();
*/

    String temperatura_string;
    temperatura_string = String(DHT.temperature, 2);
    temperatura_string.replace(".", ",");

    Keyboard.print(temperatura_string);
    teclaTAB();
  }

  teclaEnter();
// delay(2000); //medida a cada 2 segundos
 
 delay(1000); //medida a cada 1 segundo
}

//FUNCAO PARA AGUARDAR ANTES DE INICIAR O SETUP PARA NAO PROJUDICAR FUTURAS CARGAS
void estadoPause() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(900);                       // wait for a second
}

//FUNCAO PARA AVISO DE ERRO CRITICO ATRAVES DO LED INTERNO DO ARDUINO
void erroCritico() {
  pinMode(LED_BUILTIN, OUTPUT);
  while (true) {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(200);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(200);                       // wait for a second
  }
}

//FUNCAO PARA ENVIAR O APERTO DE UM ENTER
void teclaEnter() {
  Keyboard.press(KEY_RETURN);   // PRESSIONA O ENTER
  delay(50);                   // ESPERA 100 MILISSEGUNDOS
  Keyboard.release(KEY_RETURN); // SOLTA O ENTER
}

//FUNCAO PARA ENVIAR O APERTO DE UM TAB
void teclaTAB() {
  Keyboard.press(KEY_TAB);   // PRESSIONA O TAB
  delay(50);                // ESPERA 100 MILISSEGUNDOS
  Keyboard.release(KEY_TAB); // SOLTA O TAB
}

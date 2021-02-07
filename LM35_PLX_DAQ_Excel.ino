/*
 * Monitoração de temperatura com LM35,PLX_DAQ e Gráfico Excel
 * Getúlio Teruo Tateoki
 * 04.02.2021
 */
float pinoPotenciometro = 1;    //  variavel que define a porta do potenciometro.
int linha = 0;         // variavel que se refere as linhas do excel
int LABEL = 1;   
float valor = 0;               // variavel que guarda o valor lido do potenciometro
float temp = 0;
void setup(){
Serial.begin(9600);                     //  inicialização da comunicação serial
Serial.println("CLEARDATA");            // Reset da comunicação serial
//Serial.println("LABEL,Hora,valor,linha");   // Nomeia as colunas
//Serial.println("LABEL,Hora,volt,linha");   // Nomeia as colunas
Serial.println("LABEL,Hora,linha,Temp");   // Nomeia as colunas
}
 
void loop(){
  //analogReference(DEFAULT);
  analogReference(INTERNAL);  // Referencia do ADC em 1.1V
 
valor = analogRead(pinoPotenciometro);   // faz a leitura do potenciometro e guarda o valor em val.
 temp = ((valor*1.1)/1023)*100;
//temp = (valor*5.0)/1023/0.01;
linha++; // incrementa a linha do excel para que a leitura pule de linha em linha
 
Serial.print("DATA,TIME,"); //inicia a impressão de dados, sempre iniciando 
//Serial.print(valor); 
Serial.print(linha);
Serial.print(",");
Serial.println(temp);


 
if (linha > 100) //laço para limitar a quantidade de dados
{
linha = 0;
Serial.println("ROW,SET,2"); // alimentação das linhas com os dados sempre iniciando
}
delay(2000);  // espera 2000 milisegundos
 
 
}

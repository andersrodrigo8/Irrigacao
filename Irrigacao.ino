#include "dht.h" //INCLUSÃO DE BIBLIOTECA
 
const int pinoDHT11 = A2; //PINO ANALÓGICO UTILIZADO PELO DHT11
 
dht DHT; //VARIÁVEL DO TIPO DHT
int contador = 1;
//int ligado = 90000; // 1,5 minutos
//int espera = 900000; // 15 minutos
int temperAcionamento = 26; 

void setup(){
  pinMode(7, OUTPUT); //defino pino digital 7 como saida
  Serial.begin(9600); //INICIALIZA A SERIAL
  delay(2000); //INTERVALO DE 2 SEGUNDO ANTES DE INICIAR
}

void Acionamento(){
    Serial.println("Acionou a bomba");
    digitalWrite(7, HIGH);    // liga o pino 7
    delay(90000);            // aguarda 3 minutos
    digitalWrite(7, LOW);     // desliga o pino 7
}

void ImprimeTemp_Humid(){
  Serial.print("Umidade: "); //IMPRIME O TEXTO NA SERIAL
  Serial.print(DHT.humidity); //IMPRIME NA SERIAL O VALOR DE UMIDADE MEDIDO
  Serial.print("%"); //ESCREVE O TEXTO EM SEGUIDA
  Serial.print(" / Temperatura: "); //IMPRIME O TEXTO NA SERIAL
  Serial.print(DHT.temperature, 0); //IMPRIME NA SERIAL O VALOR DE UMIDADE MEDIDO E REMOVE A PARTE DECIMAL
  Serial.println("*C"); //IMPRIME O TEXTO NA SERIAL
  delay(2000);
}
  
void loop(){
  float umidad;
  int temper;
  DHT.read11(pinoDHT11); //LÊ AS INFORMAÇÕES DO SENSOR
  umidad = (DHT.humidity);
  temper = (DHT.temperature);
  

  ImprimeTemp_Humid();

  if (umidad < 35.00){ //comentei pois havia um erro de leitura
    if (temper >= temperAcionamento){
      Acionamento();
      contador = 11;
    }
   
      while(contador <= 10){
        Serial.print("Contador: ");
        Serial.println(contador);
        delay(90000);  //1,5 minutos
        ImprimeTemp_Humid();

        if (temper > temperAcionamento){
          Acionamento();
          contador = 11;
        }
        
        if(contador > 9){      
          Acionamento();
          contador = 11;
        }
        
        contador++;
      }
  }         
  delay(900000); // aguarda 30 minutos
}

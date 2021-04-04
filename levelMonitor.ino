#include <LiquidCrystal.h>
LiquidCrystal lcd(7,8,9,10,11,12);

const int SENSOR_BAIXO =  3;
const int SENSOR_MEDIO =  4;
const int SENSOR_ALTO =  5;

const int INTERRUPCAO_SENSOR = 0;
const int SENSOR_FLUXO = 2;

//definicao da variavel de contagem de voltas
unsigned long contador = 0;
//definicao do fator de calibracao para conversao do valor lido
const float FATOR_CALIBRACAO = 4.5;
//definicao das variaveis de fluxo e volume
float fluxo = 0;
float volume = 0;
float volume_total = 0;

//definicao da variavel de intervalo de tempo
unsigned long tempo_antes = 0;




void setup() {
  
    //configuracao do pino do sensor como entrada em nivel logico alto
  pinMode(SENSOR_FLUXO, INPUT_PULLUP);
  pinMode(SENSOR_BAIXO, INPUT);
  pinMode(SENSOR_MEDIO, INPUT);
  pinMode(SENSOR_ALTO, INPUT);
  
  pinMode(6, OUTPUT);
  analogWrite(6, 80);
  
  lcd.begin(16,2);
  }

void loop() {
  lcd.clear();
  
  if((millis() - tempo_antes) > 1000){

    //desabilita a interrupcao para realizar a conversao do valor de pulsos
    detachInterrupt(INTERRUPCAO_SENSOR);

    //conversao do valor de pulsos para L/min
    fluxo = ((1000.0 / (millis() - tempo_antes)) * contador) / FATOR_CALIBRACAO;
  
    //reinicializacao do contador de pulsos
    contador = 0;

    //atualizacao da variavel tempo_antes
    tempo_antes = millis();

    //contagem de pulsos do sensor
    attachInterrupt(INTERRUPCAO_SENSOR, contador_pulso, FALLING);
    
  }

  if (fluxo > 0) {

    lcd.print(fluxo);
    lcd.println(" L/min");
   
    } 
  else {
    lcd.print("Nivel de Agua");  

    }
  
  
  
  lcd.setCursor(0,1);
  
  int read_sensor_baixo = digitalRead(SENSOR_BAIXO);
  int read_sensor_medio = digitalRead(SENSOR_MEDIO);
  int read_sensor_alto = digitalRead(SENSOR_ALTO);
  
  if(read_sensor_baixo == LOW){ //Se for '0'
    
    lcd.print("Muito Baixo");
    
    } else if (read_sensor_medio == LOW) { 
    lcd.print("Baixo");
  } else if (read_sensor_alto == LOW) { 
    lcd.print("Medio");
  } else {
    lcd.print("ALTO");
    }

  delay(100); //Aguarda 100 milissegundo para nova leitura
  }

 void contador_pulso() {
  
  contador++;
  
}
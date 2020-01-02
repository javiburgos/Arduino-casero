//  Programa que configura un sensor de ultrasonido y enciende un led cuando está por debajo de una determinada distancia
//  Javier Burgos. 2019.
#include <Arduino.h>

#define PinTrig 7
#define PinEcho 6
#define PinLed 3  // Pin PWM

void mostrar_distancia();
void alarma();
// Definimos las variables que vamos a necesitar para calcular la distancia de detección
long duracion;
long distancia;


void setup() {
  pinMode(PinTrig, OUTPUT);   // Lo configuramos como salida porque es por donde vamos a meter un pulso
  pinMode(PinEcho, INPUT);    // Es un pin de entrada ya que nos devolverá un pulso de duración el tiempo que ha tardado en ir y volver nuestra señal
  pinMode(PinLed, OUTPUT);    // Configuramos el led como salida
  Serial.begin(9600);         // Inicializamos el serial a 9600 baudios
}

void loop() {
  // Primero nos aseguramos de que el pulso está en bajo (durante 2 ms)
  digitalWrite(PinTrig, LOW);
  delay(2);

  // Ahora configuramos el pulso durante 10 ms (data sheet)
  digitalWrite(PinTrig, HIGH);
  delay(10);
  digitalWrite(PinTrig, LOW);

  // Recogemos la duración del pulso recibida por el Echo y calculamos la distancia
  duracion = pulseIn(PinEcho, HIGH);
  distancia = duracion*0.034/2;       // Lo multiplicamos por 0.034 ya que es la velocidad del viento en cm/μs y entre 2 ya que solo queremos la distancia de ida

  if (distancia > 0 && distancia <= 15){        // Si la distancia es menor de 15 cm, se activa el led
    mostrar_distancia();    // Mostramos la distancia en cm
    alarma();               // Hacemos el led parpadear
    Serial.println("¡Alarma!");
  }
  else if (distancia > 15 && distancia < 500){  //  Si no está por debajo de 15 cm
    mostrar_distancia();    // Solo mostramos la distancia
  }
  else{                                         // Si la distancia está fuera del rango (muy cerca o más lejos de 5 metros), decimos que no muestre nada
    Serial.println("--- Fuera de rango ---");
    digitalWrite(PinLed, LOW);  // Apagamos el led por si acaso
  }
}

// Función que muestra la distancia en cm por el serial
void mostrar_distancia(){
  Serial.print("distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");
}

// Función que hace parpadear al led progresivamente
void alarma(){
  int i;
  for(i=0; i<=255; i+=10){
    analogWrite(PinLed, i);
    delay(10);
  }
  for(i=255; i>=0; i-=10){
    analogWrite(PinLed, i);
    delay(10);
  }
}

// Función que hace sonar el buzzer
void buzzer(){
  
}

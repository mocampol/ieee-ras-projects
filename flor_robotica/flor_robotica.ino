/*
  FLOR ROBÓTICA
*/

#include <Stepper.h>

// Configuración
const int PASOS_POR_VUELTA = 2048;
const int VELOCIDAD_RPM    = 6;      // (máximo 15 rpm)
const int DIRECCION        = 1;

const int PIN_LED          = 3;
const bool LED_RESPIRA     = true;   // true = brillo sube y baja | false = LED encendido fijo

Stepper motor(PASOS_POR_VUELTA, 8, 10, 9, 11);

// Variables del brillo del LED
int brillo = 0;
int pasoBrillo = 5;
unsigned long ultimoCambioLed = 0;
const unsigned long INTERVALO_LED = 30;


void setup() {
  pinMode(PIN_LED, OUTPUT);
  motor.setSpeed(VELOCIDAD_RPM);

  if (!LED_RESPIRA) {
    digitalWrite(PIN_LED, HIGH);
  }
}

void loop() {
  motor.step(DIRECCION);

  if (LED_RESPIRA && millis() - ultimoCambioLed >= INTERVALO_LED) {
    ultimoCambioLed = millis();
    brillo += pasoBrillo;

    if (brillo >= 255) {
      brillo = 255;
      pasoBrillo = -pasoBrillo;
    } else if (brillo <= 10) {
      brillo = 10;
      pasoBrillo = -pasoBrillo;
    }
    analogWrite(PIN_LED, brillo);
  }
}

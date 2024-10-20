#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Inicializa el objeto para el driver PCA9685
Adafruit_PWMServoDriver pca9685 = Adafruit_PWMServoDriver();

#define SERVOMIN  150 // Valor mínimo del pulso para el servo
#define SERVOMAX  600 // Valor máximo del pulso para el servo

// Número de servos que controlaremos
const int num_servos = 12;

void setup() {
  Serial.begin(9600);
  Serial.println("Inicializando PCA9685 para controlar 12 servomotores");

  // Inicializa el PCA9685 con la dirección I2C por defecto (0x40)
  pca9685.begin();
  
  // Ajusta la frecuencia PWM para los servos (50Hz, para servos típicos)
  pca9685.setPWMFreq(50);
  
  // Espera a que se estabilice
  delay(10);
}

void loop() {
  // Mueve todos los servos a 90 grados continuamente
  for (int servo = 0; servo < num_servos; servo++) {
    moverServo(servo, 0);  // Mueve cada servo a la posición de 90 grados
    delay(100);
    moverServo(servo, 90);  // Mueve cada servo a la posición de 90 grados
    delay(100);
    moverServo(servo, 180);  // Mueve cada servo a la posición de 90 grados
  }

  // Puedes poner un pequeño retraso para evitar mandar señales demasiado rápido
  delay(100);  // Envía el comando cada 500ms
}

// Función para mover un servo a un ángulo dado
void moverServo(int servo_num, int angulo) {
  // Convierte el ángulo (0-180 grados) al rango del PWM
  int pulso = map(angulo, 0, 180, SERVOMIN, SERVOMAX);
  
  // Envía la señal PWM al canal correspondiente
  pca9685.setPWM(servo_num, 0, pulso);
}

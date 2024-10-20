#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Crea un objeto para el controlador PCA9685
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Definir los puertos del controlador para cada servo
const int servo_pin[4][3] ={ {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {9, 10, 11} };

// Rango de ángulo para los servos
const int SERVO_MIN = 150;
const int SERVO_MAX = 600;



void setup() {
  //Inicializa el controlador 
  pwm.begin();
  pwm.setPWMFreq(60); //Frecuencia de 60 Hz para los servos 

  // Establece todos los servos en la posición inicial de 90 grados
  for(int i=0; i<4; i++){

    for(int j = 0 ; j < 3 ; j++){

      setServoAngle(servo_pin[i][j], 90);
      delay(20);

    }


  }

}

void loop() {
  //Mover todos los servos a 90
  for(int i = 0 ; i<4;i++){

    for(int j = 0;j<3;j++){
      
      setServoAngle(servo_pin[i][j],90);
      delay(20);
    }


  }

}


//Funcion para mover el servo a un angulo en especifico 
void setServoAngle(int servoNum , int angle){
  int pulse = SERVO_MIN + ((SERVO_MAX - SERVO_MIN) * angle) / 180;
  pwm.setPWM(servo_num, 0, pulse);
}


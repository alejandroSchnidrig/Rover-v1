#include <Arduino.h>
#include "Motor.h"

#define DERECHA_A 12
#define DERECHA_B 14
#define DERECHA_PWM 13
#define IZQUIERDA_A 26
#define IZQUIERDA_B 27
#define IZQUIERDA_PWM 25

Motor::Motor() = default;

void Motor::inicializar() {
    pinMode(DERECHA_A, OUTPUT);
    pinMode(DERECHA_B, OUTPUT);
    pinMode(DERECHA_PWM, OUTPUT);
    pinMode(IZQUIERDA_A, OUTPUT);
    pinMode(IZQUIERDA_B, OUTPUT);
    pinMode(IZQUIERDA_PWM, OUTPUT);
}

void Motor::avanzar() {
    digitalWrite(DERECHA_A, LOW);
    digitalWrite(DERECHA_B, HIGH);
    digitalWrite(IZQUIERDA_A, LOW);
    digitalWrite(IZQUIERDA_B, HIGH);
    analogWrite(DERECHA_PWM, 170);
    analogWrite(IZQUIERDA_PWM, 170);
}

void Motor::retroceder() {
    digitalWrite(DERECHA_A, HIGH);
    digitalWrite(DERECHA_B, LOW);
    digitalWrite(IZQUIERDA_A, HIGH);
    digitalWrite(IZQUIERDA_B, LOW);
    analogWrite(DERECHA_PWM, 170);
    analogWrite(IZQUIERDA_PWM, 170);
}

void Motor::parar() {
    digitalWrite(DERECHA_A, LOW);
    digitalWrite(DERECHA_B, LOW);
    digitalWrite(IZQUIERDA_A, LOW);
    digitalWrite(IZQUIERDA_B, LOW);
}
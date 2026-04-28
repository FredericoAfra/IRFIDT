#include <Servo.h>

Servo servo;
int pos;
const int motor = 4;
  
void setup()
{
  servo.attach(3);
  servo.write(0);
  pinMode(motor, LOW);
}

void loop()
{
  // Movimento do servo de 0 a 90 graus
    for (pos = 0; pos < 90; pos++) {
        servo.write(pos); // Define a posição atual do servo
        delay(15); // Aguarda 15 milissegundos antes de mover para a próxima posição
    }
    delay(1000); // Aguarda 1 segundo antes de iniciar o próximo movimento
 
    // Movimento do servo de 90 a 0 graus
    for (pos = 90; pos >= 0; pos--) {
        servo.write(pos); // Define a posição atual do servo
        delay(15); // Aguarda 15 milissegundos antes de mover para a próxima posição
    }
    delay(1000); // Aguarda 1 segundo antes de iniciar o próximo ciclo
}
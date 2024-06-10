#include <SoftwareSerial.h> //Biblioteca para conectar com o bluetooth (já vem instalado), não precisa baixar
#include <Servo.h>//Inclusão da biblioteca Servo

SoftwareSerial serialdobluetooth(8,9); // Portas para o serial do bluetooth (RX, TX)
Servo servomotor;//Criando objeto do tipo Servo
int pos = 90;//Variável que armazena a posição do servo

#define led1 13 // Pinos digitais dos leds
#define IN1 5 // Pino do L298
#define IN2 6 // Pino do L298
#define IN3 10 // Pino do L298
#define IN4 11 // Pino do L298
#define PinoServo 3 // Pino do servo motor

int valordobluetooth; // Variável que vai ler o valor enviado pelo bluetooth 

class DCMotor {  
  int spd = 255; 
  int pin1, pin2;
  
  public:  
  
    void Pinout(int in1, int in2){ // Pinout é o método para a declaração dos pinos que vão controlar o objeto motor
        pin1 = in1;
        pin2 = in2;
        pinMode(pin1, OUTPUT);
        pinMode(pin2, OUTPUT);
      }   
    void Speed(int speed){ // Speed é o método que irá ser responsável por salvar a velocidade de atuação do motor
        spd = speed;
      }     
    void Forward(){ // Forward é o método para fazer o motor girar para frente
        analogWrite(pin1, spd);
        digitalWrite(pin2, LOW);
      }   
    void Backward(){ // Backward é o método para fazer o motor girar para trás
        digitalWrite(pin1, LOW);
        analogWrite(pin2, spd);
      }
    void Stop(){ // Stop é o metodo para fazer o motor ficar parado.
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, LOW);
      }
   };
  
  
DCMotor Motor1, Motor2; // Criação de dois objetos motores, já que usaremos dois motores, e eles já estão prontos para receber os comandos já configurados acima.

void setup() 

{
  serialdobluetooth.begin(9600); //Início da serial do bluetooth
  pinMode(led1, OUTPUT); //Ligando a saída dos leds
  servomotor.attach(PinoServo);//Atribui o pino digital 3 ao objeto servomotor
  digitalWrite(led1,LOW); //Garantir que os LEDs estejam desligados antes do comando
  Motor1.Pinout(IN1,IN2); // Seleção dos pinos que cada motor usará, como descrito na classe.
  Motor2.Pinout(IN3,IN4); 
}

void loop() {

  if (serialdobluetooth.available()) //Se o bluetooth estiver funcionando, vai ser lido o "valor", para reproduzir o comando
    {
      valordobluetooth = serialdobluetooth.read();
    }

  //*****Funções de direção utilizando o servo motor*****
  if (valordobluetooth == 'A') //Retorna o servo motor para o angulo reto (BOTAO BAIXO)
    {
      servomotor.write(90);
    }

  if (valordobluetooth == 'D')//Pisca o led builtin (BOTAO CIMA)
    { 
      servomotor.write(90);
    }

  if (valordobluetooth == 'L') //Move o servo para o lado esquerdo (BOTAO LADO ESQUERDO)
    {
      
      servomotor.write(72);
      
    }

  if (valordobluetooth == 'R') //Move o servo para o lado direito (BOTAO LADO DIREITO)
    {
      
      servomotor.write(108);
      
    }

  //*****Funções dos Motores de Velocidade*****

  if (valordobluetooth == 'B')//Função que freia os motores (BOTAO QUADRADO)
    {
      Motor1.Stop();
      Motor2.Stop();
    } 

  if (valordobluetooth == 'S') //Função que anda pra frente com velocidade máxima (BOTAO X)
    {
      Motor1.Speed(255); // A velocidade do motor pode variar de 0 a 255, onde 255 é a velocidade máxima.
      Motor2.Speed(255);
      Motor1.Forward();
      Motor2.Forward();
    }
  
  if (valordobluetooth == 'Z') //Função para dar ré (BOTAO BOLA)
    {
      Motor1.Speed(255);
      Motor2.Speed(255);
      Motor1.Backward();
      Motor2.Backward();
    }
  if (valordobluetooth == 'F') //Função para andar devagar (BOTAO TRIANGULO)
    {
       digitalWrite (led1,HIGH);
      delay(10000);
      digitalWrite (led1,LOW);
      
    }

  
}

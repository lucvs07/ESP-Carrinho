// Projeto Física -> Medir acelaração e velocidade de um carrinho de brinquedo

// Importação de Bibliotecas
#include <Adafruit_GFX.h> // Biblioteca para o display oled
#include <Adafruit_SSD1306.h> // Biblioteca para o display oled
#include <Wire.h>
#include <MPU6050.h> // Biblioteca para o sensor MPU6050
#include <VL53L0X.h> // Sensor TOF
#include <NewPing.h> // Sensor ultrassônico

// Definir sensores
#define TRIG_PIN 23
#define ECHO_PIN 18
#define MAX_DISTANCE 200 // distância máxima do sensor ultrassônico

VL53L0X sensorTOF;
NewPing sensorUltrasonic(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

// Definições do Display
#define width_display 128
#define height_display 64
#define reset_display -1
Adafruit_SSD1306 display(width_display, height_display, &Wire, reset_display);

// Definição MPU
MPU6050 mpu;

//int16_t ax, ay, az; // Aceleração nos eixos
// float velocidadeX = 0; // Velocidade no eixo X
//unsigned long lastTime = 0; // Tempo para integração

//unsigned long startTime;
//unsigned long endTime;
const float distanceSensores = 15; // cm
float velocidade = 0;
long timer1 = 0;
long timer2 = 0;
float Time;
int flag1 = 0;
int flag2 = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // Inicializando o monitor serial
  Wire.begin();

  // Inicializar TOF
  sensorTOF.setTimeout(500);
  if (!sensorTOF.init()){
    Serial.println("Falha ao inicalizar o TOF");
    while(1);
  }
  sensorTOF.startContinuous();

  // Configurar sensor ultrassônico
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  /* Inicializar o MPU
  mpu.initialize();
  if(!mpu.testConnection()){
    Serial.println("MPU não conectado");
    while(1);
  }

  /* Inicializando o Display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
    Serial.println(F("Falha ao inicializar o display"));
    while(1);
  } else {
    Serial.println("Display Inicializado");
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  */

  //lastTime = millis(); // Definindo Tempo Inicial
  Serial.println("Sistema Pronto");
}

void loop() {
  // put your main code here, to run repeatedly:

  // Leitura TOF (mm)
  int distanceTOF = sensorTOF.readRangeContinuousMillimeters();

  // Leitura sensor ultrassÔnico (cm)
  int distanceUltra = sensorUltrasonic.ping_cm();

  // Detectar carrinho no tof
  if (distanceTOF < 50 && flag1 == 0){
    timer1 = millis();
    flag1 = 1;
    Serial.println("Carrinho passou pelo TOF");
    Serial.println("Distância");
    Serial.println(distanceTOF / 10.0);
  }

  // Dectectar carrinho no ultrassônico
  if (distanceUltra < 10 && timer1 > 0 && flag2 == 0){
    timer2 = millis();
    flag2 = 1;
    Serial.println("Carrinho passou pelo HC-SR04");
    Serial.println("Distância: ");
    Serial.println(distanceUltra);
  }

  // Calcular velocidade
  if (flag1 == 1 && flag2 == 1){
    Time = abs(timer2 - timer1) / 1000.0;
    velocidade = (distanceSensores / Time);
    Serial.println("Velocidade calculada: ");
    Serial.println(velocidade);
    Serial.print("cm/s")
    flag1, flag2 = 2;
  }

  

  /* Obter leituras do MPU
  mpu.getAcceleration(&ax, &ay, &az);

  // Cálculo da Velocidade
  unsigned long currentTime = millis();
  float deltaTime = (currentTime - lastTime) / 1000.0; // Convertendo para segundos
  lastTime = currentTime;

  // Converter a aceleração de raw para g (9.8 m/s²)
  float accelX = ax / 16384.0 * 9.8;

  // Calcular velocidade -> Velocidade = Velocidade_Anterior + Aceleração * Tempo
  velocidadeX += accelX * deltaTime;

  /* Limpar display
  display.clearDisplay();
  
  // Exibir informações no display
  display.setCursor(0, 0);
  display.print("Velocidade X - ");
  display.print(velocidadeX);
  display.print("m/s");

  display.setCursor(0, 20);
  display.print("Aceleracao X - ");
  display.print(accelX);
  display.print("m/s ^2");

  // Atualizar o display
  display.display();
  */
  // Delay
  delay(100);

}

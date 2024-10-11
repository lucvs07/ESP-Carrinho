// Projeto Física -> Medir acelaração e velocidade de um carrinho de brinquedo

// Importação de Bibliotecas
#include <Adafruit_GFX.h> // Biblioteca para o display oled
#include <Adafruit_SSD1306.h> // Biblioteca para o display oled
#include <Wire.h>
#include <MPU6050.h> // Biblioteca para o sensor MPU6050

// Definições do Display
#define width_display 128
#define height_display 64
#define reset_display -1
Adafruit_SSD1306 display(width_display, height_display, &Wire, reset_display);

// Definição MPU
MPU6050 mpu;

int16_t ax, ay, az; // Aceleração nos eixos
float velocidadeX = 0; // Velocidade no eixo X
unsigned long lastTime = 0; // Tempo para integração

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // Inicializando o monitor serial
  Wire.begin();

  // Inicializar o MPU
  mpu.initialize();
  if(!mpu.testConnection()){
    Serial.println("MPU não conectado");
    while(1);
  }

  // Inicializando o Display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
    Serial.println(F("Falha ao inicializar o display"));
    while(1);
  } else {
    Serial.println("Display Inicializado");
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  lastTime = millis(); // Definindo Tempo Inicial
}

void loop() {
  // put your main code here, to run repeatedly:

  // Obter leituras do MPU
  mpu.getAcceleration(&ax, &ay, &az);

  // Cálculo da Velocidade
  unsigned long currentTime = millis();
  float deltaTime = (currentTime - lastTime) / 1000.0; // Convertendo para segundos
  lastTime = currentTime;

  // Converter a aceleração de raw para g (9.8 m/s²)
  float accelX = ax / 16384.0 * 9.8;

  // Calcular velocidade -> Velocidade = Velocidade_Anterior + Aceleração * Tempo
  velocidadeX += accelX * deltaTime;

  // Limpar display
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

  // Delay
  delay(100);

}

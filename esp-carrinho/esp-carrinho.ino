// Projeto Física -> Medir acelaração e velocidade de um carrinho de brinquedo

// Importação de Bibliotecas
#include <Adafruit_GFX.h> // Biblioteca para o display oled
#include <Adafruit_SSD1306.h> // Biblioteca para o display oled
#include <Wire.h>

// Definições do Display
#define width_display 128
#define height_display 64
#define reset_display -1
Adafruit_SSD1306 display(width_display, height_display, &Wire, reset_display);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // Inicializando o monitor serial
  Wire.begin();

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
}

void loop() {
  // put your main code here, to run repeatedly:
  // Limpar display
  display.clearDisplay();
  
  // Exibir informações no display
  display.setCursor(0, 0);
  display.print("Velocidade - ");

  display.setCursor(0, 20);
  display.print("Aceleracao - ");

  // Atualizar o display
  display.display();

  // Delay
  delay(100);

}

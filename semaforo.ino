/*
  Projeto: Semáforo com Buzzer PASSIVO (Sem Transistor)
  Data: 17 de setembro de 2025

  Descrição:
  - Controla um semáforo com três LEDs (Verde, Amarelo, Vermelho).
  - Utiliza a técnica Push-Pull nos pinos 11 e 12 para maximizar o volume
    de um buzzer passivo sem a necessidade de um transistor.
  - Comportamento do som:
    - Sinal Verde: Bipes rápidos.
    - Sinal Vermelho: Som contínuo.
*/

// --- PINOS DOS LEDs ---
const int pinoLedVermelho = 10;
const int pinoLedAmarelo = 9;
const int pinoLedVerde = 8;

// --- PINOS DO BUZZER (MODO PUSH-PULL) ---
const int buzzerPin1 = 12;
const int buzzerPin2 = 11;

// Frequência do som em Hertz (Hz).
// Um valor alto (2000-4000) pode dar mais volume.
const int frequenciaSom = 3000;


/*
 * playPushPull: Função para gerar um tom usando dois pinos.
 * Esta é a melhor técnica de software para obter volume alto.
 */
void playPushPull(int pin1, int pin2, int frequency, long duration) {
  if (frequency <= 0) {
    delay(duration);
    return;
  }
  long halfPeriod = 1000000L / frequency / 2;
  long cycles = (long)frequency * duration / 1000;
  for (long i = 0; i < cycles; i++) {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
    delayMicroseconds(halfPeriod);
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
    delayMicroseconds(halfPeriod);
  }
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
}


void setup() {
  // Configura os pinos dos LEDs como SAÍDA.
  pinMode(pinoLedVermelho, OUTPUT);
  pinMode(pinoLedAmarelo, OUTPUT);
  pinMode(pinoLedVerde, OUTPUT);

  // Configura os pinos do buzzer como SAÍDA.
  pinMode(buzzerPin1, OUTPUT);
  pinMode(buzzerPin2, OUTPUT);
}


void loop() {
  // --- FASE 1: SINAL VERDE (BIPES RÁPIDOS) ---
  digitalWrite(pinoLedVerde, HIGH);
  digitalWrite(pinoLedAmarelo, LOW);
  digitalWrite(pinoLedVermelho, LOW);
  
  // Cria 5 segundos de bipes
  for (int i = 0; i < 20; i++) {
    playPushPull(buzzerPin1, buzzerPin2, frequenciaSom, 100); // Bipe
    delay(150); // Pausa
  }

  // --- FASE 2: SINAL AMARELO (SILÊNCIO) ---
  digitalWrite(pinoLedVerde, LOW);
  digitalWrite(pinoLedAmarelo, HIGH);
  digitalWrite(pinoLedVermelho, LOW);
  delay(2000);

  // --- FASE 3: SINAL VERMELHO (SOM CONTÍNUO) ---
  digitalWrite(pinoLedVerde, LOW);
  digitalWrite(pinoLedAmarelo, LOW);
  digitalWrite(pinoLedVermelho, HIGH);

  // Toca um som contínuo por 5 segundos.
  playPushPull(buzzerPin1, buzzerPin2, frequenciaSom, 5000);
}
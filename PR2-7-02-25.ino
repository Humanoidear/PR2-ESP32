#define PIN_INPUT 1  // Entrada ADC valor de la LDR
#define PIN_OUTPUT 14 // PIN al que se conecta el LED
#define CHAN 0 // Canal del PWM
#define LIGHT_MIN 372  // Valor mínimo de luz determinado por experimentación
#define LIGHT_MAX 4096 // Valor máximo en conversión de 12 bits

// Constantes del controlador (solo proporcional)
double kp=2, ki=0, kd=0;

// Variables del controlador
double Input, Output, Setpoint;
// variables internas del controlador
unsigned long currentTime, previousTime;
double elapsedTime;
double error, lastError, cumError, rateError;

void setup()
{
  Serial.begin(9600); // Inicializar puerto serie
  pinMode(PIN_INPUT, INPUT);

  // Configuración del PWM en el ESP32
  ledcSetup(CHAN, 1000, 12); // PWM de 1kHz con 12 bits de resolución
  ledcAttachPin(PIN_OUTPUT, CHAN); // Asociar el PWM al PIN del LED

  Setpoint = (LIGHT_MIN + LIGHT_MAX) / 2; // Nivel medio de luz
}

void loop()
{
  Input = analogRead(PIN_INPUT); // Leer la LDR
  Output = computePID(Input); // Calcular el PID (solo P en este caso)

  // Asegurar que la salida esté en el rango de PWM (0 a 4095)
  Output = constrain(Output, 0, 4095);

  // Escribir la salida al LED
  ledcWrite(CHAN, Output);

  // Mostrar valores en Serial Plotter
  Serial.print(Input);
  Serial.print(",");
  Serial.println(Output);

  delay(100);
}

double computePID(double inp)
{
  currentTime = millis();// obtener el tiempo actual
  elapsedTime = (double)(currentTime - previousTime);// calcular el tiempo transcurrido
  error = Setpoint - Input;// determinar el error entre la consigna y la medición
  cumError += error * elapsedTime;// calcular la integral del error
  rateError = (error - lastError) / elapsedTime; // calcular la derivada del error
  double output = kp*error + ki*cumError + kd*rateError; // calcular la salida del PID 
  lastError = error; // almacenar error anterior
  previousTime = currentTime; // almacenar el tiempo anterior
  return output;
}

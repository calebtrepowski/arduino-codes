// Sensor Ultrasonico
#define PIN_ECHO 53
#define PIN_TRIGG 51
// Pin de señal de la valvula
#define PIN_VALVE 10 //HIGH carga, LOW no carga
// Mediciones
#define DISTANCIA_LLENO 10               //cm
#define DISTANCIA_VACIO 20               //cm
#define DISTANCIA_MAXIMA_CONSIDERABLE 50 //cm
#define INTERVALO_MEDICIONES 0.5         //segundos
#define CANTIDAD_MEDICIONES 5            //mediciones
#define TIEMPO_ESPERA_CONTROL 1          // minutos

/**
 * Variable global para almacenar el promedio de distancia
*/
unsigned int distancia_promedio;
/**
 * Variable global para almacenar la cantidad de distancias
 * invalidas durante un ciclo de obtencion del promedio
*/
unsigned int cantidad_distancias_invalidas;

// Funciones

unsigned int get_distancia();
unsigned int get_distancia_promedio();
void set_cargar_valvula(bool salida);

void setup()
{
  //Serial.begin(9600);
  pinMode(PIN_TRIGG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_VALVE, OUTPUT);
}

/**
 * 
 * Obtiene la distancia promedio,
 * compara con la distancia de llenado:
 *    si se necesita cargar activa la valvula,
 *    si no se necesita cargar desactiva la valvula.
 * Espera {TIEMPO_ESPERA_CONTROL} minutos para empezar de nuevo.
 * 
*/
void loop()
{
  distancia_promedio = get_distancia_promedio();
  while (distancia_promedio > DISTANCIA_LLENO)
  {
    set_cargar_valvula(true);
    delay(100);
    distancia_promedio = get_distancia_promedio();
  }
  set_cargar_valvula(false);

  //delay(1000L * 60 * TIEMPO_ESPERA_CONTROL);

  delay(7000);
}

/**
 * Retorna la distancia en cm leida por el sensor ultrasonico
*/
unsigned int get_distancia()
{
  unsigned int tiempo, distancia;
  digitalWrite(PIN_TRIGG, LOW);
  delayMicroseconds(5);
  digitalWrite(PIN_TRIGG, HIGH);
  delayMicroseconds(10);
  tiempo = pulseIn(PIN_ECHO, HIGH);
  distancia = int(0.017 * tiempo);
  //Serial.print("Distancia: ");
  //Serial.println(distancia);
  return distancia;
}

/**
 * Retorna el promedio de una cantidad {CANTIDAD_MEDICIONES}
 * medidos cada {INTERVALO_MEDICIONES} segundos
*/
unsigned int get_distancia_promedio()
{
  unsigned int promedio = 0, distancia;
  cantidad_distancias_invalidas = 0;
  for (char i = 0; i < CANTIDAD_MEDICIONES; i++)
  {
    if (cantidad_distancias_invalidas >= CANTIDAD_MEDICIONES)
    {
      //Serial.println("Cortando la carga por seguridad");
      set_cargar_valvula(false);
      return 0;
    }
    delay(INTERVALO_MEDICIONES * 1000); // conversion de segundos a milisegundos
    distancia = get_distancia();

    if (distancia > DISTANCIA_MAXIMA_CONSIDERABLE || distancia == 0)
    {
      /**
       * se toman como invalidas distancias iguales a 0
       * o mayores a {DISTANCIA_MAXIMA_CONSIDERABLE}
      */
      cantidad_distancias_invalidas++;
      //Serial.println("Distancia invalida");
      i--;
      continue;
    }
    else
    {
      promedio += distancia;
    }
  }
  promedio /= CANTIDAD_MEDICIONES;
  //Serial.print("Promedio de mediciones: ");
  //Serial.println(promedio);
  return promedio;
}

/**
 * Asigna HIGH cuando {salida} es true
 * Asigna LOW cuando {salida} es false
 * El relay que controla la valvula es normalmente abierto
*/
void set_cargar_valvula(bool salida)
{
  if (salida)
  {
    //Serial.println("Cargando");
    digitalWrite(PIN_VALVE, HIGH);
    return;
  }
  //Serial.println("Pausando carga");
  digitalWrite(PIN_VALVE, LOW);
}

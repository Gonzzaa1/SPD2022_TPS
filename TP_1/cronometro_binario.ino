
/*
 *	Trabajo Práctico 1: Cronómetro Binario
 *
 *	Al iniciar la simulacion, todos los led deben comenzar apagados.
 *	Cada 1 segundo que transcurra, se deben encender los led
 *	de acuerdo al numero que representan.
 *
 *	Ejemplo:
 *   
 *	El numero 15 (0000001111) se representaria encendiendo los 
 *	leds AMARILLO y NARANJA.
 *	Al pasar al numero 16 (0000010000), se deben apagar todos 
 *	los led anteriores y encenderse uno de los leds VERDES. 
 *	Notese, en el ejemplo los 0 representan los led apagados 
 *	y los 1 los led encendidos). 
 *   
 *	-------------------------------------------------------
 *   
 *	Al presionarse el boton START, debe iniciar el cronometro.
 *	Volver a presionarlo hace que la secuencia se detenga. 
 *  (Como si se hubiese presionado pausa).
 *	Al presionarse el boton RESET, el cronometro
 *	debe reiniciarse y arrancar de 0.
 *
 *	Tip: Modularizar la función que controla el encendido de los 
 *	LEDS y de ser posible, todo el código para evitar repetir lineas lo mas posible.
 *  Usar millis para controlar el tiempo del contador para que el cambio de los 
 *	leds encendidos sea perceptible para el ojo humano y 
 *	documentar cada función creada en el código. 
 *	Un breve comentario que diga que es lo que hace esa función
 *  y de corresponder, que retorna).
*/

//##### Una Ayudita #####
//--- Defines ---//
#define ZERO_TO_HERO 0          //? To start the counter from 0
#define BUTTON_START 2
#define BUTTON_RESET 3
#define FIRST_LED 4             //? First pin of the leds
#define LAST_LED 13             //? Last pin of the leds
#define BASE_MILLI_SECONDS 1000 //? Secods expresed in miliseconds
#define MAX_SECONDS 1023        //! Max amount of secods to show
//--- End Defines ---//

int pines[10]={4,5,6,7,8,9,10,11,12,13};

void setup()
{
  	Serial.begin(9600);
  
  //creo un for para recorrer mi array de pines y setearlos como OUTPUT
  	for(int i = 0 ; i <= 10;i++)
    {
      pinMode(pines[i],OUTPUT);
    }
  //Seteo los botones como INPUT	
  	pinMode(BUTTON_RESET,INPUT);
  	pinMode(BUTTON_START,INPUT);
  
}

unsigned long millisAntes = ZERO_TO_HERO;

int timer = ZERO_TO_HERO;
int bin = ZERO_TO_HERO;
int binario = ZERO_TO_HERO;
int flag;
int num;

String segundos = "Seconds: ";
String binarios = " | Binary: ";

void loop()
{  
  unsigned long millisAhora = millis();
  //uso la funcion millis() para setear el loop como si fuera cada 1 segundo
  if(millisAhora - millisAntes >= BASE_MILLI_SECONDS)
  {
    	cronoBinario();
    	millisAntes = millisAhora;
  }
  delay(20);
}

//Funcion que me prende los LEDs
void prenderLed()
{
  //un ++ a mi variable que guarda mi numero
  //de donde vamos a sacar el numero binario
    binario++;
  
  //pregunto si binario es mayor/igual a 0 o menor/igual a 1023
    if(binario >= ZERO_TO_HERO && binario <= MAX_SECONDS)
    {
      //si se cumple la condicion asigno el numero que tengo guardado en binario
      //en num
        num = binario;
		
      	// creo un for para recorrer mi array de pines
        for(int i=0; i < 10; i++)
        {
          //si el resto de numero es = 1
          // prendo el Led del pin[i]
            if(num % 2 == 1)
            {
              digitalWrite(pines[i], HIGH);
            }
          //si no lo apago
            else
            {
              digitalWrite(pines[i],LOW);
            }
          //luego divido al numero 2 para sacar el proximo binario
          	num = num /2;
        }
    }
}
//Funcion de mi boton Start/Pause
void start()
{
  //variable que me lee el boton start
  int botonStart = digitalRead(BUTTON_START);
  	
  //si el boton = 1,  digo que me cambio de valor la bandera
  if(botonStart)
  {
    flag = !flag;
  }
  //si mi bandera es = 1 y el numero binario es menor/igual a 1023
  //prendo los leds, inicio el contador y muestro el mensaje por consola
  if(flag && binario <= MAX_SECONDS)
  {
    prenderLed();
    timer++;
	mostrarConsola();
  }
}
//Funcion de mi Boton de reset
void reset()
{
  //variable que me lee el boton reset
  int botonReset = digitalRead(BUTTON_RESET);
  
  //si el boton es = 1
  //seteo la bandera en 1 para que arrequen los leds
  //y seteo el timer y el numero binario en 0
  if(botonReset)
  {
    flag = 1;
    timer = ZERO_TO_HERO;
    binario = ZERO_TO_HERO;
  }
}
//Funcion que me muestra el tiempo y
//el numero binario en consola
void mostrarConsola()
{
  //si binario es menor/igual a 1023 muestro mensaje en consola
  	if(binario <= MAX_SECONDS)
  	{
      
  		Serial.println(segundos + timer + binarios+
                 			 		digitalRead(13)+ 
                             		digitalRead(12)+ 
                             		digitalRead(11)+ 
                             		digitalRead(10)+ 
                             		digitalRead(9)+ 
                             		digitalRead(8)+ 
                             		digitalRead(7)+ 
                             		digitalRead(6)+ 
                             		digitalRead(5)+
                 			 		digitalRead(4));
	}
}
//Funcion que me apaga todos los LEDs
void apagarLed()
{
  //for que recorre mi array de pines y los apaga
  	for(int i = 0; i < 11;i++)
    {
       digitalWrite(pines[i],LOW);
    }
}
//Funcion donde esta las funciones de mi cronometro
void cronoBinario()
{
  	start();
    reset();
  
  //si llega al valor maximo apaga los leds
  	if(binario >= MAX_SECONDS)
    {
       apagarLed();
    }
}


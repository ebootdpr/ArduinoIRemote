
#include <IRremote.h>
#include <IRremoteInt.h>

int LuzDelanteraIzquierda = 2;
int LuzDelanteraDerecha= 4;
int LuzTraseraIzquierda = 7;
int LuzTraseraDerecha = 12;
int ledTest = 13;

int MemoryLastIf=0;
double contador=0;

int ReceptorIR = 8;                     // Declaramos que usaremos el pin 8 (asociado a la variable ReceptorIR) como entrada del control remoto. 
IRrecv receptorIr(ReceptorIR);          // Creamos un objeto de la clase IRrecv llamado "receptorIr"

decode_results codigoLeido;              //declaramos 2 variables de tipo decode_results llamadas "codigoLeido" y "codigoLeidoNuevo"
decode_results codigoLeidoNuevo;

const int AIA = 3; 
const int AIB = 11;
const int BIA = 10; 
const int BIB = 9;

void setup() {

    //indicar los pines de salida
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(12, OUTPUT);
  //apagar todos los leds
  digitalWrite(2, LOW);
  digitalWrite(4, LOW);
  digitalWrite(7, LOW);
  digitalWrite(12, LOW);
  /*
     Seteo receptor infrarojo
  */
  Serial.begin(9600);
  receptorIr.enableIRIn();     // Habilitamos al receptor para que comience a intentar detectar señales infrarrojas.

  
  pinMode(AIA, OUTPUT); 
  pinMode(AIB, OUTPUT);
  pinMode(BIA, OUTPUT);
  pinMode(BIB, OUTPUT);
 

  analogWrite(AIA, 0);
  analogWrite(AIB, 0);
  analogWrite(BIA, 0);
  analogWrite(BIB, 0);


  pinMode(ledTest, OUTPUT);
  digitalWrite(ledTest, LOW);

  }


void loop() {  
 if (receptorIr.decode(&codigoLeidoNuevo))
  {
   receptorIr.resume();
   Serial.println(codigoLeidoNuevo.value, HEX); 
   if(codigoLeidoNuevo==0xFFFFFF) 
    {
     contador=0;
    } 
  }
   if(MemoryLastIf != 0) 
    {
    contador++;
    } 
  
  if (contador > 5)
  {
    MemoryLastIf=0;
    contador=0;
    parar();
  }
  // Serial.println(codigoLeidoNuevo.value, HEX); 
   codigoLeido = codigoLeidoNuevo;     

      if (codigoLeidoNuevo.value == 0xFF9867 || MemoryLastIf == 1 ){  //Avanzar    
        adelante();
        MemoryLastIf == 1;
         }                      
      if (codigoLeidoNuevo.value == 0xFF38C7 || MemoryLastIf == 2 ){ //RETROCEDER       
        atras();
       MemoryLastIf == 2;
         } 
      if (codigoLeidoNuevo.value == 0xFF18E7 || MemoryLastIf == 3 ){ //RETROCEDER       
        parar();
       MemoryLastIf == 3;
         } 
    codigoLeidoNuevo.value=0xFFFFFFFF;
  }

void adelante()
{
  analogWrite(AIA, 255);
  analogWrite(AIB, 0);
  delay(50); //Para evitar pico de consumo
  analogWrite(BIA, 255);
  analogWrite(BIB, 0);
}

 //colocamos en alto los IB y en bajo los IA de los dos motores
 
void atras()
{
  analogWrite(AIA, 0);
  analogWrite(AIB, 255);
  delay(50); //Para evitar pico de consumo
  analogWrite(BIA, 0);
  analogWrite(BIB, 255);
  
}

//Combinamos adelante y atras

void derecha()
{
  analogWrite(AIA, 255);
  analogWrite(AIB, 0);
  delay(50); //Para evitar pico de consumo
  analogWrite(BIA, 0);
  analogWrite(BIB, 255);
}


//Combinamos adelante y atras pero de forma diferente

void izquierda()
{
  analogWrite(AIA, 0);
  analogWrite(AIB, 255);
  delay(50); //Para evitar pico de consumo
  analogWrite(BIA, 255);
  analogWrite(BIB, 0);
  
}


//Colocamos los dos valores en alto

void parar()
{
  analogWrite(AIA, 255);
  analogWrite(AIB, 255);
  delay(50); //Para evitar pico de consumo
  analogWrite(BIA, 255);
  analogWrite(BIB, 255);
  delay(50);
  analogWrite(AIA, 0);
  analogWrite(AIB, 0);
  delay(50); //Para evitar pico de consumo
  analogWrite(BIA, 0);
  analogWrite(BIB, 0);
  delay(500);
}
//modificar
void parpadeo(int ledParpadea, int veces, int tiempo){
    for(int j=0; j<=veces; j++){
      digitalWrite(ledParpadea, LOW);
      delay(tiempo); 
      digitalWrite(ledParpadea, HIGH);
      delay(tiempo);
    }
    }

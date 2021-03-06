//Desarrolado para la plaforma Tinkercad
#include <LiquidCrystal.h>
//Luego de importar la biblioteca, declaramos los pines en el LCD
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
//Semáforo Vehicular:
const int vRojo = 12;
const int vAmarillo = 11;
const int vVerde = 10;
//Semáforo Peatonal:
const int pRojo = 9;
const int pVerde = 8;
//Botón de semaforo:
const int boton = 13;
//Declaración de variables | Estado de Botón | Tiempos |
int estadoBoton = 0;
int tiempovVerde = 10;	//Tiempo vehicular, luz LED Verde
int tiempovAmarillo = 10; //Tiempo vehicular, luz LED Amarilla

int tiempopRojo = 20;		//Tiempo de Peaton, luz LED Rojo
int tiempopVerde = 10;    //Tiempo de Peaton, luz LED Verde
bool presionado = false;

void setup() {
    //Salida:
    lcd.begin(16, 2);
    pinMode(vRojo, OUTPUT);
    pinMode(vAmarillo, OUTPUT);
    pinMode(vVerde, OUTPUT);
    pinMode(pRojo, OUTPUT);
    pinMode(pVerde, OUTPUT);
    //Entrada:
    pinMode(boton, INPUT);
}

void loop() {
    if (presionado == false) {
        estadoBoton = digitalRead(boton);
    }

    /*Cuando alguien aprieta el boton durante el lazpso
    de tiempo para cruzar (Debido a que es muy poco tiempo),
    este reduce el tiempo de espera(a la mitad), para el proximo */
    if (estadoBoton == HIGH) {
        tiempopRojo = 10;
        semaforo();
        presionado = true;
        estadoBoton = LOW;
    }
    //De no ser el caso, el semaforo seguira con su tiempo estimado
    else {
        semaforo();
    }
}//fin de loop


void semaforo() {

    if (tiempopRojo != 0) {
        //la variable "tiempopRojo" nos ayudara a tener el tiempo de:
        //El paso de vehicular o tambien visto como la espera del peaton

            //Prende las luces del Semaforo verde(Vehiculo) con su tiempo estimado
        if (tiempovVerde <= tiempopRojo) {
            digitalWrite(vVerde, HIGH);
            digitalWrite(pRojo, HIGH);
        }
        else {
            digitalWrite(vVerde, LOW);
            //Parpadea el LED amarillo, para prevenir y avisar que pasara a 
            //la siguiente LUZ (Roja)
            digitalWrite(vAmarillo, HIGH);
            delay(500);
            digitalWrite(vAmarillo, LOW);
        }
        //Prende el Led Rojo(Peatonal)
        digitalWrite(pRojo, HIGH);


        //Entrega por el LCD un contador para el Peaton
        lcd.setCursor(0, 0);
        lcd.print("Favor de Esperar");
        lcd.setCursor(0, 1);
        lcd.print("Tiempo: ");
        lcd.setCursor(11, 2);
        lcd.print(tiempopRojo);
        // se resta 1 a "tiempopRojo"
        tiempopRojo--;
        delay(1000);//Esperamo 1 segundo
        if (tiempopRojo == 9)//Limpiador de pantalla en el numero 9
            lcd.clear();
    }

    if (tiempopRojo == 0) {
        //APAGA las luz LED Roja(Peatonal)
        digitalWrite(pRojo, LOW);

        //Prende las luces del Semaforo Rojo(Vehiculo) y Verde(Peaton)
        //(Este es el unico tiempo que no cambia 10seg.Peáton)
        digitalWrite(vRojo, HIGH);
        digitalWrite(pVerde, HIGH);

        //Entrega por el LCD un contador para el Peaton 
        if (tiempopVerde != 0) {
            lcd.setCursor(0, 0);
            lcd.print("Puede Avanzar");
            lcd.setCursor(0, 1);
            lcd.print("Tiempo: ");
            lcd.setCursor(11, 1);
            lcd.print(tiempopVerde);
            tiempopVerde--;
            delay(1000);//Hacemos pasar 1 seg.
            if (tiempopVerde == 9)//Limpiador de pantalla en el numero 9
                lcd.clear();
        }
        //Reinicia los valores de las variables
        if (tiempopVerde == 0) {
            lcd.clear();
            tiempopRojo = 20;
            tiempopVerde = 10;
            estadoBoton = LOW;
            presionado = false;

            //APAGA las luces del Semaforo Rojo(Vehiculo) y Verde(Peaton)
            digitalWrite(vRojo, LOW);
            digitalWrite(pVerde, LOW);
        }
    }
}
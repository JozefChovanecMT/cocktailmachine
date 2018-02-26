/*
 * Automatická miešačka nápojov riadená Arduinom
 * Software: Jozef Chovanec
 * Hardware: Ľubomír Csicsai
 */

//zadefinovanie pinov na solenoidy
#define Solenoid_1 2
#define Solenoid_2 3
#define Solenoid_3 4
#define Solenoid_4 5
#define Solenoid_5 6
#define Solenoid_6 7

#include <Stepper.h> //kniznica na krokovy motor

int prepinac; //switch                    
int dlzka_pasu = 15000; //dlzka pasu                            
int rychlost_pasu = 100; //rychlost                          

//piny na motor
int dirPin = 8;
int stepPin = 9;

int cas_nalievania = 3000; //cas nalievania napoja, definuje aj jeho objem
int cas_posunu = 5000; //cas presunu pasu ku inemu napoju

void setup() {
  Serial.begin(9600);  //pripojenie ku seriovemu rozhraniu
  Serial.print("Prosim zadajte poradie namiesania vo formate [prvy],[druhy],[treti] ");

  //inicializovanie pinov na solenoidoch
  pinMode(Solenoid_1, OUTPUT);
  pinMode(Solenoid_2, OUTPUT);
  pinMode(Solenoid_3, OUTPUT);
  pinMode(Solenoid_4, OUTPUT);
  pinMode(Solenoid_5, OUTPUT);
  pinMode(Solenoid_6, OUTPUT);

  //inicializovanie pinov na krokovy motor
  pinMode(dirPin, OUTPUT);      
  pinMode(stepPin, OUTPUT);
  digitalWrite(dirPin, LOW);
  digitalWrite(stepPin, LOW);
  prepinac = 1;

}

void loop() {

  //zapnutie do stavu ON
  digitalWrite(Solenoid_1, LOW);
  digitalWrite(Solenoid_2, LOW);
  digitalWrite(Solenoid_3, LOW);
  digitalWrite(Solenoid_4, LOW);
  digitalWrite(Solenoid_5, LOW);
  digitalWrite(Solenoid_6, LOW);

  delay(1000);
  
if (Serial.available() > 0) //cakanie na odpoved
  {
  for(int i=1; i<=3; i++) {
        String prvy = Serial.readStringUntil(','); //precitanie hodnoty prveho napoja
        if(prvy != ""){
            String druhy = Serial.readStringUntil(','); //precitanie hodnoty druheho napoja
            if(druhy != ""){
            String treti = Serial.readStringUntil(','); //precitanie hodnoty tretieho napoja
           
            Serial.print("\nNamiesavam napoj v nasledujucom poradi: \n");
            Serial.print(prvy);
            Serial.print("\n");
            Serial.print(druhy);
            Serial.print("\n");
            Serial.print(treti);

    //skonvertiovanie na integer
    int prvy_int = prvy.toInt();
    int druhy_int = druhy.toInt();
    int treti_int = treti.toInt();

    
    //osetrenie pre pripad vpisania chybnej hodnoty
    if(prvy_int > 6 or prvy_int < 1)
    {
      Serial.print("\n Error: Iba cislo od 1-6 !\n");
      break;
    }

    if(druhy_int > 6 or druhy_int < 1)
    {
      Serial.print("\n Error: Iba cislo od 1-6 !\n");
      break;
    }

    if(treti_int > 6 or treti_int < 1)
    {
      Serial.print("\n Error: Iba cislo od 1-6 !\n");
      break;
    }
    delay(3000);

    if (prepinac < dlzka_pasu + 1)            // Je stale v prvej pozici ?
    {
      digitalWrite(dirPin, LOW);      // vypne pin smerovania
    }
    else
    {
      digitalWrite(dirPin, HIGH);    // zapne pin smerovania
    }
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(rychlost_pasu);  // vycka urcitu dobu
      digitalWrite(stepPin, LOW);
      delayMicroseconds(rychlost_pasu);  // vycka urcitu dobu
      prepinac += 1;                       // pocitanie smeru posunu
    if (prepinac > dlzka_pasu * 2)           // ak prejdeme obydva smery
    { prepinac = 1; }                  // restartujeme prepinac spat

    // ziskanie hodnoty prveho napoja
    if(prvy_int == 1)
    {
      digitalWrite(Solenoid_1, HIGH); // otvori solenoid
      Serial.print("\nNapoj c.1 sa nalieva... \n");
      delay(cas_nalievania);
      digitalWrite(Solenoid_1, LOW); // zavrie solenoid
      Serial.print("Napoj c.1 sa nalial. \n");
    }

    if(prvy_int == 2)
    {
      digitalWrite(Solenoid_2, HIGH);
      Serial.print("\nNapoj c.2 sa nalieva... \n");
      delay(cas_nalievania);
      digitalWrite(Solenoid_2, LOW);
      Serial.print("Napoj c.2 sa nalial. \n");
    }

    if(prvy_int == 3)
    {
      digitalWrite(Solenoid_3, HIGH);
      Serial.print("\nNapoj c.3 sa nalieva... \n");
      delay(cas_nalievania);
      digitalWrite(Solenoid_3, LOW);
      Serial.print("Napoj c.3 sa nalial. \n");
    }

    if(prvy_int == 4)
    {
      digitalWrite(Solenoid_4, HIGH);
      Serial.print("\nNapoj c.4 sa nalieva... \n");
      delay(cas_nalievania);
      digitalWrite(Solenoid_4, LOW);
      Serial.print("Napoj c.4 sa nalial. \n");
    }

    if(prvy_int == 5)
    {
      digitalWrite(Solenoid_5, HIGH);
      Serial.print("\nNapoj c.5 sa nalieva... \n");
      delay(cas_nalievania);
      digitalWrite(Solenoid_5, LOW);
      Serial.print("Napoj c.5 sa nalial. \n");
    }

    if(prvy_int == 6)
    {
      digitalWrite(Solenoid_6, HIGH);
      Serial.print("\nNapoj c.6 sa nalieva... \n");
      delay(cas_nalievania);
      digitalWrite(Solenoid_6, LOW);
      Serial.print("Napoj c.6 sa nalial. \n");
    }
    
    if (prepinac < dlzka_pasu + 1)            // Je stale v prvej pozici ?
    {
      digitalWrite(dirPin, LOW);      // vypne pin smerovania
    }
    else
    {
      digitalWrite(dirPin, HIGH);    // zapne pin smerovania
    }
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(rychlost_pasu);  // vycka urcitu dobu
      digitalWrite(stepPin, LOW);
      delayMicroseconds(rychlost_pasu);  // vycka urcitu dobu
      prepinac += 1;                       // pocitanie smeru posunu
    if (prepinac > dlzka_pasu * 2)           // ak prejdeme obydva smery
    { prepinac = 1; }                  // restartujeme prepinac spat

    delay(cas_posunu);

    // ziskanie hodnoty druheho napoja
    if(druhy_int == 1)
    {
      digitalWrite(Solenoid_1, HIGH);
      Serial.print("\nNapoj c.1 sa nalieva... \n");
      delay(cas_nalievania);
      digitalWrite(Solenoid_1, LOW);
      Serial.print("Napoj c.1 sa nalial. \n");
    }

    if(druhy_int == 2)
    {
      digitalWrite(Solenoid_2, HIGH);
      Serial.print("\nNapoj c.2 sa nalieva... \n");
      delay(cas_nalievania);
      digitalWrite(Solenoid_2, LOW);
      Serial.print("Napoj c.2 sa nalial. \n");
    }

    if(druhy_int == 3)
    {
      digitalWrite(Solenoid_3, HIGH);
      Serial.print("\nNapoj c.3 sa nalieva... \n");
      delay(cas_nalievania);
      digitalWrite(Solenoid_3, LOW);
      Serial.print("Napoj c.3 sa nalial. \n");
    }

    if(druhy_int == 4)
    {
      digitalWrite(Solenoid_4, HIGH);
      Serial.print("\nNapoj c.4 sa nalieva... \n");
      delay(cas_nalievania);
      digitalWrite(Solenoid_4, LOW);
      Serial.print("Napoj c.4 sa nalial. \n");
    }

    if(druhy_int == 5)
    {
      digitalWrite(Solenoid_5, HIGH);
      Serial.print("\nNapoj c.5 sa nalieva... \n");
      delay(cas_nalievania);
      digitalWrite(Solenoid_5, LOW);
      Serial.print("Napoj c.5 sa nalial. \n");
    }

    if(druhy_int == 6)
    {
      digitalWrite(Solenoid_6, HIGH);
      Serial.print("\nNapoj c.6 sa nalieva... \n");
      delay(cas_nalievania);
      digitalWrite(Solenoid_6, LOW);
      Serial.print("Napoj c.6 sa nalial. \n");
    }

    if (prepinac < dlzka_pasu + 1)            // Je stale v prvej pozici ?
    {
      digitalWrite(dirPin, LOW);      // vypne pin smerovania
    }
    else
    {
      digitalWrite(dirPin, HIGH);    // zapne pin smerovania
    }
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(rychlost_pasu);  // vycka urcitu dobu
      digitalWrite(stepPin, LOW);
      delayMicroseconds(rychlost_pasu);  // vycka urcitu dobu
      prepinac += 1;                       // pocitanie smeru posunu
    if (prepinac > dlzka_pasu * 2)           // ak prejdeme obydva smery
    { prepinac = 1; }                  // restartujeme prepinac spat
    */

    delay(cas_posunu);
    
    // ziskanie hodnoty tretieho napoja
    if(treti_int == 1)
    {
      digitalWrite(Solenoid_1, HIGH);
      Serial.print("\nNapoj c.1 sa nalieva... \n");
      delay(cas_nalievania);
      digitalWrite(Solenoid_1, LOW);
      Serial.print("Napoj c.1 sa nalial. \n");
    }

    if(treti_int == 2)
    {
      digitalWrite(Solenoid_2, HIGH);
      Serial.print("\nNapoj c.2 sa nalieva... \n");
      delay(cas_nalievania);
      digitalWrite(Solenoid_2, LOW);
      Serial.print("Napoj c.2 sa nalial. \n");
    }

    if(treti_int == 3)
    {
      digitalWrite(Solenoid_3, HIGH);
      Serial.print("\nNapoj c.3 sa nalieva... \n");
      delay(cas_nalievania);
      digitalWrite(Solenoid_3, LOW);
      Serial.print("Napoj c.3 sa nalial. \n");
    }

    if(treti_int == 4)
    {
      digitalWrite(Solenoid_4, HIGH);
      Serial.print("\nNapoj c.4 sa nalieva... \n");
      delay(cas_nalievania);
      digitalWrite(Solenoid_4, LOW);
      Serial.print("Napoj c.4 sa nalial. \n");
    }

    if(treti_int == 5)
    {
      digitalWrite(Solenoid_5, HIGH);
      Serial.print("\nNapoj c.5 sa nalieva... \n");
      delay(cas_nalievania);
      digitalWrite(Solenoid_5, LOW);
      Serial.print("Napoj c.5 sa nalial. \n");
    }

    if(treti_int == 6)
    {
      digitalWrite(Solenoid_6, HIGH);
      Serial.print("\nNapoj c.6 sa nalieva... \n");
      delay(cas_nalievania);
      digitalWrite(Solenoid_6, LOW);
      Serial.print("Napoj c.6 sa nalial. \n");
    }

      Serial.print("Napoj uspesne namiesany \n");

    if (prepinac < dlzka_pasu + 1)            // Je stale v prvej pozici ?
    {
      digitalWrite(dirPin, LOW);      // vypne pin smerovania
    }
    else
    {
      digitalWrite(dirPin, HIGH);    // zapne pin smerovania
    }
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(rychlost_pasu);  // vycka urcitu dobu
      digitalWrite(stepPin, LOW);
      delayMicroseconds(rychlost_pasu);  // vycka urcitu dobu
      prepinac += 1;                       // pocitanie smeru posunu
    if (prepinac > dlzka_pasu * 2)           // ak prejdeme obydva smery
    { prepinac = 1; }                  // restartujeme prepinac spat
    
            }
        }
    }
}
}

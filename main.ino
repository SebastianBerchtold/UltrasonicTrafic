#include <Ultrasonic.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

Ultrasonic ultrasonic3(13);		// An Seeed Studio ultrasonic sensor


int entf;
long autoanzahl=0; // Gesamtautoanzahl
int laenge =5;  //mindestanzahl an Messung bis es als Fahrzeug erkannt wird
int zaehler =0;
int mindest= 200; // Sobald diese Mindestentfernung unterschritten wird wird detektiert

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Autos: ");

}

void loop() {

  entf = (ultrasonic3.read(CM));
  int entfernung = entf;

  lcd.setCursor(7,0);
  lcd.print(autoanzahl);
  lcd.setCursor(0,1);
  lcd.print (entf);
  lcd.print ("cm  ");

  zaehler=0;

  while (entf <= mindest){
    Serial.print("Wert kleiner mindestabstand:  ");
    Serial.println(entf);
    Serial.print("Anzahl der Messungen kleiner: ");
    Serial.println(zaehler);
    entf = (ultrasonic3.read(CM));
    zaehler=zaehler+1;
    if (zaehler > laenge){
      autoanzahl = autoanzahl+1;
      Serial.println("Fahrzeug erkannt");
      Serial.println("Warte bis Fahrzeug vorbei...");
      while (entf<=mindest){
        entf = (ultrasonic3.read(CM));

      }
    }
  }

  delay(10);
}

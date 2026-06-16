# PCF8575_LCD_V2

Bibliothèque Arduino permettant de piloter un afficheur LCD HD44780 et un clavier matriciel à l'aide d'un expandeur d'E/S I²C PCF8575.

## Fonctionnalités

- Pilotage des afficheurs HD44780 en mode 4 bits
- Compatible LCD 16x2, 20x4 et dérivés
- Basée sur la classe Arduino `Print`
- Positionnement du curseur
- Effacement de ligne
- Centrage de texte
- Barre de progression
- Gestion des claviers matriciels 3x4 et 4x4
- Support optionnel des interruptions du PCF8575
- Compatible AVR, ESP8266 et ESP32

---

## Répartition des broches

### LCD

| LCD | PCF8575 |
|------|------|
| RS | P0 |
| EN | P1 |
| D4 | P2 |
| D5 | P3 |
| D6 | P4 |
| D7 | P5 |

### Clavier matriciel

| PCF8575 | Fonction |
|----------|----------|
| P6 | Ligne 1 |
| P7 | Ligne 2 |
| P8 | Ligne 3 |
| P9 | Ligne 4 |
| P10 | Colonne 1 |
| P11 | Colonne 2 |
| P12 | Colonne 3 |

### Rétroéclairage LCD

| PCF8575 | Fonction |
|----------|----------|
| P13 | Backlight LCD |

### Broches disponibles

| PCF8575 |
|----------|
| P14 |
| P15 |

---

## Installation

Copiez le dossier de la bibliothèque dans :

```text
Documents/Arduino/libraries
```

ou installez-la depuis le gestionnaire de bibliothèques Arduino.

---

# Exemple LCD

```cpp
#include <Wire.h>
#include "PCF8575.h"
#include "LCD_HD44780_PCF8575.h"

PCF8575 pcf(0x20);
LCD_HD44780_PCF8575 lcd(pcf);

void setup()
{
    Wire.begin();

    pcf.begin();

    lcd.begin(20,4);

    lcd.printAt(0,0,"Bonjour");
    lcd.printAt(0,1,"Mon LCD");
}

void loop()
{
}
```

---

# Exemple clavier

```cpp
#include <Wire.h>

#include "PCF8575.h"
#include "LCD_HD44780_PCF8575.h"
#include "Keypad_PCF8575.h"

PCF8575 pcf(0x20);
LCD_HD44780_PCF8575 lcd(pcf);

uint8_t rows[] = {6,7,8,9};
uint8_t cols[] = {10,11,12};

const char keys[] =
{
    '1','2','3',
    '4','5','6',
    '7','8','9',
    '*','0','#'
};

Keypad_PCF8575 keypad(
    pcf,
    rows,4,
    cols,3,
    keys
);

void setup()
{
    Wire.begin();

    pcf.begin();

    lcd.begin(20,4);

    keypad.begin();
}

void loop()
{
    char key = keypad.getKey();

    if(key)
    {
        lcd.print(key);
    }
}
```

---

# Exemple de câblage clavier 3x4

| Broche clavier | Fonction | PCF8575 |
|---------------|----------|----------|
| 1 | Colonne 2 | P11 |
| 2 | Ligne 4 | P9 |
| 3 | Colonne 3 | P12 |
| 4 | Ligne 1 | P6 |
| 5 | Colonne 1 | P10 |
| 6 | Ligne 2 | P7 |
| 7 | Ligne 3 | P8 |

---

# Fonctions PCF8575

```cpp
pcf.begin();
pcf.isConnected();

pcf.digitalWrite(pin, valeur);
pcf.digitalRead(pin);

pcf.write16(valeur);
pcf.read16();
```

---

# Fonctions LCD

```cpp
lcd.begin(colonnes,lignes);

lcd.clear();
lcd.home();

lcd.setCursor(colonne,ligne);

lcd.print("Texte");

lcd.printAt(0,0,"Texte");

lcd.printfAt(0,1,"Valeur=%d",10);

lcd.center(0,"Texte centre");

lcd.clearLine(1);

lcd.progressBar(0,3,20,75);
```

---

# Fonctions clavier

```cpp
keypad.begin();

keypad.getKey();

keypad.available();

keypad.read();

keypad.setDebounce(100);
```

---

## Matériel compatible

- Arduino Uno
- Arduino Nano
- Arduino Mega
- ESP8266
- ESP32
- ESP32-S2
- ESP32-S3

---

## Licence

Licence MIT.

Vous êtes libre d'utiliser, modifier et redistribuer cette bibliothèque dans vos projets personnels ou professionnels.

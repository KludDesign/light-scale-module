# light-scale-module
Project which convert your water weight into light, using Arduino uno combine with wheatstone bridge and shift register 74hc595.

## Description of the installation
### Slaves (Scales)
This module is composed of three scals. Each scale are connected to one Arduino where 2 Wheatstone Amplifier Shields (http://www.robotshop.com/eu/fr/blindage-amplificateur-cellule-force-2ch.html) are mounted on. 
Four 50 Kg micro load cells (http://www.robotshop.com/eu/fr/micro-cellule-force-50-kg.html) are connected to this two shields in order to get a maximum of 200Kg.

### Master (Light)
Each three Arduino slaves are connected to the Arduino master via A4 and A5 plug, get and treat the data before transmitting into bits. 

### PCB
A personnal PCB are build in order to connect 72 leds. 
To light-up as much needed leds with enought Arduino output, 9 shift registers 74hc595 (https://www.sparkfun.com/products/10680) are connected in serie.

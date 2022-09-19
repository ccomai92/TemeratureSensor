# Temerature Sensor
## Requirements
1.	The system shall record Arduino temperature at a periodic rate 10 seconds.
2.	The system shall transmit recorded timestamp and temperature across a Serial bus.
3.	The system shall capture the temperature and convert it to Fahrenheit.

## Components and Supplies
1.	Thermistor NTC 10K
2.	Resistor 10k ohm
3.	Arduino UNO
4.	Jumper wires (generic)
5.	Breadboard (generic)

## Schematics
![image](https://user-images.githubusercontent.com/24425401/190999977-e8605e1a-4a89-48b9-a552-947c07b24eb7.png)\
from https://create.arduino.cc/projecthub/Marcazzan_M/how-easy-is-it-to-use-a-thermistor-e39321

## Formulas
1. Convert analog signal to voltage\
  voltage=ADC*5/1023
2. Convert voltage to resistance\
  R=10k/(1023/ADC-1)
3. Convert resistance to temperature in Kelvin (Steinhart-Hart Approximation)\
  1/T=A+Bln(R)+C(ln⁡(R) )^3\
  T=1/(A+Bln(R)+C(ln⁡(R) )^3)\
  ![image](https://user-images.githubusercontent.com/24425401/191001362-cb7aa449-a414-47d1-994c-f7fa574e9674.png)
4. Convert Kelvin to Fahrenheit\
  F=1.8*(K-273.15)+32
5. Convert Kelvin to Celsius (optional)\
  C=K-273.15

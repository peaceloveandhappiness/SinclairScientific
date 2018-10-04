
# Sinclair Scientific Hardware


## Revision History

### v1A

* Initial revision, based largely on [ArduinoEnigma's design](https://cdn.hackaday.io/files/918953931635680/V5%20Schematic.png)

### v1B

* Replaced Arduino NANO MCU with one used by Adafruit Feather M0 (SAMD21G18)
* Replaced alkaline batteries with LiPo battery
* Added LiPo battery charging circuit
* Changed LED resistor values to work with LiPo battery voltage
* Swapped 7-segment displays for ones that could be recessed easier
* Swapped existing tactile buttons for more comfortable ones
* Swapped existing ON/OFF switch for more comfortable one

### Future Changes

* Consider using LED or 7-segment display driver
  * [MAX6954](https://www.maximintegrated.com/en/app-notes/index.mvp/id/3210)
  * [MAX6957](https://www.maximintegrated.com/en/products/power/display-power-control/MAX6957.html)
  * [MAX7301](https://www.maximintegrated.com/en/products/interface/controllers-expanders/MAX7301.html)
  * Maxim has many other parts that may work better
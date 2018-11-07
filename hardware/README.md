
# Sinclair Scientific Hardware


## Revision History

### v1A

* Initial revision, based on [ArduinoEnigma's design](https://cdn.hackaday.io/files/918953931635680/V5%20Schematic.png)

### v1B

* Replaced Arduino NANO MCU with one used by Adafruit Feather M0 (SAMD21G18)
* Replaced alkaline batteries with LiPo battery
* Added LiPo battery charging circuit
* Changed LED resistor values to work with 3.3V
* Changed 7-segment displays to mount on a daughter board to allow them to be flush mounted with the faceplate
* Swapped existing tactile buttons for ones that can be used with button caps
* Swapped existing ON/OFF switch for more comfortable one
* Added charging LED that can be seen by user
* Moved LED segments [B, E] to [D0, D1] pins to allow button input lines to use [D8, D9] exclusively

### v1C

* Fixed footprint for flash memory IC
* Changed button spacing to match original sinclair dimensions
* Replaced power switch with SMT device

### Future Changes

* Consider using LED or 7-segment display driver
  * [MAX6954](https://www.maximintegrated.com/en/app-notes/index.mvp/id/3210)
  * [MAX6957](https://www.maximintegrated.com/en/products/power/display-power-control/MAX6957.html)
  * [MAX7301](https://www.maximintegrated.com/en/products/interface/controllers-expanders/MAX7301.html)
  * Maxim has many other parts that may work better
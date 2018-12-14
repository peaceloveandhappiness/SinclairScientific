
# Sinclair Scientific

This is a recreation of the original 1974 Scientific Calculator, the first affordable calculator with more than just + - ÷ ×.

Hewlett Packard had released it’s first “scientific” calculator two years earlier, and despite it costing literally as much as a fairly nice used car, it was a very successful product. Texas Instruments, on the other hand, had a widely available “four function” chip that was the heart of every cheap digital calculator, but was limited to adding, subtracting, multiplying and dividing, with limited precision.

Enter Clive Sinclair and Nigel Searle, who figured out how to use the ultra-meager 320 bytes of instruction space on that TI device to implement sine, asin, cos, acos, tan, atan, log, and antilog, in scientific notation! A feat of hacking that’s mystifying even now.

We have recreated this hallowed machine using an emulator of the TI chip, running the original instructions, at the original speed. It has lots of quirks and issues, some of which are described in this manual, some of which we had fun exploring. Far from diminishing it, these idiosyncrasies, in reality, highlight the amazing achievement that this device represents.

Enjoy!


## Inspiration

This work was inspired by and largely based upon [ArduinoEnigma's similar project](https://gitlab.com/arduinoenigma/ArduinoNanoSinclairScientificCalculator), which was inspired by [Ken Shirriff's Sinclair Scientific Calculator Simulator](http://righto.com/sinclair). The hardware design is based upon [Adafruit's Feather M0](https://github.com/adafruit/Adafruit-Feather-M0-Basic-Proto-PCB), as well as [ArduinoEnigma's hardware designs](https://hackaday.io/project/91895-sinclair-scientific-calculator-emulator). The firmware used in this project is based on [ArduinoEnigma's SinclairScientific7 code](https://gitlab.com/arduinoenigma/ArduinoNanoSinclairScientificCalculator/tree/master/SinclairScientific7) and [Adafruit's SAMD toolchain](https://github.com/adafruit/ArduinoCore-samd).

* [Ken Shirriff's Simulator](http://files.righto.com/calculator/sinclair_scientific_simulator.html)
* [ArduinoEnigma's Arduino Code](https://github.com/arduinoenigma/ArduinoNanoSinclairScientificCalculator)
* [ArduinoEnigma's Hackster Guide](https://www.hackster.io/arduinoenigma/sinclair-scientific-calculator-emulator-a11dba)
* [ArduinoEnigma's Hackaday Guide](https://hackaday.io/project/91895-sinclair-scientific-calculator-emulator)
* [ArduinoEnigma's Tindie Page](https://www.tindie.com/products/ArduinoEnigma/sinclair-scientific-calculator-emulator/)
* [Adafruit's Feather M0](https://github.com/adafruit/Adafruit-Feather-M0-Basic-Proto-PCB)


## Credits

* Thank you Joerg Woerner of [Datamath Calculator Museum](www.datamath.org/) for finding and scanning the original [Sinclair Scientific Operating Manual](www.datamath.net/Manuals_Others/Sinclair_Scientific_GB.pdf).
* Thank you [Katherine Wasserman](www.wass.net/) for finding the original [Sinclair Scientific Assembly Manual](www.wass.net/manuals/Sinclair%20Scientific%20Assembly.pdf)
* Thank you [ArduinoEnigma](www.arduinoenigma.blogspot.com) for starting the project and making the previous iterations. Awesome work!
* Thank you [Ken Shirriff](www.righto.com) for your immense talents and hard work, not only on this emulator but on lots of interesting stuff.
* Thank you [Adafruit](www.adafruit.com) for all of your incredible open source work.


## Additional Information

* [Wikipedia Page for the Sinclair Scientific](https://en.wikipedia.org/wiki/Sinclair_Scientific)
* [Historical Info about the Sinclair Scientific](http://rk.nvg.ntnu.no/sinclair/calculators/scientific.htm)
* [Technical Info about the Sinclair Scientific](http://www.vintagecalculators.com/html/scientific_-_giant_scientific.html)
* [Sinclair Scientific Operating Manual](http://www.datamath.net/Manuals_Others/Sinclair_Scientific_GB.pdf)
* [Sinclair Scientific Assembly Manual](http://www.wass.net/manuals/Sinclair%20Scientific%20Assembly.pdf)

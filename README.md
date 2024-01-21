# ATmega32 Drivers implementation

- [Description](#Description)

- [HAL](#HAL)
- [MCAL](#MCAL)
  - [GPIO](#GPIO)
- [Service](#Service)
  - [Common-Macros](#Common-Macros)
  - [Standrad-Types](#Standrad-Types)



## Description
<p>Here I implement drivers to be independent on any built in drivers and apply some concepts like</p>
<p>1.modularity</p>
<p>2.save hierarchy</p>
<p>3.easy configurability</p>

## HAL
<p>Here will find all Drivers for external hardware devices that ready to use with ATmega32</p>


## MCAL
<p>Here will find All drivers for MCU specefic and deal direct with it</p>

### GPIO
<p>Here deal with Digital input / output for MCU  </p>


## Service 
<p>Here will find some service header file used to facilitate dealing</p>

### Common-Macros
<p>Here will find function like macros that help in change bits in register easly without make stack context switch</p>

### Standrad-Types
<p>Here will find standard data types that don't depend on architecture
  bits size</p>


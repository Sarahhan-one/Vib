# Vib : Wearable Directional Assistant

![image](https://github.com/user-attachments/assets/dd931122-ff3b-4bf1-a659-7b5e057d0389)

## What is Vib? 
Vib is a ```wearable smart anklet``` that navigates the wearer using vibration. 
It houses ```three haptic motors``` facing three different directions – ```left```, ```forward```, and ```right``` – to convey an intuitive sense of direction. 
A smartphone connects to it and enables the navigator mode, as well as the customization of features.

## How it works? 
Vib is powered by a rechargeable battery that uses a type-C charger. The battery powers the microcontroller, the ATmega328P-AU, which controls all inputs and outputs used by Vib as well as the GPS and the bluetooth connection. 

The inputs to the devices are the GPS and the bluetooth signals. 
The bluetooth module allows the user to use the Vib app to cater the device to their needs, including setting the destination and the vibration intensity. 

As the device receives locational and direction information from the phone, it will send corresponding vibrational signals to vibrational motors installed at different sides of the device. 
As well, two LED lights are also used as the outputs of the microcontroller to indicate, for example, the bluetooth or battery status. 

![image](https://github.com/user-attachments/assets/f7642dc9-3b13-454c-8644-50d888046f85)

## Future enhancements
* _Real-Time Location_ : Vib will have an embedded GPS module that allows user to track the location of the device real-time.
  This means one can easily find Vib device when lost, as well as the location of the other Vib it is connected to.
* _Connect to Another Vib via Bluetooth_ : Vib will provide an option to connect to another Vib, which allows one to find the location of the other Vib wearer through vibration.
* _Change Vibration Intensity_ : Through the Vib app, one will be able to easily change the vibration intensity. From workouts to daily walks, Vib can be felt in any environment.
* _Change Light Style_ : As well, Vib also offers diverse light modes. One will be able to choose to turn off the LEDs during the day and bright and festive at night. 



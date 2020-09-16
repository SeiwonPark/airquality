# KMUSensorCloud
KMU Sensor Cloud Helper   
This is a project called KMU Crowd Sensor Cloud Air&Home&Web.   
_Korean verion here : [https://github.com/ghoxa/KMUSensorCloud](https://github.com/ghoxa/KMUSensorCloud)_   
<br/>
**ABSTRACT**   
Connect air quality sensors(dust sensor, temperature, humidity and pressure sensor, etc...) to Arduino and collect data based on ThingSpeak api.
We can visualize these collected data and make lots of applications, and even predict numbers by machine learning if those are collected for a few years(So that we can have enough data). Also, we can add other sensors to extend various applications by web programming based on ThingSpeak or AWS(Amazon Web Service).

## Table of Contents   
+ [1. Author](#1-author)   
+ [2. Objective](#2-objective)   
+ [3. Sensor Modules Introduction](#3-sensor-modules-introduction)   
  + [3.1 WiFi Module(ESP8266)](#31-wifi-moduleesp8266)   
  + [3.2 Dust Sensor(PMS7003m)](#32-dust-sensorpms7003m)   
  + [3.3 Temperature, Humidity and Pressure Sensor(BME280)](#33-temperature-humidity-and-pressure-sensorbme280)   
+ [4. Arduino Connection](#4-arduino-connection)
  + [4.1 Arduino Sensor Connection](#41-arduino-sensor-connection)   
  + [4.2 Installing Arduino](#42-installing-arduino)
  + [4.3 Adding Libraries to Arduino](#43-adding-libraries-to-arduino)
  + [4.4 WiFi Communication Test](#44-wifi-communication-test)
    + [4.4.1 Port Check](#441-port-check)
    + [4.4.2 Upload and Enter AT Command](#442-upload-and-enter-at-command)
+ [5. Communication with ThingSpeak](#5-communication-with-thingspeak)    
  + [5.1 Sign in to ThingSpeak](#51-sign-in-to-thingspeak)   
  + [5.2 Create Channel](#52-create-channel)   
  + [5.3 Run `main.ino`](#53-run-mainino)   
    + [5.3.1 Code Refactoring](#531-code-refactoring)   
  + [5.4 Visualize Data](#54-visualize-data)   
    + [5.4.1 Check on Arduino Monitor](#541-check-on-arduino-monitor)   
    + [5.4.2 Check on ThingSpeak](#542-check-on-thingspeak)   
    
<br/>   
    

## 1. Author   
* Professor Suntae Hwang(sthwang@kookmin.ac.kr)   
* Professor Daeyoung Heo(dyheo@kookmin.ac.kr)   
* Director Gyuyeon Choi(gychoi@cs.kookmin.ac.kr)   
* Hojun Kim(hotem1234@naver.com)   
* Seiwon Park(psw7347@gmail.com)   

<br/>   

## 2. Objective   
* Collecting data from various places by sensing air quality to visualize, analyze and predict future data   
* **First**, practice by building platform using ThingSpeak   
* **Second**, linking IoT Device with ThingSpeak and practice   
* **Third**, configuration Web Application to approach from mobile   

<br/>   

## 3. Sensor Modules Introduction
### 3.1 WiFi Module(ESP8266)   
<img src="https://user-images.githubusercontent.com/63793178/92008373-0db94b00-ed82-11ea-9255-9d55aec0d4fc.jpeg" width="40%">     

**Technical Index**   
Parameter | Index
:------------ | :-------------
Name | ESP8266 + ESP-01
Command | UART AT Command
Antenna | On-Board Ceramic Antenna
Communication Method | 802.11 b/g/n   
Communication Speed<br/>(Baud Rate) | - 115200(Default) <br/> - Software-Serial: 57600bps ~ 2000000bps <br/> - Hardware-Serial: 9600bps ~ 2000000bps
Flash Memory | 16M Byte
Processor Speed | 80 ~ 160 Mhz
Supply Voltage | 3.3V(≥ 300mA)
Size | 14.5 x 24.8 mm²   

_Further reference_:   

<br/>   

### 3.2 Dust Sensor(PMS7003m)   
<img width="300" src="https://user-images.githubusercontent.com/63793178/92009149-0a728f00-ed83-11ea-8238-f80b9e00cb11.jpeg">   

**Technical Index**   
Parameter | Index
:------------ | :------------  
Name | PMS7003m
Operating Range | 0.3 ~ 1.0, 1.0 ~ 2.5, 2.5 ~ 10 µm
Valid Range(PM 2.5) | 0 ~ 500 µm
Maximum Range(PM 2.5) | ≥ 1000 µm
Supply Voltage | 5.0V
Operating Temperature | -10 ~ +60 °C
Operating Humidity | 0 ~ 99 %
Size |  48 x 37 x 12 mm³

_Further reference_:   

<br/>   

### 3.3 Temperature, Humidity and Pressure Sensor(BME280)   
<img width="300" src="https://user-images.githubusercontent.com/63793178/92009502-95ec2000-ed83-11ea-8f62-ba1e85fb941c.jpeg">      

**Technical Index**   
Parameter | Index
:------------ | :------------  
Name | BME280   
Operating Range | Pressure: 300 ~ 1100 hPa <br/> Temperature: -40 ~ +85 °C
Humidity Sensor | Accuracy Tolerance: ±3% <br/> Response Time: 1 sec
Pressure Sensor | Sensitivity Error: ±0.25%
Voltage | 3.3 ~ 5.0 V  
Supply Current | 2mA
Size | 2.5 x 2.5 x 0.93 mm³

_Further reference_: [BOSCH](https://www.bosch-sensortec.com/products/environmental-sensors/humidity-sensors-bme280/), [BME280 libraries](https://github.com/finitespace/BME280), [Specification](https://wiki.dfrobot.com/Gravity__I2C_BME280_Environmental_Sensor__Temperature,_Humidity,_Barometer__SKU__SEN0236)   

<br/>   

## 4. Arduino Connection   
### 4.1 Arduino Sensor Connection   

<img width="700" src ="https://user-images.githubusercontent.com/63793178/92118804-ede16000-ee31-11ea-8e05-4aa9e468d4ae.png">   

Connect sensors and modules with Arduino board as above.   

You can check details at following site: [Arduino Sensor Connection](https://air.cs.kookmin.ac.kr/디바이스/law-iot-ta2019)   
Also, it would be better if you have following knowledge about Arduino Board   

<img width = "500" src = "https://user-images.githubusercontent.com/63793178/92121794-a65cd300-ee35-11ea-9603-1be69fd95832.jpeg">   

As you can see, each block is connected: VCC with VCC, GND with GND. So it doesn't matter which VCC or GND you choose within each block.   
***But*** be cautious which ***PIN*** to choose as it should be consistent with code.   

Parameter | Index
:------------ | :-------------
VCC | 5V 
GND | 0V    


If sensors and modules are correctly connected, connect Arudino with computer using cable as follows:    

<img width="300" src="https://user-images.githubusercontent.com/63793178/92117915-c2aa4100-ee30-11ea-9b4b-35bbdf728e4d.jpeg">      

<br/>   


### 4.2 Installing Arduino   
Visit [https://www.arduino.cc](https://www.arduino.cc/en/Main/Software) and follow the path ***SOFTWARE > DOWNLOADS***. And then choose your OS.   

<img width="500" alt="스크린샷 2020-09-03 오후 9 40 44" src="https://user-images.githubusercontent.com/63793178/92116122-60e8d780-ee2e-11ea-8919-73051bf37a07.png" width="10%">   

<img width="500" src ="https://user-images.githubusercontent.com/63793178/92210025-f769d700-eec8-11ea-9ffc-ef89819229ae.jpeg">    

Click ***JUST DOWNLOAD***.   


<br/>   

### 4.3 Adding Libraries to Arduino    

If Arduino IDE is installed, execute Arudino Application.   

<img width="500" alt="스크린샷 2020-09-03 오후 9 51 45" src="https://user-images.githubusercontent.com/63793178/92117352-0e101f80-ee30-11ea-8143-a442a4bcda48.png" width="10%">

Then you may see following screen. Follow the path ***Sketch > Include Library > Add .ZIP Library...*** and add all zip files in **KMUSensorCloud/library/**. Zip files are as follows:   

```   
Adafruit_BME280_Library_KMU-master.zip   

Adafruit_Sensor-master.zip   

PMS-master.zip   

SparkFun_ESP8266_AT_Arduino_Library_KMU-master.zip   
```     

_NOTE_   

<img width="600" src = "https://user-images.githubusercontent.com/63793178/92210317-74954c00-eec9-11ea-9aff-29a53fd51bbc.jpeg">   

You can download `.zip` files as above.   

<br/>   

### 4.4 WiFi Communication Test        
Execute `wificonnect.ino` and check WiFi communication.   
<br/>   

#### 4.4.1 Port Check    

<img width="500" alt="스크린샷 2020-09-03 오전 11 54 24" src="https://user-images.githubusercontent.com/63793178/92066252-6e757180-eddc-11ea-86e1-2b39e8d57fc1.png" width="10%">   

Follow the path ***Tool > Port***, then make sure that serial port setting is correct.   

<br/>   

#### 4.4.2 Upload and Enter AT command      

<img width="500" alt="스크린샷 2020-09-03 오전 11 45 00" src="https://user-images.githubusercontent.com/63793178/92065879-78e33b80-eddb-11ea-82b0-c13cb6a40752.png" width="10%">

Click ***UPLOAD***, then follow the path ***Tool > Serial Monitor*** and set ***Both NL & CR***, ***9600 Baud Rate*** as above.   
When all things are confirmed, Enter `AT` and check whether the output is `OK`. If `OK` is printed, move on to next step.      

<br/>   

We know that default communication speed of ***3.1 WiFi Module(ESP8266)*** on ESP-01 board is 115200bps. By the way, as 9600bps is commonly used due to it's enough speed, let's change speed permanently to 9600bps.   

<img width="500" alt="스크린샷 2020-09-03 오후 9 21 53" src="https://user-images.githubusercontent.com/63793178/92114288-8c1df780-ee2b-11ea-8e93-93526da61c7b.png" width="30%">   

Enter `AT+ UART_DEF=9600,8,1,0,0` on your monitor as above.   
_NOTE: `AT + UART_DEF = (baudrate),(databits),(stopbits),(parity),(flow control)`_   

<br/>   

## 5. Communication with ThingSpeak   
### 5.1 Sign in to ThingSpeak   

<img width="700" src = "https://user-images.githubusercontent.com/63793178/92125626-31d86300-ee3a-11ea-96c8-a763b5d6a855.jpeg">   

Visit [https://thingspeak.com](https://thingspeak.com).   
Then click ***`GET STARTED FOR FREE`***. 
   
<br/>   

<img width="700" src = "https://user-images.githubusercontent.com/63793178/92126047-add2ab00-ee3a-11ea-9246-4f975afaea89.jpeg">   

If you are not signed up yet click ***`Create one!`***, or sign in with your E-mail.   

<br/>    

### 5.2 Create Channel      

<img width="700" src = "https://user-images.githubusercontent.com/63793178/92126165-ccd13d00-ee3a-11ea-8daf-46044ea809b6.jpeg">   

Sign in and then click  ***`Channels > New Channel`***.   

<img width="700" src = "https://user-images.githubusercontent.com/63793178/92126223-dd81b300-ee3a-11ea-98d6-1f15644b6aec.jpeg">   

Enter blanks as above.   
* ***`Name`*** :  your student ID
* ***`Description`*** :   date that you made this channel.

<br/>

<img width="700" src = "https://user-images.githubusercontent.com/63793178/92126316-fe4a0880-ee3a-11ea-90f3-728e3cc390e6.jpeg">   

* ***`Link to External Site`*** :    `https://air.cs.kookmin.ac.kr/`
* Click checkbox ***`Show Channel Location`*** and enter the latitude and longitude.    
_NOTE_: You can check your latitude and longitude on Google Map.   
Refer to [Google Map](https://mainia.tistory.com/2404).   

<br/>   

### 5.3 Run ***`main.ino`***    
_NOTE: Make sure that Arduino is connected correctly with your computer and that port and others are set in consistent with **4. Arduino Connection**_.   

#### 5.3.1 Code Refactoring      

<img width="500" src="https://user-images.githubusercontent.com/63793178/92211971-3cdbd380-eecc-11ea-9640-2d09cf21c24e.jpeg">   

* `#define SSID   "Enter"`       :   Enter WiFi's ID that your WiFi Module(ESP8266) is connected.   
* `#define PASSWORD   "Enter"`   :   Enter WiFi's password that your WiFi Module(ESP8266) is connected.   
* `#define SENSOR_NAME  "Enter"` :   Enter your Student ID.   
* `#define API_KEY  "Enter"`     :   Enter as follows:   

  Visit [https://thingspeak.com](https://thingspeak.com), then click channel that you created at **5.2 Create Channel**.      

  <img width="700" alt="스크린샷 2020-09-04 오후 4 44 04" src="https://user-images.githubusercontent.com/63793178/92213206-1c147d80-eece-11ea-94fc-1514c1b33d57.png">   
  
  Then, click ***API Keys*** as above.   
  
  <img width="500" src="https://user-images.githubusercontent.com/63793178/92215500-d5278780-eecf-11ea-9e72-b75a4aad46d3.jpeg">   
  
  Copy ***Key*** under ***Write API Key*** then paste it to `#define API_KEY  "Enter"`.   
  
  And finally click ***UPLOAD*** in file ***`main.ino`***.  

<br/>    

### 5.4 Visualize Data      

#### 5.4.1 Check on Arduino Monitor     

<img width="700" alt="스크린샷 2020-09-04 오후 5 01 30" src="https://user-images.githubusercontent.com/63793178/92215819-51ba6600-eed0-11ea-877e-3ff5325c4272.png">   

Follow the path ***Tool > Serial Monitor***, and you can check the figures like _Temperature_, _Humidity_, _Pressure_, _PM 1.0_, _PM 2.5_, _PM 10.0_ as above.   

<br/>   

#### 5.4.2 Check on ThingSpeak   

<img width="700" src = "https://user-images.githubusercontent.com/63793178/92126483-33eef180-ee3b-11ea-9adb-4feb09774d36.jpeg">   

Also at ***Channel*** on ThingSpeak, you can check the values that Arduino sent through serial and see that the values are represented in a graph.   

<br/>   

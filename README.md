# KMUSensorCloud
KMU Sensor Cloud Helper   
This is a project called KMU Crowd Sensor Cloud Air&Home&Web. Copyright © [KOOKMINUNIVERSITY SENSOR CLOUD LAB](https://air.cs.kookmin.ac.kr/)      

**ABSTRACT**   
Connect air quality sensors(dust sensor, temperature, humidity and pressure sensor, etc...) to Arduino and collect data based on ThingSpeak api.
We can visualize these collected data and make lots of applications, and even predict numbers by machine learning if those are collected a few years.
Also, we can add other sensors so that extend various applications by web programming based on ThingSpeak or AWS(Amazon Web Service).

## Table of Contents   
+ [1. Author](#1-author)   
+ [2. Objective](#2-objective)   
+ [3. Sensor Modules Introduction](#3-sensor-modules-introduction)   
  + [3.1 WiFi Module(ESP8266)](#31-wifi-moduleesp8266)   
  + [3.2 Dust Sensor(PMS7003m)](#32-dust-sensorpms7003m)   
  + [3.3 Temperature, Humidity and Pressure Sensor(BME280)](#33-temperature-humidity-and-pressure-sensorbme280)   
+ [4. Arduino Connection](#4-arduino-connection)
  + [4.1 Arduino Sensor Connection](#41-arduino-sensor-connection)   
  + [4.2 Install Arduino](#42-install-arduino)
  + [4.3 Add Libraries to Arduino](#43-add-libraries-to-arduino)
  + [4.4 WiFi Communication Test](#44-wifi-communication-test)
    + [4.4.1 Port Check](#441-port-check)
    + [4.4.2 Upload and implement AT Command](#442-upload-and-implement-at-command)
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
* Collecting data from various places by sensing air quality to visualize, analyze and predict   
* First, practice by building platform using ThingSpeak   
* Second, linking IoT Device with ThingSpeak and practice   
* Third, configuration Web Application to approach from mobile   

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

You can check details at following [Arduino Sensor Connection](https://air.cs.kookmin.ac.kr/디바이스/law-iot-ta2019)   
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


### 4.2 Install Arduino   
Visit [https://www.arduino.cc](https://www.arduino.cc/en/Main/Software) and follow the path ***SOFTWARE > DOWNLOADS***. And then choose your OS.   

<img width="500" alt="스크린샷 2020-09-03 오후 9 40 44" src="https://user-images.githubusercontent.com/63793178/92116122-60e8d780-ee2e-11ea-8919-73051bf37a07.png" width="10%">   

<img width="500" src ="https://user-images.githubusercontent.com/63793178/92210025-f769d700-eec8-11ea-9ffc-ef89819229ae.jpeg">    

Click ***JUST DOWNLOAD***.   


<br/>   

### 4.3 Add Libraries to Arduino    

If Arduino IDE is installed, execute Arudino Application.   

<img width="500" alt="스크린샷 2020-09-03 오후 9 51 45" src="https://user-images.githubusercontent.com/63793178/92117352-0e101f80-ee30-11ea-8143-a442a4bcda48.png" width="10%">

Then you may see following screen. Follow the path ***Sketch > Include Library > Add .ZIP Library...*** and add all zip files in **KMUSensorCloud/library/**. Zip files are as follows:   

```   
Adafruit_BME280_Library_KMU-master.zip   

Adafruit_Sensor-master.zip   

PMS-master.zip   

SparkFun_ESP8266_AT_Arduino_Library_KMU-master.zip   
```     

_Reference_   

<img width="600" src = "https://user-images.githubusercontent.com/63793178/92210317-74954c00-eec9-11ea-9aff-29a53fd51bbc.jpeg">   

You can download `.zip` files as above.   

<br/>   

### 4.4 WiFi Communication Test        
Implement `wificonnect.ino` and check WiFi communication.   
<br/>   

#### 4.4.1 Port Check    

<img width="500" alt="스크린샷 2020-09-03 오전 11 54 24" src="https://user-images.githubusercontent.com/63793178/92066252-6e757180-eddc-11ea-86e1-2b39e8d57fc1.png" width="10%">   

Follow the path ***Tool > Port > Serial Port***, then make sure that serial port setting is correct.   

<br/>   



#############################################################










#### 4.4.2 업로드 및 AT command 실행   

<img width="500" alt="스크린샷 2020-09-03 오전 11 45 00" src="https://user-images.githubusercontent.com/63793178/92065879-78e33b80-eddb-11ea-82b0-c13cb6a40752.png" width="10%">

***업로드*** 를 클릭한 후, ***툴 > 시리얼 모니터*** 에서, 사진과 같이 ***Both NL & CR*** 로 설정해준 후, ***9600 보드레이트*** 인지 확인한다.   
확인이 됐다면, `AT` 를 입력한 후, `OK`가 출력되는지 확인한다. `OK`가 출력이 되면 정상이다.   

<br/>   

***3.1 와이파이 모듈(ESP8266)*** 에서 ESP-01 보드의 Default 통신 속도가 115200bps 임을 알 수 있다. 충분히 빠른속도로 가장 흔하게 사용되는 통신속도는 9600bps 이므로 속도를 영구적으로 변경해보자.   

<img width="500" alt="스크린샷 2020-09-03 오후 9 21 53" src="https://user-images.githubusercontent.com/63793178/92114288-8c1df780-ee2b-11ea-8e93-93526da61c7b.png" width="30%">   

모니터에 `AT+ UART_DEF=9600,8,1,0,0`을 입력한다.    
_참고로, AT + UART_DEF = (baudrate),(databits),(stopbits),(parity),(flow control) 를 의미한다._   

<br/>   

## 5. ThingSpeak와 통신   
### 5.1 ThingSpeak에 로그인   

<img width="700" src = "https://user-images.githubusercontent.com/63793178/92125626-31d86300-ee3a-11ea-96c8-a763b5d6a855.jpeg">   

[https://thingspeak.com](https://thingspeak.com) 에 접속한다.   
접속 후 ***`GET STARTED FOR FREE`*** 를 클릭한다. 
   
<br/>   

<img width="700" src = "https://user-images.githubusercontent.com/63793178/92126047-add2ab00-ee3a-11ea-9246-4f975afaea89.jpeg">   

회원가입이 되어 있지 않다면 ***`Created one!`*** 을 누르고, 가입이 되어 있다면 해당 이메일로 로그인 한다.

<br/>    

### 5.2 ThingSpeak 채널 생성   

<img width="700" src = "https://user-images.githubusercontent.com/63793178/92126165-ccd13d00-ee3a-11ea-8daf-46044ea809b6.jpeg">   

로그인 후  ***`Channels > New Channel`*** 을 클릭한다.   

<img width="700" src = "https://user-images.githubusercontent.com/63793178/92126223-dd81b300-ee3a-11ea-98d6-1f15644b6aec.jpeg">   

보기와 같이 작성하되 ***`Name`*** 에 본인의 학번, ***`Description`*** 에 채널을 생성한 날짜를 쓴다.

<br/>

<img width="700" src = "https://user-images.githubusercontent.com/63793178/92126316-fe4a0880-ee3a-11ea-90f3-728e3cc390e6.jpeg">   

***`Link to External Site`*** 에는 `https://air.cs.kookmin.ac.kr/` 를 입력해주고, ***`Show Channel Location`*** 을 체크하고 위도와 경도를 작성한다. 
이 때, 위도 및 경도는 구글 지도에서 알 수 있다.
[구글지도 참조](https://mainia.tistory.com/2404) 를 참조하도록 한다.   

<br/>   

### 5.3 아두이노 ***`main.ino`*** 실행   
_컴퓨터와 아두이노가 연결 돼 있고, 포트 및 기타 설정이 **4. 아두이노 연결** 과 같이 되어 있는지 확인한다._     

#### 5.3.1 코드 수정   

<img width="500" src="https://user-images.githubusercontent.com/63793178/92211971-3cdbd380-eecc-11ea-9640-2d09cf21c24e.jpeg">   

* `#define SSID   "입력할 곳"` 에 WiFi 모듈과 연결 돼 있는 WiFi의 이름을 입력한다.   
* `#define PASSWORD   "입력할 곳"` 에 해당 WiFi 의 비밀번호를 입력한다.   
* `#define SENSOR_NAME  "입력할 곳"` 에 본인의 학번을 입력한다.   
* `#define API_KEY  "입력할 곳"` 은 다음과 같이 진행한다.   

  [https://thingspeak.com](https://thingspeak.com) 에 접속 후, 위 **5.2 ThingSpeak 채널 생성** 에서 생성한 채널을 클릭한다.   

  <img width="700" alt="스크린샷 2020-09-04 오후 4 44 04" src="https://user-images.githubusercontent.com/63793178/92213206-1c147d80-eece-11ea-94fc-1514c1b33d57.png">   
  
  그런 다음, 위 사진과 같이 ***API Keys*** 를 클릭한다.   
  
  <img width="500" src="https://user-images.githubusercontent.com/63793178/92215500-d5278780-eecf-11ea-9e72-b75a4aad46d3.jpeg">   
  
  ***Write API Key*** 에 해당하는 ***Key*** 를 복사하여 `#define API_KEY  "입력할 곳"` 에 붙여넣는다.   
  
  그리고 ***`main.ino`*** 파일을 업로드 한다.


### 5.4 ThingSpeak 데이터 시각화 확인   

#### 5.4.1 아두이노 시리얼 모니터에서 확인   

<img width="700" alt="스크린샷 2020-09-04 오후 5 01 30" src="https://user-images.githubusercontent.com/63793178/92215819-51ba6600-eed0-11ea-877e-3ff5325c4272.png">   

아두이노 상단바에서, ***툴 > 시리얼 모니터*** 에서 위와 같이 온도, 습도, 기압, PM 1.0, PM 2.5, PM 10.0 의 수치를 알 수 있다.   

<br/>   

#### 5.4.2 ThingSpeak 채널에서 확인

<img width="700" src = "https://user-images.githubusercontent.com/63793178/92126483-33eef180-ee3b-11ea-9adb-4feb09774d36.jpeg">   

또한, ThingSpeak에서 생성한 ***Channel*** 에서 아두이노에서 전송된 결과값들이 그래프로 표시됨을 확인할 수 있다.   

<br/>   

# KMUSensorCloud
KMU Sensor Cloud Helper   
This is a project called KMU Crowd Sensor Cloud Air&Home&Web. Copyright © [KOOKMINUNIVERSITY SENSOR CLOUD LAB](https://air.cs.kookmin.ac.kr/)      

**개요**   
공기질 센서(미세먼지, 온도, 습도 등)를 아두이노에 결합하여 ThingSpeak를 기반으로 수집하고 관리한다. 
이렇게 모인 데이터를 시각화하고 분석하여 여러가지 응용 앱을 만드는데 활용할 수 있으며, 데이터가 수년간 축적되면 기계학습을 통한 예측 기능을 추가하는 것이 가능하다. 
또한 센서 이외에 다른 장치를 부착하여 ThingSpeak, AWS 기반의 웹서버 프로그래밍을 통해 다양한 응용 및 확장이 가능하다. 
함께 모여 아두이노와 공기질 센서를 조립하고 테스트한 후, 각자 집에 설치하여 ThingSpeak를 통해 데이터를 수집하고 지도에 나타내는 것이 1차 목표이다.   

## 목차   
+ [1. 저자](#1-저자)   
+ [2. 목표](#2-목표)   
+ [3. 센서모듈 종류 및 소개](#3-센서모듈-종류-및-소개)   
  + [3.1 와이파이 모듈(ESP8266)](#31-와이파이-모듈esp8266)   
  + [3.2 미세먼지 센서(PMS7003m)](#32-미세먼지-센서pms7003m)   
  + [3.3 온도/습도/기압 센서(BME280)](#33-온도습도기압-센서bme280)   
+ [4. 아두이노 센서 연결](#4-아두이노-센서-연결)
  + [4.1 WiFi 통신 테스트](#41-wifi-통신-테스트)   
+ [5. ThingSpeak와 통신](#5-thingspeak와-통신) 

## 1. 저자   
* 황선태 교수님(sthwang@kookmin.ac.kr)   
* 허대영 교수님(dyheo@kookmin.ac.kr)   
* 최규연 이사님   
* 김호준   
* 박세원(psw7347@gmail.com)   

## 2. 목표   
* 여러 공간의 대기질 센싱 데이터 수집,가시화, 분석, 예측   
* 첫째, ThingSpeak를 사용한 IoT 센서 플랫폼 구축 방법과 실습   
* 둘째, IoT Device와 ThingSpeak 연동과 실습    
* 셋째, 모바일 환경에서 접근하기 위한 웹 어플리케이션 구성   

## 3. 센서모듈 종류 및 소개   
### 3.1 와이파이 모듈(ESP8266)   
<img src="https://user-images.githubusercontent.com/63793178/92008373-0db94b00-ed82-11ea-9255-9d55aec0d4fc.jpeg" width="40%">     

**Technical Index**   
Parameter | Index
:------------ | :-------------
모듈명 | ESP8266 + ESP-01
동작명령 | UART AT Command
안테나 | On-Board Ceramic Antenna
통신방식 | 802.11 b/g/n 지원
통신속도<br/>(Baud Rate) | - 115200(Default) <br/> - 소프트웨어-시리얼: 57600bps ~ 2000000bps <br/> - 하드웨어-시리얼: 9600bps ~ 2000000bps
플래시 메모리 | 16M Byte
프로세서 스피드 | 80 ~ 160 Mhz
동작 전압 | 3.3V(300mA 이상)
크기 | 14.5 x 24.8 mm²   

_추가참조_:   

### 3.2 미세먼지 센서(PMS7003m)   
<img src="https://user-images.githubusercontent.com/63793178/92009149-0a728f00-ed83-11ea-8238-f80b9e00cb11.jpeg" width="30%">   

**Technical Index**   
Parameter | Index
:------------ | :------------  
모듈명 | PMS7003m
측정 범위 | 0.3 ~ 1.0, 1.0 ~ 2.5, 2.5 ~ 10 µm
유효 범위(PM 2.5) | 0 ~ 500 µm
최대 범위(PM 2.5) | ≥ 1000 µm
전압 | 5.0V
동작 온도 | -10 ~ +60 °C
동작 습도 | 0 ~ 99 %
크기 |  48 x 37 x 12 mm³

_추가참조_:   

### 3.3 온도/습도/기압 센서(BME280)   
<img src="https://user-images.githubusercontent.com/63793178/92009502-95ec2000-ed83-11ea-8f62-ba1e85fb941c.jpeg" width="25%">      

**Technical Index**   
Parameter | Index
:------------ | :------------  
모듈명 | BME280   
유효 범위 | 압력: 300 ~ 1100 hPa <br/> 온도: -40 ~ +85 °C
습도 센서 | 허용안정도: ±3% <br/> 샘플링 시간: 1 sec
기압 센서 | 감도오차: ±0.25%
전압 | 3.3 ~ 5.0 V  
전류 | 2mA
크기 | 2.5 x 2.5 x 0.93 mm³

_추가참조_: [BOSCH](https://www.bosch-sensortec.com/products/environmental-sensors/humidity-sensors-bme280/), [BME280 libraries](https://github.com/finitespace/BME280), [Specification](https://wiki.dfrobot.com/Gravity__I2C_BME280_Environmental_Sensor__Temperature,_Humidity,_Barometer__SKU__SEN0236)   

## 4. 아두이노 센서 연결   
### 4.1 WiFi 통신 테스트   


## 5. ThingSpeak와 통신


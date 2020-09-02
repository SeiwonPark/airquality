# KMUSensorCloud
KMU Sensor Cloud Helper   
This is a project called KMU Crowd Sensor Cloud Air&Home&Web. Copyright © [KOOKMINUNIVERSITY SENSOR CLOUD LAB](https://air.cs.kookmin.ac.kr/)      

**ABSTRACT**   
Connect air quality sensors(dust sensor, temperature, humidity and pressure sensor, etc...) to Arduino and collect data based on ThingSpeak api.
We can visualize these collected data and make lots of applications, and even predict numbers by machine learning if those are collected a few years.
Also, we can add other sensors so that extend various applications by web programming based on ThingSpeak or AWS(Amazon Web Service).

## Table of Contents   
+ [1. Author](#1-author)   
+ [2. Objective](#2-Objective)   
+ [3. Sensor Modules Introduction](#3-sensor-modules-introduction)   
  + [3.1 WiFi Module(ESP8266)](#31-wifi-moduleesp8266)   
  + [3.2 Dust Sensor(PMS7003m)](#32-dust-sensorpms7003m)   
  + [3.3 Temperature, Humidity and Pressure Sensor(BME280)](#33-temperature-humidity-and-pressure-sensorbme280)   
+ [4. Arduino Connection](#4-arduino-connection)
  + [4.1 WiFi Communication Test](#41-wifi-communication-test)   
+ [5. Communication with ThingSpeak](#5-communication-with-thingspeak) 

## 1. Author   
* Professor Suntae Hwang(sthwang@kookmin.ac.kr)   
* Professor Daeyoung Heo(dyheo@kookmin.ac.kr)   
* Director Gyuyeon Choi()   
* Hojun Kim()   
* Seiwon Park(psw7347@gmail.com)   

## 2. Objective   
* 여러 공간의 대기질 센싱 데이터 수집,가시화, 분석, 예측   
* 첫째, ThingSpeak를 사용한 IoT 센서 플랫폼 구축 방법과 실습   
* 둘째, IoT Device와 ThingSpeak 연동과 실습    
* 셋째, 모바일 환경에서 접근하기 위한 웹 어플리케이션 구성   

## 3. Sensor Modules Introduction
### 3.1 WiFi Module(ESP8266)   
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

_Further reference_:   

### 3.2 Dust Sensor(PMS7003m)   
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

_Further reference_:   

### 3.3 Temperature, Humidity and Pressure Sensor(BME280)   
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

_Further reference_: [BOSCH](https://www.bosch-sensortec.com/products/environmental-sensors/humidity-sensors-bme280/), [BME280 libraries](https://github.com/finitespace/BME280), [Specification](https://wiki.dfrobot.com/Gravity__I2C_BME280_Environmental_Sensor__Temperature,_Humidity,_Barometer__SKU__SEN0236)   

## 4. Arduino Connection   
### 4.1 WiFi Communication Test   


## 5. Communication Test with ThingSpeak


gdm3d-uav
=========

Data sampling system of GDM platform, it's implemented on UAVs. This data sampling system consists of a microcontroller board, sensor boards and wifi board. It receives flight data including GPS position data using MAVLINK protocal via serial port, sampling sensors and insert the data into MAVLINK protocal and then sends them to ground station through wifi link. The microontroller is STM32F103C8T6.

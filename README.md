# PMS7003reader
![screenshot](/picture.png)

This is a simple program to gather data from PMS7003 sensor.
Features
* Plot showing actual data
* save to .csv file, and plot to picture
* display most of received data
* slep mode enables gathering data in periods of: 15mins, 30mins, 1 hour
* selectable COM port
* ability to add data when saving to file
* currently works only on x64 system

How to use
	You need except sensor You need UART to USB converter with connected cables.
After installing this app You need to select serial port, and press start. Wait 5secs for first data. When You run app
plot x axis is automatically set to 24 hours range. you can zoom and move whole chart, or just 
particular axis.

Known limitations:
*with data stamp it always adds new data every time Start button is pressed
*if path to save file does not exist it won't inform about problem, until first measurement
*needs at least 2 measurements to display data on plot

Author: Rafa³ Mazurkiewicz
contact: raf.mazurkiewicz@op.pl
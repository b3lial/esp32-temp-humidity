# ESP32 Cloud Sensor
Esp32 firmware for DHT22 based temperature/humidity sensor.
Connects to to your local wifi access point and 

* publishes sensor data via rest uri __http://cloudsensor/data__. 
* sends sensor data to an influx db

## Hardware
You will need:

* ESP32 uC
* DHT22 temp/humidity sensor

The vanilla dht22 needs an additional pull-up resistor. You can also buy
prebuild boards which contain the resistor to spare some soldering time.
The code in this project assumes the data pin of the dht22 is connected
to GPIO 4 of the esp32. This behaviour can be changed in `DHT_task()`
with a call to `setDHTgpio()`. Below is an image of my setup:

![ESP32 and DHT22](esp.jpg "ESP32 and DHT22")

## Build
It is an esp-idf project so you have to use __idf.py__ to
build, flash and monitor. Details can be found 
[here](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/linux-macos-setup.html#get-started-linux-macos-first-steps)
if you are new to esp32 programming. 

Since the esp32 connects to your local wifi and is available via mDNS
discovery, run `idf.py menuconfig` and configure a few default
values in section __Cloud Sensor WiFi Configuration__:

* CLOUDSENSOR_WIFI_SSID: Your access point.
* CLOUDSENSOR_WIFI_PASSWORD: Its password.
* CLOUDSENSOR_NAME: mDNS host name and influxdb measurement name.
* CLOUDSENSOR_INFLUX_HOSTNAME: Influxdb host name.
* CLOUDSENSOR_INFLUX_TOKEN: Influxdb access token.
* CLOUDSENSOR_INFLUX_BUCKET: Influxdb bucket name.
* CLOUDSENSOR_INFLUX_ORGANISATION: Influxdb organisation name.

## Sensor Access
I am using the dht22 library written by Ricardo Timmermann. 
After the esp32 has been booted successfully, it starts the
__DHT_task__ which reads current sensor values every three
seconds. They can be queried via `getHumidity()` and
`getTemperature()`. I have added a mutex to the library because
this project uses concurrency and I do not want to read sensor values
while their a written at the same time. 

## REST
The esp32 starts web server on port 80 and offers sensor
data at __/data__.

## mDNS
The sensor can be discovered by __cloudsensor__ and publishes the txt record:

* board: esp32
* version: 1.0.0

## WiFi
My implementation connects to WPA2 access points and needs a
DHCP server to get an IP address.

## Influxdb
Sends sensor data on a 30 seconds basis to influxdb via http request.
Request has the following structure:

```bash
#read from dht22
temp="26.4" 
hum="45.2"

curl --request POST \
"http://localhost:8086/api/v2/write?org=phobosys&bucket=cloudsensor&precision=ns" \
  --header "Authorization: Token XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" \
  --header "Content-Type: text/plain; charset=utf-8" \
  --header "Accept: application/json" \
  --data-binary "
    office temperature=$temp,humidity=$hum
```
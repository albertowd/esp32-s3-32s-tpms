# esp32-s3-32s-tpms

A BLE library to parse TPMS data from advertised sensors.

## BLE Advertised Data

Sensor Name: TPMS1_108A78 (`_numbers` are used in the sensor address)
```
000180eaca124d01971300007f0a00006301
0001                                    Manufacturer
    80eaca108a78                        Address
                e36d0000                Pressure (in kPa)
                        e60a0000        Temperature (in ºC)
                                63      Battery (%)
                                  01    Alarm Flag (00: OK, 01: Pressure Leak)
```

## References

Big thanks for this repo here, I started from reading it!
(https://github.com/ra6070/BLE-TPMS)[https://github.com/ra6070/BLE-TPMS]

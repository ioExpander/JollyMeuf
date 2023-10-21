# Description
ESPHome controls for my Jolly Mec Bottero 2 pellet stove using Home Assistant.

## Why ?
Jolly Mec has decided to kill their current wifi control service (efesto) instead of making necessary changes to have it policy/GDPR compliant. They are now requesting all their customers to purchase a new 300€ wifi control module to retain an option they have already paid for. Many customers believe this is not an acceptable solution and are trying to free themselves from Jolly Mec.

## What
This solution uses an ESP8266 board (5$) and maybe 5$ of additionnal components and a few wires.
All it does for now is launch a scan of RAM en EEPROM adresses.

# ⚠️ WARNING ⚠️
**Do NOT install this at home.** This is not approved by Jolly Mec, this will void your warranty, this will likely damage your stove, this might burn your house down and/or severly injur pets or people.

# Instructions
- copy `poelle/*` into the esphome directory
- create a new esphome device and use the `example.yaml` as a guideline to update the base file created by ESPHome
- once connected and booted 2 buttons will appear in the Home Assistant's device page
- open a wireless log console on ESPHome and keep the tab open
- in a separate tab click on the `scan RAM` or `scan EEPROM` button
- the logs will start displaying the scan
- 🕵🏼

# Thank you to
- https://github.com/philibertc/micronova_controller
- https://github.com/Jorre05/esphome/tree/micronova
- https://github.com/eni23/micronova-controller

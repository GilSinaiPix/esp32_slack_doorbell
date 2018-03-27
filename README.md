# esp32_slack_doorbell

Doorbell with ESP32. "RING" is posted to Slack channel, instead of traditional sound. 

Preconditions:	

Create webhook in Slack for channel
Modify doorbell.ino
* Webhook
* Your Wifi SSID and KEY

ESP32 boots up, if boot is not from deep sleep, then goes to deep sleep else if boot is from deep sleep then ring
GPIO 14 is connected to Doorbell button, which wakes up ESP32
After ringing, goes deep sleep again. 

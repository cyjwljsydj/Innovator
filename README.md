# Innovator

# University Innovator Competition

This repository includes the project of the intelligent trolley of the University Innovator Competition.

All these files were edit in the Qt Creator presented in the Nvidia Jetson Nano using Linux system.
Apparently,the deployment of the opencv(Linux source) is necessary. So, remember to deploy the opencv source files in your Linux system then clone this project.
Additionally, some of the routes in the .pro file vary on each device, it depends on which kind of device you are using and exactly the route of your source files you deploy, so check the Qt documentation.
If you want to debug the trolley thoroughly,that means you need to use the serial cpp, but each device's serial port is locked in the default mode. So first you should get the access of the serial port, it can be accessed through the terminal orders, and the order vary depending on the device and the ports you use. The serial cpp in this projects only allows to send parameters to the serial port but not to get from it.

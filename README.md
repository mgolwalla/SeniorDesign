# Solar Panel Cleaner

## Overview

For our senior design project we created a solar panel cleaner to automate the cleaning process of solar panels to increase power output. The frame has the general structure of an xy plotter, controlling two dimensional brush movement with stepper motors and pulley systems. There is manual control through an app over bluetooth or automatic control when the computer vision script detects leaves through the camera's feed. This feed can be viewed live on a website accessible through the app.  

![Senior Design Flow Chart](https://user-images.githubusercontent.com/56405905/224863019-dfdd2868-c18e-4871-9937-a7d7563f195a.png)

### Frame

### Computer Vision
Imported images in Azure Custom Vision to tag images, train and test model. Then exported as TensorFlow Lite Float to run on raspberry pi's limited RAM. 
#### Performance
<img width="584" alt="image" src="https://user-images.githubusercontent.com/56405905/224867640-75cc4b1b-b835-425c-852b-9f8817993eb1.png">


### App

### Webpage

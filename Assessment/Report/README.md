# Report title goes here

Xin Cheng  
Github repo:https://github.com/zczqxc5/casa0018  
Edge Impulse projects:https://studio.edgeimpulse.com/public/362071/live  
Video presentation:https://youtu.be/uWszBTIhyO8  

## Introduction
This is a deep learning project based on neural networks, aimed at creating a smart dumbbell that recognises and counts movements during dumbbell workouts for fitness enthusiasts and provides prompts. By recognizing data from the built-in accelerometer on Arduino Nano, different dumbbell motions are detected, and an LED lights are connected to display exercise condition.  
Traditional dumbbells suffer from issues such as monotony, lack of fitness data recording, and inability to meet the precise control and recording needs of people's fitness data(Liu et al., 2019; Shiao et al., 2021). Although there are many applications on smartphones and smartwatches on the market that can record fitness data, they are not automated and do not interconnect with edge devices.  
The concept of the Internet of Things, deploying deep learning technology to edge devices (EMBEDDED AI), has provided a new intelligent interaction mode for dumbbell training (Meridou et al., 2017; Passos et al., 2021). This project successfully developed a program on the Arduino Nano 33, supported by tinyML and Edge Impulse, to monitor and record dumbbell exercises, achieving a recognition accuracy rate of up to 99.65%.  


## Research Question
Can an embedded AI project based on neural networks be constructed to recognize dumbbell exercise movements and assist fitness enthusiasts in counting?  


## Application Overview
This project consists of three parts:   
1) Manual recording of IMU data from dumbbell exercises.
2) Creating a deep learning model by conducting experiments involving different DSP modules, learning modules, parameter settings, and model architectures to identify the model with optimal performance for detection.  
3) Deploying the trained model onto an Arduino Nano board and connecting five LED lights.  

During the application process, the built-in IMU of the Arduino captures motion data every 2 seconds and converts it into spectral features. Subsequently, TensorFlow Lite runs the model to classify the detected motions into five types: "Dumbbell Row", "Hammer Curls", "Upright Row", "Deep Squat", and "other". If the probability for any type exceeds 0.8, the corresponding LED light will blink 3 times. When the count of a movement reaches ten, its corresponding LED light will stay on continuously, indicating that the training for that movement has been completed.  <br>

![image](https://github.com/zczqxc5/casa0018/assets/146037962/ca4a25ac-2c9a-456a-8e70-2a404fa8319b)
<p align="center"><em>Application Diagram</em></p>

![image](https://github.com/zczqxc5/casa0018/assets/146037962/8deb5ed1-56b4-406c-ae4d-cb46159f1997)
<p align="center"><em>Working Flow</em></p>
<br>

## Data
Gesture data are collected by the onboard accelerometer connected to the Arduino Nano (accX, accY, accZ, gyrX, gyrY, gyrZ, magX, magY, magZ). The experiment gathered 966 samples from 10 participants, totaling 34 minutes and 24 seconds, of which 81% and 19% were used for model training and test, respectively. This sample distribution was chosen to maximize the quantity of data and improve model accuracy. Fitness data were categorized into five labels: "Dumbbell Row," "Hammer Curls," "Upright Row," "Deep Squat," and "other". The first four fitness movement data were derived from ten participants of varying genders, heights, and fitness levels, using both left and right hands. They performed the movements by mimicking a standard reference video ("Top dumbbell exercises for your shoulders, back and arms | Technogym United Kingdom," n.d.). Data under the "other" label included potential dumbbell movements during fitness activities such as shaking, lying flat, rolling, and Interference movements. Additionally, the orientation of the dumbbell was considered during data collection, with arrows affixed to the dumbbell to indicate the direction of grip.

<br>
![image](https://github.com/zczqxc5/casa0018/assets/146037962/4dac507a-cd18-4b8c-af1d-dec4d46b96f5)
<p align="center"><em>Dembbell exercises I chose</em></p>
<br>
![image](https://github.com/zczqxc5/casa0018/assets/146037962/7ab79393-382a-4f9f-bc5c-ec0b39fd7991)
<p align="center"><em>Dembbell</em></p>
<br>


Table1: Data Information
|  | Dumbbell Row | Hammer Curls | Upright Row | Deep Squat | Other | All |
|:-------|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|
| Training | 149 | 151 | 144 | 142 | 193 | 799(81%) |
| Test | 33 | 43 | 39 | 38 | 34 | 187(19%) |
| All | 182 | 194| 183 | 180 | 227 | 966 |

<br>

## Model
This is a Deep Learning project! What model architecture did you use? Did you try different ones? Why did you choose the ones you did?

*Tip: probably ~200 words and a diagram is usually good to describe your model!*

## Experiments
What experiments did you run to test your project? What parameters did you change? How did you measure performance? Did you write any scripts to evaluate performance? Did you use any tools to evaluate performance? Do you have graphs of results? 

*Tip: probably ~300 words and graphs and tables are usually good to convey your results!*

## Results and Observations
Synthesis the main results and observations you made from building the project. Did it work perfectly? Why not? What worked and what didn't? Why? What would you do next if you had more time?  

*Tip: probably ~300 words and remember images and diagrams bring results to life!*

## Bibliography
*If you added any references then add them in here using this format:*

1. Last name, First initial. (Year published). Title. Edition. (Only include the edition if it is not the first edition) City published: Publisher, Page(s). http://google.com

2. Last name, First initial. (Year published). Title. Edition. (Only include the edition if it is not the first edition) City published: Publisher, Page(s). http://google.com

*Tip: we use [https://www.citethisforme.com](https://www.citethisforme.com) 
## Declaration of Authorship

I, AUTHORS NAME HERE, confirm that the work presented in this assessment is my own. Where information has been derived from other sources, I confirm that this has been indicated in the work.


*Digitally Sign by typing your name here*

ASSESSMENT DATE

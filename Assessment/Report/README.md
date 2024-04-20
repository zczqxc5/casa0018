# Smart Dumbbell_DL4SN Project
Author name: Xin Cheng  
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
 <br>
 
![image](https://github.com/zczqxc5/casa0018/assets/146037962/8deb5ed1-56b4-406c-ae4d-cb46159f1997)
<p align="center"><em>Working Flow</em></p>
<br>

## Data
Gesture data are collected by the onboard accelerometer connected to the Arduino Nano (accX, accY, accZ, gyrX, gyrY, gyrZ, magX, magY, magZ). The experiment gathered 966 samples from 10 participants, totaling 34 minutes and 24 seconds, of which 81% and 19% were used for model training and test, respectively. This sample distribution was chosen to maximize the quantity of data and improve model accuracy. Fitness data were categorized into five labels: "Dumbbell Row," "Hammer Curls," "Upright Row," "Deep Squat," and "other". The first four fitness movement data were derived from ten participants of varying genders, heights, and fitness levels, using both left and right hands. They performed the movements by mimicking a standard reference video ("Top dumbbell exercises for your shoulders, back and arms | Technogym United Kingdom," n.d.). Data under the "other" label included potential dumbbell movements during fitness activities such as shaking, lying flat, rolling, and Interference movements. Additionally, the orientation of the dumbbell was considered during data collection, with arrows affixed to the dumbbell to indicate the direction of grip.

Table1: Data Infomation
![image](https://github.com/zczqxc5/casa0018/assets/146037962/29d13847-f937-4689-aca9-b1bdf5c6c787)
 <br>

![image](https://github.com/zczqxc5/casa0018/assets/146037962/4c88ed8a-7670-44b8-8c1f-3c561d5391bb)

<p align="center"><em>Dumbbell exercises I chose</em></p>
 <br>

![image](https://github.com/zczqxc5/casa0018/assets/146037962/cf50bb06-277a-4673-a17a-dc58422b7cb5)

<p align="center"><em>Dumbbell</em></p>
 <br>

Data processing involves both pre-processing and post-processing stages. In the pre-processing phase, 30 seconds of continuous motion data are collected, as continuous motion captures transitions between movements and natural variations in the movements, which is closer to real-world usage scenarios ("Continuous motion recognition | Edge Impulse Documentation," 2024). Subsequently, by observing data characteristics, windows are manually segmented into equal 2-second intervals, eliminating intervals between movements and data with indistinct features.

![image](https://github.com/zczqxc5/casa0018/assets/146037962/34760eaf-3497-4584-a7dd-e8d7b877dde0)
![image](https://github.com/zczqxc5/casa0018/assets/146037962/76d69fda-6a06-458b-ab43-f8b391df74f4)
![image](https://github.com/zczqxc5/casa0018/assets/146037962/bdfedefd-17e9-4f71-8726-e12512b6f849)
<p align="center"><em>Data of each action completed by cutting</em></p>
 <br>

After the initial training of the model, erroneous data are marked with red dots. Among these, disruptive data—flaws present due to manual trimming—are identified and removed. For example, as shown in the incorrect data graph below, the selection of the cropping window is clearly incorrect, featuring nearly a second of stagnant gesture. After removing these data, the model is retrained.


![image](https://github.com/zczqxc5/casa0018/assets/146037962/b974a5cc-6eaf-46b1-a9a9-8186ea50d044)

![image](https://github.com/zczqxc5/casa0018/assets/146037962/34def87f-6455-4191-baf7-fbedeeb6fc35)
<p align="center"><em>Flaw Data</em></p>
 <br>


## Model
For continuous motion recognition, Edge Impulse offers DSP modules including Spectral Analysis and IMU (Syntiant). Additionally, the learning blocks provided include Classification and Anomaly Detection (K-means). These tools are integral for effectively processing and learning from sensor data, facilitating the development of robust models for recognizing diverse motion patterns.  
![image](https://github.com/zczqxc5/casa0018/assets/146037962/7d265477-62ea-4af0-aefc-f96b850b5913)
<p align="center"><em>DSP modules</em></p>
 <br>
 
![image](https://github.com/zczqxc5/casa0018/assets/146037962/6034dd8f-2e45-419d-8ee8-ba3ef0b48fb8)
<p align="center"><em>learning blocks</em></p>
 <br>

Under conditions where other variables (training cycles-1, learning rate-0.0005, batch size-32, etc.) were held constant, four tests were conducted with different combinations of the four modules. The experimental results showed that the best performance was achieved using the Spectral Analysis processing block and the Classification Learning Block. When these were applied, the model training reached a test accuracy of 97.18%.  
<br>
Table2: Blocks experiment 
![image](https://github.com/zczqxc5/casa0018/assets/146037962/97c5e744-1324-4c6d-ac0e-4830e5467631)
<br>

The parameter settings for the Spectral Analysis processing block are shown in the diagram below. It includes the setup of a low-pass filter, which helps to remove high-frequency noise from the signal. Subsequently, spectral features are extracted using FFT, and the extracted features undergo logarithmic transformation and frame overlapping to enhance their representational capability. This preprocessing step provides input features for the subsequent machine learning or deep learning models. The DSP results demonstrate a clear attenuation of the signal after 8Hz, indicating that the filter has successfully removed high-frequency noise.  
The Classification Learning Block offers automated model selection, which is particularly suitable for resource-constrained edge devices (IoT devices). This feature streamlines the deployment process, allowing for efficient model operation within limited hardware capabilities.  
![image](https://github.com/zczqxc5/casa0018/assets/146037962/e39a2bb9-7a52-4d70-9142-d3102f9c952f)
<p align="center"><em>DSP Result</em></p>
<br>

The final neural network architecture is depicted in the diagram below.
![image](https://github.com/zczqxc5/casa0018/assets/146037962/51eb2970-caa3-42f8-a5ed-28964ed599d6)
![image](https://github.com/zczqxc5/casa0018/assets/146037962/dd034384-25a9-4f97-93fe-03ee3290b778)




## Experiments
The project conducted three different types of experiments:   
1. Attempting to distinguish between left and right hand dumbbell movements.  
2. Adding noise (other) data.  
3. Modifying training parameters to find the most suitable model.  
<br>
Initially, each movement label was further subdivided into left-hand and right-hand actions to try to distinguish between them. However, subsequent tests revealed that the current model's capability to differentiate such subtle differences between the left and right hands was insufficient. Particularly for the dumbbell roll movement, the accuracy was even less than 50%, which is no better than random guessing. Consequently, the project abandoned the distinction between left and right hands and instead added more fitness movements for differentiation.  

![image](https://github.com/zczqxc5/casa0018/assets/146037962/b3004e2a-3985-4ad4-9031-eec6fc028e6d)
<p align="center"><em> left-hand and right-hand Model testing result</em></p>
<br>

The experiments found that without the addition of noise data, the model's accuracy was exceptionally high at 99.4%. However, during actual testing, some non-fitness movements were also misidentified as "fitness movements." This high accuracy rate was misleading due to the lack of noise data, which meant that any captured data was inevitably classified into one of the four fitness movements, even if they were not very similar. After incorporating other data (static, rolling, shaking, non-standard movements, and other fitness activities), the accuracy decreased to 97.18%. However, in practical tests, there were almost no instances of inaccurate recognition. This more realistic setting provided a significant improvement in the model's practical application.  
![image](https://github.com/zczqxc5/casa0018/assets/146037962/90e924da-c33f-4105-b2ae-0f983bb18191)
<p align="center"><em> Model testing result without noise data</em></p>
<br>

After selecting the model modules, the experiments also involved adjusting the neural network settings, including training cycles, learning rate, batch size, input layer features, and the number of neurons in the dense layer, in an effort to find the most efficient and accurate model configuration. A total of 12 experiments were conducted as follows, resulting in the most satisfactory data settings, achieving a test accuracy of 99.65%:  

Table3: Experiment
![image](https://github.com/zczqxc5/casa0018/assets/146037962/978fa0ef-ebd6-411a-bce3-f600405e0ec8)
<br>
Increasing the number of training epochs, although it extends the training time, significantly enhances accuracy. However, prolonged training can lead to overfitting, where the model learns the training data too well to the extent that it cannot generalize to unseen data. Therefore, a dropout layer was added to avoid this issue.  
![image](https://github.com/zczqxc5/casa0018/assets/146037962/b16af577-efda-464f-8b38-1aa8414742bf)
<br>

## Results and Observations
After extensive experimentation and testing, the model's test accuracy improved from the recommended settings provided by Edge Impulse at 97.18% to 99.65% through designing and fine-tuning the model parameters. Although it is not perfect, it is sufficiently accurate for practical applications. 
Table4: Final Result
![image](https://github.com/zczqxc5/casa0018/assets/146037962/78146e9e-9960-4d2d-af11-5c339ecc64e8)
<br>
![image](https://github.com/zczqxc5/casa0018/assets/146037962/17127bf8-ab39-43d8-a938-61f09eca35bf)
<br>
![image](https://github.com/zczqxc5/casa0018/assets/146037962/7d95efa6-c84f-4efd-88bf-7e1bfc188899)
<br>

The experiments revealed that the inclusion of 'other' data is crucial for enhancing the practical application capabilities of the AI model. Moreover, various parameters, including training cycles, learning rate, batch size, input layer features, and the number of neurons in the dense layer, are not necessarily better when they are higher or lower. Each change in data can affect training stability, generalization ability, risk of overfitting, convergence speed, and training time. These factors require experimental evaluation and holistic consideration during model training. Furthermore, the practical applicability of a model cannot be solely assessed by its test accuracy. Even with a very high accuracy, there is a risk that the model may not generalize well to unseen data.  

During the data collection phase, I neglected to differentiate the sources of the training and test data. They were both derived from the same ten individuals and randomly allocated proportionally. If two participants who were not involved in the training data collection could be added, and their data used to test the model, the actual application data of the model would be more realistically reflected. This is because the ultimate users of the model do not originate from the participants in the data collection. Although I invited a friend to test the dumbbell in real-time, and there were no inaccuracies, this test sample size is too small to prove the model's capabilities.  


If I had more time, I would first focus on collecting and expanding more data to enhance model stability, while also adding 200 test data points from different participants. Secondly, I would revisit the model approaches that were abandoned during the experiments: distinguishing whether each action is performed by the left hand or the right hand. Due to time and resource constraints, this approach was set aside in the early stages of the project. However, in reality, it could significantly enhance the applicability of the model, providing users with a more customized and interactive experience.  

## Bibliography
Continuous motion recognition | Edge Impulse Documentation [WWW Document], 2024. URL https://edge-impulse.gitbook.io/docs/tutorials/end-to-end-tutorials/continuous-motion-recognition (accessed 4.20.24).  
Liu, Yang, Hsu, C.-L., Liu, Yuan, 2019. An Intelligent Dumbbell Designed for Fitness Activity Monitoring, in: 2019 IEEE International Conference on Computation, Communication and Engineering (ICCCE). Presented at the 2019 IEEE International Conference on Computation, Communication and Engineering (ICCCE), pp. 29–32. https://doi.org/10.1109/ICCCE48422.2019.9010796  
Meridou, D.T., Papadopoulou, M.-E.Ch., Kapsalis, A.P., Kasnesis, P., Delikaris, A.I., Patrikakis, C.Z., Venieris, I.S., Kaklamani, D.I., 2017. Improving Quality of Life with the Internet of Everything, in: Batalla, J.M., Mastorakis, G., Mavromoustakis, C.X., Pallis, E. (Eds.), Beyond the Internet of Things: Everything Interconnected. Springer International Publishing, Cham, pp. 377–408. https://doi.org/10.1007/978-3-319-50758-3_15  
Passos, J., Lopes, S.I., Clemente, F.M., Moreira, P.M., Rico-González, M., Bezerra, P., Rodrigues, L.P., 2021. Wearables and Internet of Things (IoT) Technologies for Fitness Assessment: A Systematic Review. Sensors 21, 5418. https://doi.org/10.3390/s21165418  
Shiao, Y., Hoang, T., Chang, P.-Y., 2021. Real-Time Exercise Mode Identification with an Inertial Measurement Unit for Smart Dumbbells. Applied Sciences 11, 11521. https://doi.org/10.3390/app112311521  
Top dumbbell exercises for your shoulders, back and arms | Technogym United Kingdom [WWW Document], n.d. URL https://www.technogym.com/en-GB/best-dumbbell-exercises-shoulders-back-arms/ (accessed 4.20.24).  


## Declaration of Authorship

I, Xin Cheng, confirm that the work presented in this assessment is my own. Where information has been derived from other sources, I confirm that this has been indicated in the work.


*XIN CHENG*

ASSESSMENT DATE: 4/20/2024

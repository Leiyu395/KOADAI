# KOADAI

## An Arduino Obstacle-Avoidance Robot

### Photo:
<img width="3986" height="3386" alt="IMG_2427 (2)" src="https://github.com/user-attachments/assets/9f8a96c0-0d1b-4198-aa22-8cd05d6f1b81" />

### What it does:
 * Moves forward until the ultrasonic sensor detects an object
 * Servo motor will sweep the sensor left and right to find the best path (direction with the greatest distance)
 * The robot will then turn to move in that direction

### How to set it up and run it:
 * Setup Chassis: https://www.youtube.com/watch?v=t6nfFJCMNwY
 * Circuit Schematic: <img width="1365" height="1707" alt="KOADAI-layout" src="https://github.com/user-attachments/assets/52e7529e-d147-442b-886c-52a358d6e6fd" />

 * Upload the code onto the Arduino board using the Arduino IDE

### What components are needed:
| Item                       | Cost            | Link                                                                                                                                       | Contains                                                                                                                                                                                                 |
|----------------------------|-----------------|--------------------------------------------------------------------------------------------------------------------------------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Arduino Kit                | £45.00          | https://www.amazon.ca/ELEGOO-Compatible-Components-24-Lesson-Education/dp/B01D8KOZF4/ref=ast_sto_dp_puis                                   | UNO R3 Controller Board 1PC, Servo Motor SG90 1PC, Active Buzzer 1PC, Breadboard, USB Cable 1PC, Female-to-Male Dupont Wires, Breadboard Jumper Wires 65PCS, Resistors 120PCS, LED 25PCS                 |
| Chassis Kit                | £19.20          | https://thepihut.com/products/robot-chassis-kit-ms                                                                                         | Mecanum Wheels, Mobile robot mounting plate (large size), TT Motor, TT motor bracket                                                                                                                   |
| L298N Motor Stepper Driver | £7.00 (for two) | https://thepihut.com/products/l298n-motor-stepper-driver                                                                                   | L298N Motor Stepper Driver                                                                                                                                                                              |


#### Total Cost
£71.20

### Extra Information

For the sensor, I took inspiration from Russel Electronics on YouTube.

Link to the video: https://www.youtube.com/watch?v=QEIl2Nxot5M

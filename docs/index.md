---
layout: page
title: Project Overview
permalink: /
exclude: true
---
<div style="text-align: left">
  <img src="./assets/img/Logo.png" alt="logo" width="100" />
</div>

# Project Abstract
In this final project, we built a crane game controlled by an FPGA and MCU. The MCU will control mutliple stepper motors which allow the user to move a gantry in the x, y, and z directions via an external joystick. The MCU will interface with h-bridges that will provide the necessary power to move the entire carriage.  The FPGA will provide a visual component through a 32x32 LED matrix that will display a timer as well as additional light assortments to convey the different stages of the game.  The entire housing will be constructed out of 80/20 alumninum bars with wood finishes. All together, the user will be able to press a button, move the gantry around, drop the claw, and retrieve their prize. 

# Project Motivation
The motivation behind this project is that we are curious behind the mechanisms behind these common and seemingly simple games. Arcade games have been around for a long time and employ a variety of different hardware and software components, and we believe that it will provide a fun medium to learn more about real world systems. These games also require consistent operation under a variety of conditions over extended periods of time so it will also be interesting to see how the system responds to multiple tests. It will also be a test to prove the design 

# System Block Diagram
<div style="text-align: left">
  <img src="./assets/schematics/system_block_diagram.png" alt="sys" width="1000" />
</div>
Shown above is the system level block diagram of the crane game.  The MCU can receive up to 6 inputs from the user via the joystick and buttons. The MCU then controls the FPGA by asserting an enable line, and depending on the stage and joystick input, outputs the correct stepper motor sequence to the h-bridges.  The FPGA then ouputs the proper data message to the LED matrix to display the current time remaining or the starting the sequence.  The stepper motors control where the carriage moves and descends.  
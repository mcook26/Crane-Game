---
layout: page
title: Documentation
permalink: /doc/
---

# Schematics
### Overall System Level Diagram
<div style="text-align: left">
  <img src="./assets/schematics/system_block_diagram.PNG" alt="sys" width="1000" />
</div>

### Game Timing Diagram
<div style="text-align: left">
  <img src="./assets/schematics/game_timing.PNG" alt="game" width="1000" />
</div>

### System Schematic
<div style="text-align: left">
  <img src="./assets/schematics/full_schematic.PNG" alt="schem" width="1000" />
</div>


# Source Code Overview
<!-- This section should include information to describe the organization of the code base and highlight how the code connects. -->

The source code for the project is located in the Github repository [here](https://github.com/mcook26/Crane-Game/tree/main/src).

The MCU code is organized by having multiple sequential while loops.  Because gameplay is rather streamlined with few places of variability, it is easier to design using this structure. The first step is to press the button which exits the first loop. Then once the timer is up or the button is pressed again, you exit the second loop.  Finally, once the system attempts to return home, the final two loops are exited. 

As noted in the design section, the MCU interfaces with the FGPA via a 1 bit enable line that is asserted upon the first button push and deasserted after the second button push or time runs out. This line directly controls each stage of the FGPA's display sequence by either starting or ending it.

The FGPA code is organized into a top level module that controls all of the functionality as well as performs boolean operations to set the display output.  These are determined based on the timer submodule which increments after each slow clock cycle.  More details are provided in the FGPA section.

Test change


# Bill of Materials
<!-- The bill of materials should include all the parts used in your project along with the prices and links.  -->

| Item | Part Number | Quantity | Unit Price | Link |
| ---- | ----------- | ----- | ---- | ---- |
| 5 stepper motors |  B094F4CH71 | 1 | $26.99 |  [link]([https://www.adafruit.com/product/3317](https://www.amazon.com/VEVOR-Stepper-Stepping-Printer-Extruder/dp/B094F4CH71/ref=sr_1_2?crid=LM3SP4EJBXVF&keywords=vevor+stepper+motor+59+ncm&qid=1670566600&s=industrial&sprefix=vevor+stepper+motor+59+nc%2Cindustrial%2C226&sr=1-2)) |
| Joy Stick |  B01N2G0H1T | 1 | $11.99 |  [link]([https://www.adafruit.com/product/3317](https://www.amazon.com/EG-STARTS-Arcade-Classic-Competition/dp/B01N2G0H1T/ref=sr_1_1?keywords=eg+start+red+arcade&qid=1670566339&sr=8-1)) |
| Button |  0654913663700 | 1 | $6.99 |  [link]([https://www.adafruit.com/product/3317](https://www.amazon.com/Twidec-Waterproof-Momentary-Modification-Switch%EF%BC%88Quality/dp/B07P5WNJG8/ref=asc_df_B07P5WNJG8/?tag=hyprod-20&linkCode=df0&hvadid=398540768796&hvpos=&hvnetw=g&hvrand=17157778640646146457&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=1014089&hvtargid=pla-843183269405&psc=1&tag=&ref=&adgrpid=92996539388&hvpone=&hvptwo=&hvadid=398540768796&hvpos=&hvnetw=g&hvrand=17157778640646146457&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=1014089&hvtargid=pla-843183269405)) |
| Wood |  796758 | 1 | $44.89 |  [link]([https://www.adafruit.com/product/3317](https://www.lowes.com/pd/Top-Choice-SkyPly-1-4-in-HPVA-Maple-Plywood-Application-as-4-x-8/1000083311)) |
| Extra Materials |  Stock Room | x | x |  Thank you Sam

**Total cost: $90.87**

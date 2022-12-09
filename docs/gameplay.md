---
layout: page
title: Gameplay
permalink: /gameplay/
---
Here is a video of the system's full operation.

<iframe width="560" height="315" src="https://www.youtube.com/watch?v=sIIKwWzw8-U" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

From the video, it can be seen that the system does have almost complete functionality.  From the MCU, the stepper motors do move with the joystick, and the crane does fall and rise at the end of the turn.  The game logic all works, and the timing is easily configurable to make it longer or shorter.  The user can also control and reset the game when needed.  On the FGPA side, there is a display sequence on the FGPA display that does sync with the MCU and the rest of the game.  This works consistently, and provides the user with a nice visual input.

However, there are a few places that the project came up short.  Due to the nature of stepper motors and environmental inconsistencies, it was difficult to have the gantry move forward and backwards consistently.  We iterated on the design multiple times throughout our design process, adding in a variety of additional mechanical components to try and ensure that the carriage moved smoothly.  However, because the system is not exactly perfect and a lot of the parts were taken from what was accessible, there will be inconsistent movement. The gantry tends to lean in one direction and results in a lack of motion.  However, the center motor if kept straight will keep this movement to a minimum.  This inconsistent motion led to difficulties with the return feature that brought the gantry back to the original starting point.  The code has the infrastructure to perform the task, and it does work if the motion is smooth, but it accuracy hinges on random environmental factors. Despite the stepper motors being the same as well as the power source and control signals, there will be inconsistencies with the stepper motors, and this will result in issues for the user.

Moving forward or if more time was available, the team would spend more time developing a more consistent method of forward and reverse movement.  This would provide us with a platform that could return to the start position easier, and it would make the user’s experience overall better. Another step could be the introduction of an actual claw instead of a magnet such that the user could pick up a variety of prizes.  Overall, the system worked well, and the team is happy with the results. 


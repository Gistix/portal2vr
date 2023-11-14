### I(Juliasmatius/original writer) will **not** be addressing *any* crashes. If someone else wants to, make a fork of the repo, edit it, and make a pull request.

# How to enable 6DOF (by qwertylesh)
1. Browse the Portal 2 local files.

![image](https://github.com/Juliasmatius/portal2vr/assets/80146546/1f514b95-f06b-46cd-90cd-40000c5d9aa4)

2. Open the VR directory.

![image](https://github.com/Juliasmatius/portal2vr/assets/80146546/33bd4618-274f-4a58-ba76-8d445d9e2730)

3. Open the config file.

![image](https://github.com/Juliasmatius/portal2vr/assets/80146546/c2b1ee86-5176-4893-b864-e28ae6474543) 

4. Set 6DOF to true.

![image](https://github.com/Juliasmatius/portal2vr/assets/80146546/d0f473f3-8342-4eb0-9370-a586aad38f0b)

5. Save and relaunch the game.

# I am too tall/head is in the ceiling.
Press the left thumbstick.

# FPS is low/I can't hear anything.
Make sure to focus the game's window (Click it last).

# Game launches, but don't see in VR.
If you're using an Oculus headset with the Oculus app, go to Settings -> General -> Enable "Unknown Sources"


# How do I stream/record gameplay?
There are two options.
In the config, set RenderWindow to 1. (lowers performance)
Enable "Display VR View" in SteamVR (doesn't allow audio capture on programs like Discord)

# How do I play co-op?
To play co-op the person in VR needs to have the [latest preview](https://github.com/Gistix/portal2vr/releases).  \
The person in VR needs to be host.

# My portal gun is far away.
In the config file, edit the following:
```
ViewmodelPosCustomOffsetX
ViewmodelPosCustomOffsetY
ViewmodelPosCustomOffsetZ
```


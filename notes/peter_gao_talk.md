# Cruise Introduction
* Started in 2014 
* Got acquired by GM in march 2016
* Driving in san francisco makes it really hard for self-driving cars.
* Goal: Ship self-driving cars at scale 
* Unlike lifts and  monorail environment is unconstrained.
* HD maps: Maps with granularity dealing at lane level. Google maps has road level view. 
* Low Latency: models will be running on car hardware and should be able to decide as quickly as 
  a human
* Correctness: Models should have low false negatives. Hitting a pedestrian on the road is highly
  unwanted behavior.
* Robust: Since, hardware to run the software is on the car(resistant to outside temperature, shocks)
* Sensors 
    * Lidar : Big Spinny thing. shoots out laser beam in the world. Assembles 3d point clouds.
    Colors denote the intensity of the objects. Critical for depth information. Great 360 view.
        * Cons: 
            * Its sparse.
            * It's an optical system. Can't work under fog conditions. or places where light can not reach.
            * Doesn't discriminate colors.
            * Needs line of sight to work.
            * Involves moving parts
            * Big ugly think on top of car. Ugly doesn't sell.
    
    * Radar
        * Works regardless of weather conditions 
        * Accurate distance and speed readings
        * Cons
            * Only one direction
            * Can not see color/brightness. Brake lights/hazard lights/turn signals would be ignored
        
    * Camera 
        * Recognize colors
        * Can create 3d maps of surrounding 
        * Useful for reading road signs/traffic lights/lane marking
        * Cons
            * Depends upon lighting conditions. Wouldn't work in very dark or flashy conditions.
            * Less reliable for depth perception and speed.
            
# Computer vision in self-driving cars
* CV in self-driving is different from academia and Web technology domain, as here we have more 
  control on hardware and improvements in performance can also come from hardware and imposed constraints.
* Cameras are popular choice, because Deep Learning has really taken off recently and CPU/GPU 
  cost has come down. Automotive grade cameras are better cheaper and better.
* Working with Camera Hardware
    * Can't put 10 DSLR on car. Too bulky. Suck power. Data is too much to save to disk. 
    * Durability and Reliability. Resistance to weather and shock.
    * Second order things: Enough compute power to handle it ? Enough bandwidth to handle the data 
     coming in. Enough Disk capacity to hold the data. 
    * Tune camera to look for things. At night, Adjust shutter speed to identify the objects. 
     Same cameras can be tuned to make sensitive to colors in order to spot colors.
    * Intrinsic Calibration : Camera lens make lines e.g. wires over road curved. We need to make them
    straight before processing.
* After we get the data, we label the data. Image labelling view for traffic lights, 
bounding boxes around cars/buses and around pedestrians.
* Spark for data processing.
* Taking action on traffic lights is one of those things where its easy to get to 99 % and last 
1 % is hard to squeeze in.
* Vehicle light detection: if a car has hazard lights on, we would want to detect that and 
 overtake thar car. List of edge cases is really long. some cars ust flash lights in 
 totally different way.
* A walk through funny corner cases.


 
  
    
    
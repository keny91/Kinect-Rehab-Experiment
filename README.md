# Kinect-Rehab-Experiment

Often, after an accident, many patients have their mobility restrained. This situation is usually a temporary issue, and the recovering process can be accelerated by following the proper rehabilitation routines. Under normal circumstances, the whole recovery process would be monitored by a specialist in a controlled environment such a clinic or a hospital. However, this procedure carries plenty of inconveniences with it. The fact that the patient is required to move to specific locations even if there are services that greatly facilitate the displacement remains. Additionally, the rehabilitation exercises often require supervision of professional personnel instructed in the utilization of any particular equipment necessary. The cost carrying out rehabilitation is already really high. Also, there is a risk to restrained mobility patients when having them strive to reach the installations on a frequent basis.


This application presents a solution. An application based on the Kinect technology and implemented with the help of NiTE2 ([OpenNI0](http://openni.ru/files/nite/)) libraries. The application has two different working modes: Comparing and Recording.


## Recording Process.

This process will create an identical reproduction of a gesture performed by a user in front of the device. It automatically creates a new folder with all the required files to make this new move enter the comparison process.

## Comparison Process.

Two different gestures must be selected for this functionality, one from the GT folder and another from the Sample´s one. The gestures are selected by inputing the name with which they were recorded. The comparison will use the Dynamic Time Warp algorithm to find how similar are both streams of data.



Sergio González Quirós
Luis carrillo
Angel

Modificar el app en la BB-xM:
cd /libfreenect/wrappers/Kinect-Mouse
vi mouse.cpp

Compilar la aplicacion en la BB-xM:
cd /libfreenect/build
./prueba.sh

Corre la aplicacion en la BB-xM:
cd /libfreenect/build/bin
sudo ./mouse 172.0.0.1 # ip de la compu

Corre la aplicacion en la PC:
qtcreator chatserver.pro

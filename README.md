# Krabbs

Main code for the year 2021-2022.

## Project structure
```
root
├───includes
├───res
└───src
```

- includes : contains the header files (ex: Controller.h)
- res : contains all the resources needed for the project (ex: conf.info, fileactions etc)
- src : contains the source files (ex: main.cpp etc)

## How to run it ?

1. Clone this repository
```
git clone https://github.com/ENSIMelec/Krabbs.git
```
2. Do some coding !

3. Connect to the Raspberry

To connection is made using SSH. Once the robot is powered and ready, connect to the WIFI and run the following command :
```
ssh pi@robot
```

4. Clone your files on the Raspberry

5. Go inside the root folder

6. Build the program
The program is built with a Makefile. Use the following command :
```
make
```

7. Run the program
```
./build/bin/krabbs
```

8. Enjoy ! :)

# Dependencies

Here are all the dependencies we are using :
- ptree
- wiringPi
- Dynamixel SDK
- Cmake

Don't forget to do `sudo apt update && upgrade` before installing anything.

## Ptree

To install ptree, do the following : 
```
sudo apt install libboost-all-dev
```

*Note that it will install a bunch of things. If you know how to install only ptree, feel free to update this file.*

## Wiring Pi

- [Documentation](http://wiringpi.com/)
- [Non official Github](https://github.com/WiringPi)

To install Wiring Pi on your Raspberry Pi, follow these instructions :

#### Step 1 : Cloning the repository

Clone Wiring Pi repository into your Raspberry

```
git clone https://github.com/WiringPi/WiringPi
```

#### Step 2 : Building WiringPi

This will build the needed files into `/usr/local/lib/` directory. Don't forget to link `wiringPi` lib when using CMake.

```
cd WiringPi
./build
```

#### Step 3 : Adding the directory to PATH

*This step might be optional*

Some distributions do not have /usr/local/lib in the default LD_LIBRARY_PATH. To 
fix this, you need to edit /etc/ld.so.conf and add in a single line:

```/usr/local/lib```

then run the ldconfig command.

```sudo ldconfig```

#### Step 4 : Enabling I2C

On recent versions of raspberries, I2C is not activated by default.

Run ```sudo raspi-config```

Then go to Interfacing options > I2C > enable

## Dynamixel SDK

Go [here](https://github.com/ENSIMelec/Krabbs/blob/main/docs/AX12.md) and follow the install instructions for the SDK.

## CMake

Simple `sudo apt install cmake` will do.

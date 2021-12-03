# How to setup remote developement with CLION ?

First, make sure you can connect in ssh to the remote host ! You will need the host (ip or hostname) and the password.

## Setup Toolchain

Go to `Settings > Build, Excecution, Deployment > Toolchains`. 

Add a new *Remote host*.

In the credential field, configure a new connection using the gear icon.

Add a new SSH Configuration, enter the host and the password.

<img src="docs/setup clion/Add a new SSH Connection.png">

Verify that the connection works and that CLION found every tools !

You should get something that looks like that :

<img src="docs/setup clion/Setup Toolchain.png">

## Setup CMake

We are using CMake to build and deploy the project. In the CMake tab, add a new *Profile*.

Set the build type to Default and select the previously created Toolchain.

Set the build directory to something like *cmake-build-krabbs*

<img src="docs/setup%20clion/Setup CMake.png">

## Setup Run Configuration

Go to `Run/Debug Configurations` and add a new *CMake Application* configuration. Call it *build and run*

In the target field, set *krabbs*

<img src="docs/setup%20clion/Create Build and Run Configuration.png">

You can create an other configuration to simply run the program without rebuilding it.

Repeat the previous step but remove the *build* action in the *before launch* field.

## Edit the path of the remote repository

If you want to switch in which directory the project will be copied on the remote host, go to `Settings > Build, Execution, Deployment > Deployment`.

Select the correct Remote Developement modify the *root path*. 

<img src="docs/setup%20clion/Set Root Path.png">

You can go to the *Mapping* tab and modify the deployment path. *

<img src="docs/setup%20clion/Set Deployment Path.png">

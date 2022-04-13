# Krabbs

Main code for the year 2021-2022.
Please see the coding guidelines in the project repository before starting to code.

We are using a repository for the code that will be shared among all robots. You must clone the `base` repository inside the `src` directory.
To do so, follow the following instructions :
```
git clone https://github.com/ENSIMelec/Krabbs.git
cd Krabbs/src
git clone https://github.com/ENSIMelec/base.git
```

## Project structure
```
root
├───arduino
├───docs
├───src
|   ├───base
|   └───main.cpp
├───build
└───res
```

- arduino : contains the .ino files for the arduinos
- docs : contains all the documentation for the project
- res : contains all the resources needed for the project (ex: conf.info, fileactions etc)
- base : file from the base repository (https://github.com/ENSIMelec/base.git)
- build : contains the build files. Including the executable `krabbs`
- src : contains the source files (ex: main.cpp etc)

## How to run it ?

- See the configuration explanation for CLion remote development [(here)](https://github.com/ENSIMelec/Krabbs/blob/main/docs/tutorials/Clion%20Remote%20Setup/CLion%20Remote%20Setup.md)
- See dependencies [(here)](https://github.com/ENSIMelec/Krabbs/blob/main/docs/Dependencies.md)

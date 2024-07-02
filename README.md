# bmp-info
## About
Tool to get information about bmp image
## Quick start
If you're running this on linux and want to compile the RISC-V and ARM architecture, you should:
1. _Qemu_ 
    ```bash
    sudo apt install qemu-user
    ```
2. Need to install compiler for RISC-V and ARM
   ```bash
   sudo apt install gcc-arm-linux-gnueabi
   ```
   ```bash
   sudo apt install gcc-riscv64-linux-gnu
   ```
3. Run 
   ```bash
    sh ./scripts/buildarm.sh "Your BMP file" //for ARM
   ```
    ```bash
    sh ./scripts/buildriscv.sh "Your BMP file" //for RISC-V
    ```
### Examples
All examaple are in the `bmpfiles` folder
#### Author
[Ishbaev Azamat](https://github.com/odiumuniverse)
#### Licence
This project is distributed under the Unlicence licence

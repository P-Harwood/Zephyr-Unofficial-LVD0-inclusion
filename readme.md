# LVD0 for RA6M5 on Zephyr with bankswap

## Wiring

- UART connector to P411 (Board's Tx) and P410 (Board's Rx) for interacting with the board

## Install Steps (Start in desired install directory):
```    
py -3.12 -m venv .venv
cd .venv\Scripts
activate.bat
cd ../../
pip install west
west init -m https://github.com/P-Harwood/Zephyr-Unofficial-LVD0-inclusion.git --mr mcuboot .
west update
west packages pip --install
west sdk install -t arm-zephyr-eabi
west zephyr-export
```
## === === Commands === ===

#### Build command - Run from project directory

##### Single build command
```
west build -b ek_ra6m5 -d build/v1 --sysbuild . -p always -- -DCONFIG_MCUBOOT_IMGTOOL_SIGN_VERSION=\"1.0.0\" 
```
##### Test batch build command

Default build command:
```
west build -b ek_ra6m5 -d build\v1 --sysbuild . -p always -- -DCONFIG_MCUBOOT_IMGTOOL_SIGN_VERSION=\"1.1.0\" 
west build -b ek_ra6m5 -d build\v2 --sysbuild . -p always -- -DCONFIG_MCUBOOT_IMGTOOL_SIGN_VERSION=\"1.2.0\" 
west build -b ek_ra6m5 -d build\v3 --sysbuild . -p always -- -DCONFIG_MCUBOOT_IMGTOOL_SIGN_VERSION=\"1.3.0\"
```

#### Flash command - Run from project directory
```
west flash -d build/v1
```
#### To Flash the bank 1 image variant with jlink:

1. Open JLink 
```
JLink.exe -device R7FA6M5BH -if SWD -speed 4000 -autoconnect 1
```

2. Loadfile the bank1 hex
For image V1.2.0:
```
loadfile build\v2\lvd_db\zephyr\app_bank1.hex
r
g
exit
```

For image V1.3.0:
```
loadfile build\v3\lvd_db\zephyr\app_bank1.hex
r
g
exit
```

#### Manually and set LVD0 to default values
1. Open JLink 
```
JLink.exe -device R7FA6M5BH -if SWD -speed 4000 -autoconnect 1
```

2. Loadfile the LVD reset hex
```
loadfile OFS_HEX/LVD.hex
r
g
exit
```

### Reccomended example order:
1. On an erased board, with default OFS, flash the v1.1.0 project
2. Wait for the application to confirm the image
3. Flash v1.2.0 bank1 version to the device
4. Reset the board before the countdown finishes.
5. Observe the application revert to v1.1.0
6. Flash v1.3.0 bank1 version to the device
7. Wait for the countdown to finish, the application will then confirm v1.3.0
8. Flash v1.2.0 bank1 version to the device
9. Observe the application ignore v1.2.0 as it is an operating system downgrade
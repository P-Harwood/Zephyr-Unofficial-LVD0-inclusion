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
west build -b ek_ra6m5 -d build\v1 --sysbuild . -p always -- -DCONFIG_MCUBOOT_IMGTOOL_SIGN_VERSION=\"1.1.0\" 
```
##### Test batch build command
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
```
loadfile build\v1\lvd_db\zephyr\app_bank1.hex
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
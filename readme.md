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

```
west build -b ek_ra6m5 -d build/v1 --sysbuild . -p always
```

#### Flash command - Run from project directory

```
west flash -d build/v1
```


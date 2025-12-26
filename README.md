#   My QMK keyboard layout

Based on Miryoku Layout

- Don’t connect or disconnect the TRRS cable when the keyboard is powered. Always disconnect the USB cable first.
- Flash the firmware on both Raspberry Pi Picos.
- Enter the bootloader mode by holding down the BOOTSEL button while reconnecting the board into USB port.

https://github.com/beekeeb/piantor

https://github.com/qmk/qmk_firmware/tree/master/keyboards/beekeeb/piantor

## Keyboard Layers App companion

Display the selected keyboard layer layout on screen to assist your to memorize the key's locations.

It allows you to display the layout in a remote screen, so you can use a tablet or similar to save space on your main screen.

Details here: https://github.com/maatthc/miryoku_qmk_app

## Compile and Flash

### Install and setup
- Install QMK:
`python3 -m pip install qmk`

- Initialize the sub-modules:
`git submodule update --init --recursive`

- Set this folder as an userspace:
`qmk config user.overlay_dir="$(realpath qmk_userspace)"`

- Set up QMK:
`cd ..; qmk setup`

### Install old GCC 8.3.0
Reduces size considerably (~1.5k):

`./install_avr_8.3.0.sh`
export PATH=${HOME}/avr_toolchain/bin:$PATH

### Compile
`qmk compile -kb beekeeb/piantor -km maat`

### Flash
`qmk flash -kb beekeeb/piantor -km maat`

### Generates the clang compile_commands.json
`qmk compile --compiledb -kb crkbd/rev1 -km maat`

### Check debug logs
`qmk console`

### info

`qmk info -kb beekeeb/piantor -km maat`

## Configuration

- users/maat/
- keyboards/beekeeb/piantor/keymaps/maat/

### Typing Test

https://config.qmk.fm/#/test

### Symbols that correspond to keycodes available in QMK.
https://docs.qmk.fm/keycodes

## Generated Layout/Layers images

Json files and images at: ./data/layers/

- ![Base](./data/layers/miryoku-kle-base.png)

- ![Media](./data/layers/miryoku-kle-media.png)

- ![Nav](./data/layers/miryoku-kle-nav.png)

- ![Mouse](./data/layers/miryoku-kle-mouse.png)

- ![Symbols](./data/layers/miryoku-kle-sym.png)

- ![Numbers](./data/layers/miryoku-kle-num.png)

- ![Fun](./data/layers/miryoku-kle-fun.png)


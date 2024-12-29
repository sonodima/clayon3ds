# Clay on the 3DS

Just because we can.

## Known Issues

- Inputs are handled on mouse down _(which is in conflict with scrollable containers)_

## Compiling

```bash
/opt/devkitpro/portlibs/nds/bin/arm-none-eabi-cmake -S . -B Build

cmake --build Build --config Release
```

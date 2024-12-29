# Clay on the 3DS

Just because we can.

## Issues

- Short strings often won't render _(this also happens with text wrapping)_
- Scissoring is not perfect _(works perfectly with texts, breaks down when the children are rectangles)_
- Inputs are handled on mouse down _(which is in conflict with scrollable containers)_

## Compiling

```bash
/opt/devkitpro/portlibs/nds/bin/arm-none-eabi-cmake -S . -B Build

cmake --build Build --config Release
```

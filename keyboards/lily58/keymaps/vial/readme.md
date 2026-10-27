# Lily58 Vial keymap: trackpoint (left) + TPS43 touchpad (right)

A port of my ZMK Corne layout ([`zmk-config/config/corne.keymap`](https://github.com/schlechter32/zmk-config)) to the Lily58.
The keys the Corne doesn't have (the number row, the two inner keys and the outer thumbs) are used for extras.
The source is [`keymap.c`](keymap.c).

**How to read the tables:** the top line in a key is the tap, the small line below it is the hold.
An empty key falls through to the layer below it.

## BASE

| | | | | | | | | | | | | | |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| &#96; | 1 | 2 | 3 | 4 | 5 | | | 6 | 7 | 8 | 9 | 0 | - |
| Esc | Q | W | E | R | T | | | Y | U | I | O | P | Bksp |
| Tab<br><sub>Shift</sub> | A<br><sub>Ctrl</sub> | S<br><sub>GUI</sub> | D<br><sub>Alt</sub> | F<br><sub>LOWER</sub> | G<br><sub>RAISE</sub> | | | H<br><sub>RAISE</sub> | J<br><sub>LOWER</sub> | K<br><sub>Alt</sub> | L<br><sub>GUI</sub> | ;<br><sub>Ctrl</sub> | Enter<br><sub>Shift</sub> |
| Del | Z | X | C | V | B | [<br><sub>Ctrl+Shift</sub> | ]<br><sub>Ctrl+Shift</sub> | N | M | , | . | ' | /<br><sub>Meh</sub> |
| | | | Left click | RAlt | LOWER | Space<br><sub>Meh</sub> | Ctrl+Bksp | RAISE | RAlt | Right click | | | |

- **Home-row mods:** Ctrl / GUI / Alt on A S D and K L ;. Layer-taps on F G H J (LOWER / RAISE).
- **Inner keys:** tap for `[` / `]`, hold for Ctrl+Shift, so the left pinky doesn't have to hold both Ctrl (A) and Shift (Tab).
  They work with keys on either hand. Holding one alone, e.g. for Ctrl+Shift+click, takes the 280 ms tapping term.
- **Meh** is Ctrl+Shift+Alt.

## LOWER (hold the LOWER thumb, F or J)

| | | | | | | | | | | | | | |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|   |   |   |   |   |   | | |   |   |   |   |   |   |
| F1 | F2 | F3 | F4 | F5 | F6 | | | F7 | F8 | F9 | F10 | F11 | F12 |
|   | _ | +<br><sub>Ctrl</sub> | ^<br><sub>Alt</sub> | $<br><sub>GUI</sub> |   | | | ← | ↓ | ↑ | → | End |   |
|   | ~ | Drag scroll | Middle click | Snipe | F11 |   |   | Home | PgDn | PgUp | End | PgUp |   |
| | | |   |   |   |   |   |   |   |   | | | |

## RAISE (hold the RAISE thumb, G or H)

| | | | | | | | | | | | | | |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|   |   |   |   |   |   | | |   |   |   |   |   |   |
|   | @ | ! | { | } | & | | | ^ | 7 | 8 | 9 | $ |   |
|   | - | \ | ( | ) | * | | | 0 | 4 | 5 | 6 | = |   |
|   | &#96; | # | [ | ] | % |   |   | \| | 1 | 2 | 3 | , |   |
| | | |   | → PLAIN |   |   |   |   |   |   | | | |

## ADJUST (hold LOWER + RAISE)

| | | | | | | | | | | | | | |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| Clear EEPROM |   |   |   |   |   | | |   |   |   |   |   |   |
| Boot | RGB on<br><sub>off</sub> | RGB mode | Hue − | Hue + | Scroll lock | | |   |   |   |   |   | Boot |
|   | DPI | DPI snipe | Scroll speed | Save pointer | Snipe toggle | | |   | ↓ | ↑ |   |   |   |
| Shift | Bright − | Bright + | Sat − | Sat + | Drag toggle |   |   |   |   |   | Reset pointer | Dump pointer |   |
| | | |   |   |   |   |   |   |   |   | | | |

**Changing pointer speed:** hold LOWER + RAISE, hold *DPI* (or *DPI snipe* or *Scroll speed*), tap ↓ / ↑.
Then tap *Save pointer* so the setting survives a reboot. Also hold *Shift* (bottom-left on ADJUST) to tune the touchpad on the right half instead of the trackpoint.

## PLAIN (RAISE → left RAlt thumb, back with the same key)

Plain letters with no home-row mods, for typing-speed practice and games.

| | | | | | | | | | | | | | |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|   |   |   |   |   |   | | |   |   |   |   |   |   |
|   | Q | W | E | R | T | | | Y | U | I | O | P |   |
|   | A | S | D | F | G | | | H | J | K | L | ; |   |
|   | Z | X | C | V | B |   |   | N | M | , | . | ' |   |
| | | |   | → BASE |   |   |   |   |   |   | | | |

## Tap-hold behaviour

| Setting | Value | ZMK equivalent |
|---|---|---|
| Tapping term | 280 ms (one value for all keys) | `tapping-term-ms` |
| Permissive hold | on | `flavor = "balanced"` |
| Chordal hold | on, thumbs count for both hands | `hold-trigger-key-positions` |
| Prior idle | 150 ms on the home-row keys, Space and / | `require-prior-idle-ms` |

The tapping term and permissive hold can be changed at runtime in Vial → *QMK Settings*.
Flashing new firmware resets them to the values above, and also resets any keymap changes made in Vial. `keymap.c` is the source of truth.

## Build and flash

```sh
util/flash_lily58.sh --build   # build both halves, then flash them one after the other
util/flash_lily58.sh           # flash the existing build
```

Keep the TRRS cable connected. Only plug or unplug TRRS when no USB cable is connected.

- *Boot* is on ADJUST at Esc (left) and Backspace (right). Either one reboots **the half that has the USB cable** into the bootloader.
- **Left half** (the normal USB side): LOWER + RAISE + *Boot*. No unplugging needed.
- **Right half:** move the USB cable to the right half, then LOWER + RAISE + *Boot* (or double-tap its reset button).
  Never connect USB to both halves at once while TRRS is connected.
  The keymap only runs on the left half, so **keymap-only changes just need the left half flashed**; answer `n` for the right one.
  Reflash both halves when `config.h`, `rules.mk` or the userspace changes.

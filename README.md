# Tetris — STM32F429

Fully playable Tetris implemented in C for the STM32F429ZIT6 microcontroller. Built as a final project for ECEN at CU Boulder, the game runs entirely on bare-metal hardware with a custom LCD driver, touchscreen input, and an event-driven scheduler — no RTOS.

## Hardware

| Component | Part |
|---|---|
| Microcontroller | STM32F429ZIT6 (ARM Cortex-M4, 336 MHz) |
| Display | ILI9341 — 320×240 TFT LCD |
| Touchscreen | STMPE811 touch controller |
| Dev board | STM32F429I-DISC1 |

## Features

- Full Tetris ruleset — piece spawning, rotation, collision detection, line clearing, and scoring
- Start screen, active gameplay, and game-over screen with state transitions
- Timed block descent driven by a hardware timer peripheral
- Touchscreen controls via STMPE811 GPIO interrupt
- Random piece selection using the STM32 hardware RNG peripheral

## Project Structure

```
Core/
├── Src/
│   ├── main.c              # Entry point, peripheral init, main loop
│   ├── ApplicationCode.c   # Top-level application init and game loop dispatch
│   ├── Game.c              # Tetris game logic — pieces, board, scoring
│   ├── LCD_Driver.c        # ILI9341 display driver and rendering utilities
│   ├── RNG_Driver.c        # Hardware random number generator for piece selection
│   ├── Scheduler.c         # Event-driven scheduler for game state management
│   ├── Timer.c             # Hardware timer config for block descent timing
│   ├── fonts.c             # Bitmap fonts for UI text rendering
│   ├── ili9341.c           # Low-level SPI communication with the LCD
│   └── stmpe811.c          # Touchscreen controller driver
└── Inc/                    # Corresponding header files
```

## Architecture

The game is built around a lightweight event-driven scheduler rather than a polling loop or RTOS. Hardware timers fire scheduler events at fixed intervals, and the main loop dispatches on event type:

```c
switch (event) {
    case StartScreen:   // Render menu, wait for touch
    case GameScreen:    // Initialize board, spawn first piece
    case BlockDown:     // Advance piece one row; check for line clears
    case BlockRotate:   // Handle rotation input from touchscreen
    case EndScreen:     // Display score, wait for restart
}
```

This keeps game logic, rendering, and input handling cleanly separated and makes timing deterministic without needing an operating system.

## Build & Flash

Developed using **STM32CubeIDE**. To build and flash:

1. Clone the repo and open in STM32CubeIDE (`File → Open Projects from File System`)
2. Build with `Project → Build All` (or `Ctrl+B`)
3. Flash via `Run → Debug` with the STM32F429I-DISC1 connected over ST-LINK USB

The `.ioc` file (STM32CubeMX config) is included — peripheral assignments and clock configuration can be viewed and regenerated from there.

## Author

Oliver Browne — Electrical Engineering, CU Boulder

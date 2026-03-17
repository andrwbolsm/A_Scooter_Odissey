# A Scooter Odyssey

A 2D endless-runner game written in C, developed as a course project for the Algorithms and Programming class in the Aerospace Engineering program at the Federal University of Santa Maria (UFSM), Brazil.

---

## About

*A Scooter Odyssey* is inspired by the Chrome T-Rex game. The player controls a character riding a scooter across the UFSM campus, dodging randomly generated COVID-19 virus obstacles while trying to achieve the highest score possible.

The game is set in recognizable campus locations — the Technology Center, the Cosmopolita cafeteria, the Planetarium, and others — giving it a local, nostalgic feel alongside classic 8-bit visuals and sounds.

---

## Gameplay

- **Objective:** jump over obstacles for as long as possible to maximize your score.
- **Jump:** press the `↑` arrow key. The jump simulates gravity — the character rises to a fixed height, then falls at double the upward speed.
- **Lives:** collect coffee cups (max 3) displayed in the top-left corner. Each collision with a virus costs one coffee. Running out turns the character into a visibly sick sprite; one more collision ends the game.
- **Restart:** press `Enter` after game over to reset the score and replay.
- **Score:** displayed in the top-right corner alongside `HS` (high score for the current session). Game speed increases as the player progresses.

---

## Technical Overview

- **Language:** C
- **Graphics/Audio:** [Allegro](https://liballeg.org/) library
- **Rendering logic:** background and obstacle bitmaps scroll left at increasing speed to simulate movement; the player sprite stays fixed on the x-axis.
- **IDE:** Code::Blocks (project file: `ASO.cbp`)

### Repository Structure

```
.
├── fonte/      # Source files
├── imagens/    # Sprite and background assets
├── sons/       # 8-bit sound effects
├── bin/        # Compiled binary output
├── obj/        # Object files
├── main.c      # Main game logic
└── ASO.cbp     # Code::Blocks project file
```

---

## Requirements

- GCC or any C99-compatible compiler
- [Allegro 5](https://liballeg.org/download.html)

---

## Build & Run

```bash
# Clone the repository
git clone https://github.com/andrwbolsm/A_Scooter_Odissey.git
cd A_Scooter_Odissey

# Open in Code::Blocks and build, or compile manually:
gcc main.c fonte/*.c -o Game $(allegro-config --libs) -lm

# Run
./Game
```

---

> Developed at UFSM — Aerospace Engineering, Algorithms and Programming course.

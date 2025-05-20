🕹️ Isolation Game

Welcome to Grid Tactics, a strategic 2-player board game where your objective is to block your opponent by outmaneuvering them on a customizable grid.
📦 How to Start the Game
1. Download and Extract

Download the folder containing the following files:

    main.c

    board.o

    board.h

Once downloaded, extract the folder to a location of your choice.
2. Compile the Game

Open a terminal in the extracted folder and compile the game using the following command:

gcc -Wall main.c board.o

3. Launch the Game

Run the compiled output with:

./a.out

🎮 Game Rules
🔧 Game Options

Before starting, choose from the following options to customize your game:
🧱 Grid Type

    Normal: Standard rectangular grid.

    Hexagonal: Beehive-shaped grid layout.

⚔️ Combat Rule

    With Rule: You can only attack cells within a 3-cell range from your position.

    Without Rule: No limit on attack range.

You can combine these options to create unique and challenging game modes.
🛠 Preparation

Before your first game:

    Choose the grid type and combat rule settings.

    Define the player names.

    ⚠️ This is a 2-player only game.

🏆 Objective

Your goal is to block your opponent so that they can no longer move. The game is played in turns.
Each Turn

    Move your piece one cell in any direction (as long as it's within the board and not a dead cell).

    Kill a Cell: Choose one unoccupied and alive cell to "kill" (remove from the board permanently).

Use your movement and cell elimination wisely to trap your opponent!
⛔ Game End

The game ends when one player can no longer move. The other player is declared the winner.
📝 Notes

    All moves and actions are taken one per turn.

    Strategy and planning are key to victory.

    Dead cells remain unusable for the entire game.

Let me know if you’d like this turned into a downloadable README.md file or want it enhanced with images, examples, or code snippets!

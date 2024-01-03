# RAIInet - The Strategy Game

RAIInet is a two-player strategy game where players assume the roles of computer hackers, controlling a set of links which are either viruses or data. The objective is to either download four pieces of data or make the opponent download four viruses.

## Table of Contents
- [Installation](#installation)
- [Gameplay](#gameplay)
- [Features](#features)
- [Screenshots](#screenshots)
- [How to Play](#how-to-play)
- [Commands](#commands)
- [Command Line Arguments](#command-line-arguments)
- [License](#license)

## Installation

To install the game, follow these steps:

```bash
git clone https://github.com/yourgithubusername/RAIInet.git
cd RAIInet
# Follow platform-specific instructions to compile and run the game
```

## Gameplay

RAIInet is played on an 8x8 board, with each player starting with 8 links - a mix of viruses and data. Players take turns to move their links and use special abilities, aiming to either download data or make their opponent download viruses. The game ends when a player achieves one of these objectives.

## Features

- **Turn-Based Strategy**: Engage in a strategic battle of wits with turn-based gameplay.
- **Graphical & Text-Based UI**: Play the game with a sleek graphical interface or a classic text-based view.
- **Multiple Abilities**: Utilize various abilities like Firewall, Download, and Polarize to gain an edge.
- **Extensible Design**: Easily add new abilities and features to the game.

## Screenshots

<img src="https://raw.githubusercontent.com/daniel-su1/RAIInet/master/screenshots/1.png" alt="RAIInet Gameplay Screenshot 1" width="400"> <img src="https://raw.githubusercontent.com/daniel-su1/RAIInet/master/screenshots/2.png" alt="RAIInet Gameplay Screenshot 2" width="400">


## How to Play

RAIInet is a strategy game that involves careful planning, strategic movement, and the use of special abilities. The game is played on an 8x8 grid, resembling a chessboard, with two players each controlling eight links. Here's a detailed guide on how to play the game:

### Setup

1. **Board Setup**: The game board is an 8x8 grid with the middle two squares on the first and last row designated as server ports.
2. **Choosing Links**: Each player starts with 8 links - a mix of viruses and data, each having a strength between 1 and 4. Arrange your links on the first and last row of the board, avoiding placing them on the server ports.
3. **Selecting Abilities**: Each player chooses five abilities from options like Link Boost, Firewall, Download, Scan, Polarize, Wall, and Backup. These abilities can be used strategically during the game.

### Game Turn

The game proceeds in turns, with each player taking one turn at a time.

1. **Move a Link**: On your turn, move one of your links one space in a cardinal direction (north, south, east, or west). You cannot move a link onto one of your own links or server ports.
2. **Battle**: If you move your link onto a space occupied by an opponent's link, a battle ensues. The link with the higher strength wins, and the loser's link is downloaded by the winner. In a tie, the attacking player wins.
3. **Download**: Moving a link off the opponent's side of the board or into their server ports results in downloading that link.
4. **Use an Ability**: You may use one of your abilities per turn, either before or after moving a link. Abilities can change the game state significantly, like revealing link types or changing a link's allegiance.

### Abilities Explained

Each ability adds a unique strategic element to the game. Here’s a breakdown:

#### Link Boost
- **Effect**: Enhances a link's mobility for one turn.
- **Usage**: Activate before moving a link.
- **Strategic Tip**: Ideal for quick positioning.

#### Firewall
- **Effect**: Targets a square to reveal and potentially download opponent viruses.
- **Usage**: Place strategically on the board.
- **Strategic Tip**: Use to guard key areas.

#### Download
- **Effect**: Instantly downloads an opponent’s link.
- **Usage**: Select an opponent's link.
- **Strategic Tip**: Target high-strength data links.

#### Polarize
- **Effect**: Changes a link's type (data to virus or vice versa).
- **Usage**: Activate on a revealed link.
- **Strategic Tip**: Useful for deception or conversion.

#### Scan
- **Effect**: Reveals the type and strength of a link.
- **Usage**: Target an unrevealed link.
- **Strategic Tip**: Gain intelligence for strategy.

#### Wall (Additional Ability)
- **Effect**: Creates an impassable square.
- **Usage**: Activate to block paths or protect positions.
- **Strategic Tip**: Funnel opponent movements or create safe zones.

#### Backup (Additional Ability)
- **Effect**: Reverses a link's last move.
- **Usage**: Activate after a link moves.
- **Strategic Tip**: Correct mistakes or tactically retreat.

### Winning the Game

The game ends when either:
- A player successfully downloads four data links, winning the game.
- A player is forced to download four virus links, resulting in their loss.

### Strategic Elements

- **Link Types**: Keep in mind the types of links (virus or data) you're moving. Misleading your opponent can be a key strategy.
- **Abilities**: Use abilities wisely. They are limited and can turn the tide of the game.
- **Positioning**: Be strategic about the positioning of your links, especially when it comes to protecting your server ports and planning attacks.

## Commands

Players can interact with the game using the following command line commands:

- `move <link> <direction>`: Moves the specified link in the given direction (`up`, `down`, `left`, `right`).
- `abilities`: Displays the ability cards available to the player.
- `ability <N>`: Uses the ability card with ID N. May require additional information like a target or a board square.
- `board`: Displays the current state of the board.
- `sequence <file>`: Executes a sequence of commands from a specified file.
- `quit`: Exits the game.

## Command Line Arguments

When launching RAIInet, you can customize your game setup using various command line arguments. Here’s a guide to using these options:

- **`-ability1 <order>`**: Specifies the abilities for player 1. This is a list of the 5 abilities player 1 will use, given by a string consisting of the first letter of each ability. For example, `-ability1 LFDSP` for Link boost, Firewall, Download, Scan, Polarize in that order.

- **`-ability2 <order>`**: Similar to `-ability1`, but for player 2.

- **`-link1 <placement-file>`**: Specifies the placement of links for player 1. The contents of `<placement-file>` should list what each link should be for player 1, in order from `a` to `h`. For example, a file containing `V1 D4 V3 V2 D3 V4 D2 D1` sets up the links in the specified order.

- **`-link2 <placement-file>`**: As above, but for player 2.

- **`-graphics`**: Enables the graphical interface for the game. If this option is not specified, the game defaults to a text-based interface.
-  **`-enablebonus`**: Enables bonus features.

Example usage:
```bash
./RAIInet -ability1 LFDSP -ability2 DSPLF -link1 player1.txt -link2 player2.txt -graphics
```
This command launches the game with specified abilities and link placements for both players and enables the graphical interface.


## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

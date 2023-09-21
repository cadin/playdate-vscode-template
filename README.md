# Playdate VS Code Template (Mac)
Build and run projects in the Playdate simulator with a key shortcut.

## Requirements
- [VS Code](https://code.visualstudio.com)
- [Node](https://nodejs.org/)
- [Playdate SDK](https://play.date/dev/)

## Get Started
**This is a template repo.**  
You can generate your own separate repositories from this template with the same directory structure, branches, and files. Click "Use this template" to create your own repo.

1. Clone or download the repo.
2. In VS Code, choose Run > Run Without Debugging to launch the project in the Playdate simulator.
3. Assign a keyboard shortcut to the Run Without Debugging option to build and run with a keypress.
4. To use autocomplete/intellisense, add `PLAYDATE_SDK_PATH` to your `.bashrc`/`.zshrc` or equivalent, and source it; check it with: `env | grep -i playdate`

## Output
Build files get output to `bin/Output.pdx`.  
Change this by editing the `playdate.output` property in `.vscode/settings.json`.

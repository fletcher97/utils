################################################################################
# ZSHRC
################################################################################

# OH-MY-ZSH Plugins
plugins=(alias-finder common-aliases git git-flow z)
ZSH_ALIAS_FINDER_AUTOMATIC=true

# Add personal bin folder to path
path+=('/home/fletcher/bin')

# Setting default editor to nano
EDITOR=nano

# Disable Bell
unsetopt BEEP
set bell-style none

# Norminette aliases (create link in bin)
alias norm="norminette"

# Compiler aliases
alias gw="gcc -Wall -Werror -Wextra"
alias gws="gw -fsanitize=address"

# Utility aliases
alias cls="clear"
LESS="-FRXx4"
unalias rm
unalias mv
unalias help
unalias run-help

# Valgrind aliases
alias vg="valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all \
-v"
alias vgf="vg --log-file=vg_out.txt"

# VSC: Use insider
alias code=code-insiders

# Visual Studio Code Alias
alias vsc="code --extensions-dir ~/.vscode-insiders/extensions/common"
alias vsc-c="code --extensions-dir ~/.vscode-insiders/extensions/C"
alias vsc-cpp="code --extensions-dir ~/.vscode-insiders/extensions/Cpp"
alias cpp=vsc-cpp
alias vsc-py="code --extensions-dir ~/.vscode-insiders/extensions/Py"
alias vsc-rust="code --extensions-dir ~/.vscode-insiders/extensions/Rust"
alias vsc-go="code --extensions-dir ~/.vscode-insiders/extensions/Go"
alias vsc-bb="code --extensions-dir ~/.vscode-insiders/extensions/bitburner"
alias vsc-ansible="code --extensions-dir ~/.vscode-insiders/extensions/ansible"

# Set tabs
tabs 4

# VPN
alias 42lisboa-vpn="sudo cp /home/fletcher/.vpn/resolv-lx.conf /etc/resolv.conf && sudo openvpn --config ~/.vpn/42lisboa/42lisboa.ovpn"
alias 42porto-vpn="sudo cp /home/fletcher/.vpn/resolv-lx.conf /etc/resolv.conf && sudo openvpn --config ~/.vpn/42porto/42porto.ovpn"
alias 42bcn-vpn="sudo cp /home/fletcher/.vpn/resolv-bcn.conf /etc/resolv.conf && sudo openvpn --config ~/.vpn/42bcn/42bcn.ovpn"

# Docker
alias dc=docker-compose
alias dkill="docker system prune -a; docker stop \$(docker ps -a -q); docker rm \$(docker ps -a -q); docker rmi \$(docker images -a -q)"
alias dropi-cli="docker attach --detach-keys="ctrl-d" dropi-cli"

# Python
export PYTHONDONTWRITEBYTECODE=1
alias pysrc='source venv/bin/activate'

#export TERM=xterm-256color

# GPG export to fix git error
export GPG_TTY=$(tty)

# TODO manager
export TASKRC=~/.config/task/taskrc
alias tt=taskwarrior-tui

<p align="center">
    <a href="https://unitfactory.net/en/" target="_blank">
        <img src="https://github.com/viacheslavpleshkov/unit-factory-ucode/blob/master/.git_images/unit_logo.png?raw=true" height="100px">
    </a>
    <a href="https://ucode.world/en/" target="_blank">
        <img src="https://github.com/viacheslavpleshkov/unit-factory-ucode/blob/master/.git_images/ucode_logo.png?raw=true" height="100px">
    </a>
    <h1 align="center">unit-factory-ucode-uls</h1>
    <br>
</p>
<p align="center">⚙️ Implementation of shell zsh. iTerm taken as an example of a terminal.</p>

## Got skills

Critical Thinking, Problem Solving, Analysis, Reasoning & Argumentation, Creativity, Agility & Adaptability, Responsibility, Self-Management,  Communication, Teamwork, UNIX, Git, Algorithms, C, Procedural Programming, Leadership

<hr>

## Building the program

1. Download/Clone the source code
2. `cd` into the root directory
3. Run `make`

## Description

1. The default prompt looks like u$h> followed by the space character.
2. The shell deals only with one line user input. In other cases, appropriate
descriptive error message is displayed.
3. The shell implements builtin commands without flags: export, unset, fg, exit . 
4. The shell also implements the following builtin commands with flags:
- env with -i, -P, -u;
- cd with -s, -P and - argument; 
- pwd with -L, -P;
- which with -a, -s;
- echo with -n, -e, -E;
5. The shell calls the builtin command instead of binary program if there is the name match between them.
6. The shell correctly manages errors like other shells do.
7. The shell manages user environment correctly.
8. The shell runs programs located in the directories listed in the PATH variable.
9. The shell manages signals CTRL+D , CTRL+C and CTRL+Z .
10. The shell implements command separator ; .
11. These characters are escaped to be used literally: space , ' , " , $ , ( , ) , \,`,{,}.
12. The shell manages these expansions correctly:
- tilde expansion ~ with the following tilde-prefixes: ~ , ~/dir_name , ~username/dir_name , ~+/dir_name , ~-/dir_name ;
- the basic form of parameter expansion ${parameter} ;
- command substitution `command` and $(command) .

## Author
1. <a href="https://github.com/viacheslavpleshkov" target="_blank">Viacheslav Pleshkov</a>
1. <a href="https://github.com/arni30" target="_blank">Oleksandr Arnopolin</a>
1. <a href="https://github.com/NastiaSvyryda" target="_blank">Anastasiia Svyryda</a>


## License

Collision is an open-sourced software licensed under the [MIT license](LICENSE.md).
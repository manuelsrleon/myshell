 # Práctica SO 2023-2024
### P0 - Intro to C Language
- [ ] Basic command processing structure
- [X] autores
    - [X] -l
    - [X] -n
    - [X] -l -n
    - [ ] TODO fix : Success when using perror("Comando no reconocido");
- [ ] pid
- [ ] chdir
- [ ] date
- [ ] time
- [ ] comand
- [ ] open
- [ ] close
- [ ] dup
- [ ] listopen
- [ ] infosys
- [ ] help
- [X] quit
- [X] exit
- [X] bye

### P1 - Filesystems
- [ ] Histórico de comandos implementado para la p1
- [X] create
    - [ ] Check file permissions
        - File permissions are different, however, I'm not quite sure why that's the case.
    - [ ] Check error handling
        - At least for directories, it does handle errors beautifully.
- [ ] stat
    - [X] -long: Listado largo
    - [ ] -acc: accesstime
    - [ ] -link: Si es enlace simbólico, el path contenido
        lista múltiples
    - [X] 0args
- [X] list
    - [X] hid
    - -recb
    - -reca
    - parámetros que se pasan directamente a stat
    - [X] Testear directorio en un directorio diferente al directorio actual, después hacer recursividad. 
        - Directorio como argumento.
- [ ] delete
- [ ] deltree

## testing

# p0
- [X] authors Prints the names and logins of the program authors. authors -l prints
only the logins and authors -n prints only the names
- [X] pid Prints the pid of the process executing the shell.
- [X] ppid Prints the pid of the shell’s parent process.
- [X] cd [dir] Changes the current working directory of the shell to dir (using the
chdir system call). When invoked without auguments it prints the

current working directory (using the getcwd system call.
- [X] date [-t|-d] Prints the current date in the format DD/MM/YYYY and the current
time in the format hh:mm:ss.
- [X] date -d Prints the current date in the format DD/MM/YYYY
- [X] date -t Prints and the current time in the format hh:mm:ss.
- [ ] historic [N|-N] Shows the historic of commands executed by this shell. In order to
do this, a list to store all the commands input to the shell must be
implemented.
– historic Prints all the comands that have been input with their
order number
– historic N Repeats command number N (from historic list)
– historic -N Prints only the lastN comands
Students are free to decide whether historic stars numbering commands
at 0 or at 1. Hypothetically, there’s a scenario where trying to repeat
a historic command could yield an infinite loop or a stack overflow
(depending on how it is coded), so students may choose to not store
calls to historic N itself in the historic list if they want so (See the
NOTES ON LIST IMPLEMENTATIONS at the end of this document)
- [ ] open [file] mode Opens a file and adds it (together with the file descriptor and the
opening mode to the list of shell open files. For the mode we’ll use:
- cr for O CREAT, 
- ap for O APPEND, 
- ex for O EXCL, 
- ro for O RDONLY,
rw for O RDWR, wo for O WRONLY and tr for O TRUNC.
Open without arguments lists the shell open files. For each file it lists its
descriptor, the file name and the opening mode. The shell will inherit
from its parent process open descriptors 0, 1 and 2 (stdin, stout, and
stderr). To get the opening mode from a descriptor (df) we can use
fcntl(fd,F GETFL).
- [ ] close [df ] Closes the df file descriptor and eliminates the corresponding item from
the list
- [ ] dup [df ] Duplicates the df file descriptor (using the dup system call, creating the
corresponding new entry on the file list
infosys Prints information on the machine running the shell (as obtained via
the uname system call/library function)
help [cmd] help displays a list of available commands. help cmd gives a brief help
on the usage of comand cmd
- [X] quit Ends the shell
- [X] exit Ends the shell
- [X] bye Ends the shell

# p1

- [X] makefile
    - makefile
    - makefile [name]
- [X] makedir
    - makedir
    - makedir [name]
- [X] listfile
    - [X] listfile
    - [X] listfile -long
    - [X] listfile -link 0.5pomo
    - [X] listfile -acc 0.5pomo
- [X] cwd
- [ ] listdir
    - [X] -hid  {
    - [X] -long
    - [X] -link
    - [X] -acc }1+ pomo
    - [ ] varios
- [ ] reclist
- [ ] revlist
- [X] erase 0.3pomo 
    - [X] TEST: dir vacio
    - [X] TEST: symlink
    - [X] TEST: archivo normal en carpeta
    - [X] TEST: dir con algo -> error
    - [X] TEST: archivo dentro de dir
    - [X] TEST: 0 tokens
    - [X] TEST: varios archivos
- [ ] delrec 1+pomo
    - [ ] TEST: directorio con cosas
    - [ ] TEST: varios directorios
    - [ ] TEST: varios directorios con cosas
# p2 
- [ ] List implementation

- [ ] allocate
    - [X] allocate -malloc -n
    - [-] allocate -mmap file perm
    - [-] allocate -create cl n
    - [-] allocate -shared cl
- [ ] deallocate
    - [X] deallocate -malloc
    - [ ] deallocate -mmap
    - [ ] deallocate -shared cl
    - [ ] deallocate -delkey cl
- [-] read
- [-] write
- [-] memfill addr cont ch
- [-] memdump addr cont
- [X] memory
    - [X] memory -funcs
    - [X] memory -blocks
    - [X] memory -vars
    - [X] memory -all
    - [X] memory -pmap

Con el parámetro `-funcs` imprimimos las direcciones de 3 funciones del programa y 3 funciones de librería. En la shell original vemos que las direcciones están en rangos de direcciones completamente distintos:

```
Variables locales       0x7ffde0c9abcc,    0x7ffde0c9abc8,    0x7ffde0c9abc4
Variables globales      0x562111f862f8,    0x562111f862f0,    0x562111f862f4
Var (N.I.)globales      0x562111f97e68,    0x562111f97e70,    0x562111f97e78
Variables staticas      0x562111f862fc,    0x562111f86300,    0x562111f86304
Var (N.I.)staticas      0x562111fab780,    0x562111fab788,    0x562111fab790
Funciones programa      0x562111f76e97,    0x562111f76c98,    0x562111f76da0
Funciones libreria      0x7f82740606f0,    0x7f827407f380,    0x7f82740a50a0
``` 
        Esto es debido a que cuando el programa se inicializa, las funciones del programa se cargan dentro del espacio de memoria del programa, pero las funciones de librería se cargan en otra región distinta, la asociada a {STACK | HEAP}.
        Lo mismo apreciamos en el caso de las variables: 
        Las variables locales están reservadas en una región cercana a la de la librería, mientras que el resto de variables se reservan en regiones más próximas.
        En el caso de las variables      , están separadas por 8 unidades (8 bits).
        El tamaño de int dependerá del compilador, por lo que podemos hacer sizeof(int) para saber cuánto ocupa en nuestro sistema.
        Haciendo sizeof en mi máquina, vemos que el tamaño asociado es de 4 bytes, lo cual significa que cada variable estará situada en.
        El stack crece hacia abajo (siendo abajo las direcciones bajas), y el heap crece hacia arriba.
        Según GeeksForGeeks, en un programa escrito en C tenemos: 
            1: Segmento de texto: Contiene las instrucciones ejecutables por el programa. Debe emplazarse por debajo del heap o el stack para evitar poder sobreescribirlo mediante overflows.
            2: Segmento de datos inicializados: Se llama a veces "segmento de datos" a secas. Es una porción del espacio de direcciones virtuales del programa, que contiene las variables globales y estáticas inicializadas por el programador. Es por ello que podemos localizar las local
            3: Segmento de datos no inicializados
            4: Heap (montículo)
            5: Stack
        
        Una cosa a observar es que las variables no inicializadas siempre están por encima de sus contrapartes inicializadas. (?)

- [ ] readfile addr cont
- [ ] writefile addr cont
- [ ] read  df addr cont
- [ ] write df addr cont
- [X] recurse n
Salida de la función recurse:
```
parametro:  5(0x7fffa2d294bc) array 0x7fffa2d294c0, arr estatico 0x55a666678280
parametro:  4(0x7fffa2d2928c) array 0x7fffa2d29290, arr estatico 0x55a666678280
parametro:  3(0x7fffa2d2905c) array 0x7fffa2d29060, arr estatico 0x55a666678280
parametro:  2(0x7fffa2d28e2c) array 0x7fffa2d28e30, arr estatico 0x55a666678280
parametro:  1(0x7fffa2d28bfc) array 0x7fffa2d28c00, arr estatico 0x55a666678280
parametro:  0(0x7fffa2d289cc) array 0x7fffa2d289d0, arr estatico 0x55a666678280
```
En la función "recurse" se declaran dos variables. Por un lado, se reserva un array de chars "automático" y un array de chars estático.

La palabra automático es la "storage class" por defecto. Es por eso que raramente se utiliza el nombre. Solamente se pueden acceder desde el scope donde se han declarado. Estas variables van al segmento de datos no inicializados,

Por otra parte, el array de chars estático se inicializa junto a las variables globales. Las variables estáticas tienen la propiedad de que su valor no cambia incluso fuera del scope y fuera de llamadas de funciones, y se guarda en el segmento de datos correspondiente a las variables globales.

En las subsecuentes llamadas recursivas vemos cómo las nuevas llamadas van reservando memoria para las nuevas llamadas, mientras que el array estático permanece en la misma posición.


## memfill y memdump
Las funciones memfill addr cont ch y memdump addr cont trabajan llenando y volcando la memoria. La primera copia en un segmento de memoria que empiece por la dirección addr un caracter ch __cont__ veces. Para llenar la memoria se ha utilizado la función proporcionada en la práctica.

La segunda imprime los contenidos en memoria a partir de la dirección addr, e imprime hasta addr+cont bytes.
Fuentes:
Storage classes en C - GeeksForGeeks
C Program Structure - GeeksForGeeks

# p3
getuid
setuid
environ
fork
hacer fork (syscall) y esperar a que el hijo termine
search () (es nuestro path)
añadirmos y quitamos directorios de nuestra lista.
exec
execpri
fg
fgpri
back ls no ha vuelto el proceso
exec 

centrarse en listas
que funcione ejecutar procesos en bg y fg sin crear nuevo proceso.

17 funciones. Good luck.
- [X] getuid
- [X] setuid [-l] id
- [ ] showvar v1 v2...
- [ ] changevar [-a|-e|-p] var val
- [ ] subsvar [-a|-e] v1 v2 val
- [ ] environ [-environ|-addr]
- [ ] fork
- [ ] search
    - [ ] search -add dir
    - [ ] search -del dir
    - [ ] search clear
    - [ ] path
- [ ] exec progspec
- [ ] execpri prio progspec
- [ ] fg progspec
- [ ] fgpri prio progspec
- [ ] back progspec
- [ ] backpri prio progspec
- [ ] listjobs
- [ ] deljobs -term|-sig
- [ ] ******* (R)

Two lists must be implemented: search and process list

### Process list
    background processes. -> Only processes created with back or backpri
    process entity fields:
        - pid
        - launch timestamp
        - status: [FINISHED, STOPED, SIGNALED, ACTIVE]
        - command line
        - ~~priority~~ (-> obtained at runtime, no need to store)
    
    listjobs and deljobs manipulate the list
    
    Processes in the list are always inserted as active
    waitpid updates the process before printing -- waitpid only reports status changes, not the state itself. Only reports ONCE that a porocess has finished
    pid_t waitpid (pid_t pid, int *wstatus, int options)
    Priority should be obtained at the time of printing, so we don't need to store it
    Background is concurrent execution. Does not wait for its child to finish

### Search list

List of directories where the shell looks for executable files.

This is a simple list of directories where the shell looks for executes.
Execvp searches for exeutables in the list, we're using execve instead because we can pass an alternate environment.

Ejecutable takes care of finding an exec in the search list. Two examples provided

### Progspec:
[VAR1 VAR2 VAR3 ] executablefile arg1 arg2
executablefile is the name of the exec file

### Credentials 
setuid to change user credential. Real and effective credentials will be the same.

setuid rwsr-xr-x (4755)
- execute by another user f
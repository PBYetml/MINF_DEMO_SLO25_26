# MINF - DEMO SLO - 25-26 
démo réaliser dans le cadre du cours de MINF 

-> configuration de base avec Harmony 

- fusible - registres DEVCFG0 à 3 
- utilisation du BSP crée par l'ETML-ES avec importation de ses configurations 
- configuration d'un timer 

-> architecture (fichiers sources et headerfile) crée par harmony 

- main (pas touché) 
- system_task (pas touché) 
- app -> implémentation d'une machine d'état (initialisation - wait - task) 

-> Algorithme 
- faire clignoter une led avec attente passive 
- faire clignoter une led dans la fonction d'interruption d'un timer 
- faire clignoter une led via un callback (lien avec un Timer), permettant de changer l'état d'une machine d'état 

:warning => dans votre projet de MINF lié à un GIT  

> créer manuellement un fichier avec l'extension .gitignore

à l'intérieur de celui-ci vous mettre les infos suivantes

```
#Ignore List for Microchip's MPLAB X IDE
#It's a form of NetBeans with vendor specific changes
#Taken from zeha on GIST https://gist.github.com/zeha/5999375
#Updated by Cristian Cristea (https://github.com/cristiancristea00)

*.d
*.pre
*.p1
*.lst
*.sym
*.obj
*.o
*.sdb
*.obj.dmp
*.mk
*.map
*.properties
*.production
*.debug
nbproject/private/
nbproject/Package-*.bash
build/
nbbuild/
dist/
nbdist/
nbactions.xml
nb-configuration.xml
funclist
nbproject/Makefile-*
disassembly/
.generated_files/
*/.vscode/
*/_build/
*/cmake/
*/out/
```
 
# TaskManagerEmb
Task manager for Upskilling

# Config synchro
Create a backup directory.
Update all the values in the Config.ini configuration file.

## Build & Run
Change the path to your Qt installation in CMakeLists.txt

    mkdir build
    cd build
    cmake ..
    cp ../src/config.ini ./src 
    make
    src/appTaskManagerEmb

Copy the config.ini file to the same directory as the executable file.
## Profilage des performances
Memoire

    valgrind --tool=massif src/appTaskManagerEmb
    sudo massif-visualizer massif.out.<pid>

CPU

    valgrind --tool=callgrind src/appTaskManagerEmb
    sudo kcachegrind callgrind.out.<pid>
=========
Copy the config.ini file to the same directory as the executable file.
>>>>>>>>> Temporary merge branch 2

## Structure
### MainController

>Une façade pour l'application, coordonnant les interactions entre les principaux composants

> Une initialisation complète dans le constructeur, y compris la configuration des connexions entre les "managers" et le chargement initial des tâches.

>Des méthodes publiques pour interagir avec les tâches, qui serviront d'interface pour l'UI qml.

>Des slots pour gérer les événements provenant des différents classes "managers".

>Des méthodes pour l'authentification et la gestion de la sécurité.

>Une méthode de base pour la synchronisation des tâches, qui pourrait être développée davantage dans les phases ultérieures du projet.


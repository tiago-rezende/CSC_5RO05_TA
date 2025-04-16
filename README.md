# CSC_5RO05_TA

Tous les fichiers sont regroupés dans le dossier CSC_5RO05_TA. Les fichiers principaux sont nommés tdnx, où n correspond au numéro du TD et x à la question du TD. Si une question nécessite plusieurs fichiers, ils sont nommés selon le format tdnxy, où y indique la numérotation des fichiers supplémentaires liés à une même question (le premier fichier respecte toujours le format tdnx).

Pour exécuter les programmes, il suffit d’utiliser la commande suivante :
arm-linux-g++ -Wall -Wextra <<FichierPrincipal>> <<FichierComplémentaire1.h>> <<FichierComplémentaire2.cpp>> -o nomFichierCompilé
Ensuite, il faut transférer le fichier compilé vers la Raspberry Pi en utilisant :
rsync -avz nomFichierCompilé root@<<adresse IP>>

Enfin, il suffit de l’exécuter directement sur la Raspberry Pi.
Pour chaque fichier principal, la compilation suit la forme suivante :


# réponse aux questions


2 c : Les méthodes qui ne modifient pas l'état de l'objet, comme `getSample()`, peuvent être déclarées `const`. Les variables `dostop` et `iLoop` doivent être déclarées `volatile` pour garantir un accès correct lors des interruptions asynchrones, comme les signaux. Cela empêche les optimisations du compilateur qui pourraient ignorer les modifications externes. Sans `volatile`, la boucle pourrait mal se comporter si les variables sont modifiées par un signal pendant son exécution. 

![image](https://github.com/user-attachments/assets/ae80bc56-3cb2-467f-b649-bb5c39627fa1)

3a1 : ordre de grandeur = 10⁷

3a2 : 10⁸ — Le temps est plus grand car des tâches différentes peuvent prendre une valeur qui est déjà correcte et la mettre à jour alors qu’il ne le fallait pas, ce qui entraîne un nombre plus élevé.

3a3 : 10⁶ — Ça arrive car le mutex empêche que la donnée soit mise à jour plusieurs fois par cycle. Cependant, le chiffre est plus petit car il y a probablement des problèmes d'accès à la valeur par les tâches, notamment si elle est bloquée par une tâche qui ne va pas la mettre à jour.


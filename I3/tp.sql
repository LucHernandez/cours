/*
##############
# Exercice 4 #
##############

On commence par chercher le nombre total de places pour tous les circuits différents:

SELECT numC, SUM(nbPlaces)
FROM LesProgrammations
GROUP BY (numC)

On obtient
numC        nbPlacesTot
1           100
2           177
3            70
4           128
5           112
6            78
7           149
8           135
9            34
10          177
11           62
12          190
13          392
14           37
15           29
16           32
17           52
18          157
19          136
20          150
21          180

On peut ensuite simplement récupérer les numéros de circuits et leurs prix de base dans LesCircuits:

SELECT numC, prix
FROM LesCircuits

On obtient
numC  prix
1     1160
2     1160
3     1040
4     1270
5     2740
6     2520
7     2500
8     2140
9     5700
10    6170
11    6270
12    6170
13   18590
14    7700
15    8560
16   10180
17    3990
18    6690
19   10400
21   15000

Il suffit ensuite de faire une jointure sur numC pour obtenir la table désirée

##############
# Exercice 5 #
##############
On commence par chercher le nombre de fois que chaque ville est visitée :
WITH villes AS (
	SELECT vEtape AS nomV, COUNT(numC) AS apparitionsCounter
	FROM LesEtapes
	GROUP BY vEtape
)

On obtient donc le nom de chaque ville et le nombre de fois qu'elles sont visitées.

On décide ensuite d'associer chaqune de ces villes avec le pays dans le quel elles sont situées avec un simple JOIN :
VcountPerP AS (
	SELECT pays, nomV, apparitionsCounter
	FROM LesVilles JOIN villes USING (nomV)
)

On décide enfin de récupérer le max de fois visitées dans chacuns des groupes pays:
maxPerP AS (
	SELECT pays, MAX(apparitionsCounter AS maxi
	FROM VcountPerP
	GROUP BY pays
)

Pour ensuite associer la/les ville ayant été visitées ce nombre maximum de fois:
SELECT V.pays, V.nomV
FROM maxPerP M JOIN VcountPerP V ON (M.maxi = V.apparitionsCounter AND M.pays = V.pays)
ORDER BY V.pays
;
*/

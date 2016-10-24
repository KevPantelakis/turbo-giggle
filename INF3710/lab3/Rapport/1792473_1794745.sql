--Richer Archambault - 1792473
--Kevin Pantelakis   - 1794745


--------------- SCHÉMA RELATIONNEL--------------

-- Vider les tables si elle sont deja crées
DROP TABLE Note;
DROP TABLE Epreuve;
DROP TABLE Inscription;
DROP TABLE Section;
DROP TABLE CoursTrim;
DROP TABLE Prerequis;
DROP TABLE Cours;
DROP TABLE Personne;

CREATE TABLE Personne
(
  nas INTEGER CHECK(nas BETWEEN 000000000 and 999999999) PRIMARY KEY,
  nom VARCHAR(255) NOT NULL,
  prenom VARCHAR(255) NOT NULL,
  typPers CHAR(1) NOT NULL CHECK(typPers IN ('E','X','P')),
  matricule VARCHAR(20) UNIQUE,
  pmatricule  VARCHAR(20) UNIQUE
);

CREATE TABLE Cours(
  sigle VARCHAR(15) primary key,
  titre VARCHAR(50) NOT NULL,
  nbCredits INTEGER NOT NULL
);

CREATE TABLE Prerequis(
  sigle VARCHAR(15),
  lePrerequis VARCHAR(15),
  PRIMARY KEY (sigle,lePrerequis),
  FOREIGN KEY (lePrerequis) REFERENCES Cours(sigle),
  FOREIGN KEY (sigle) REFERENCES Cours(sigle)
);

CREATE TABLE CoursTrim(
  sigle VARCHAR(15),
  trim VARCHAR(5),
  responsable INTEGER,
  PRIMARY KEY (sigle,trim),
  FOREIGN KEY (sigle) REFERENCES Cours(sigle),
  FOREIGN KEY (responsable) REFERENCES Personne(nas)
);

CREATE TABLE Section(
  sigle VARCHAR(15),
  trim VARCHAR(5),
  numSect INTEGER,
  capacite INTEGER NOT NULL,
  enseignant INTEGER,
  PRIMARY KEY (sigle,trim,numSect),
  FOREIGN KEY (sigle,trim) REFERENCES CoursTrim(sigle,trim),
  FOREIGN KEY (enseignant) REFERENCES Personne(nas)
);


CREATE TABLE Inscription(
  sigle VARCHAR(15),
  trim VARCHAR(5),
  matricule VARCHAR(20),
  numSect INTEGER,
  cumulatif REAL CHECK(cumulatif BETWEEN 0 AND 20),
  noteFinale VARCHAR(3),
  PRIMARY KEY (sigle,trim,matricule),
  FOREIGN KEY (matricule) REFERENCES Personne(matricule),
  FOREIGN KEY (sigle,trim,numSect) REFERENCES Section(sigle,trim,numSect)
);

CREATE TABLE Epreuve(
  idEpr INTEGER PRIMARY KEY,
  sigle VARCHAR(15),
  trim VARCHAR(5),
  typEpr CHAR(2) CHECK(typEpr IN ('CP','EF','TP')),
  ponderation INTEGER CHECK(ponderation BETWEEN 0 and 100),
  FOREIGN KEY (sigle,trim) REFERENCES CoursTrim(sigle,trim)
);

CREATE TABLE Note(
  idEpr INTEGER,
  matricule VARCHAR(20),
  laNote REAL CHECK(laNote BETWEEN 0 AND 20),
  PRIMARY KEY (idEpr, matricule),
  FOREIGN KEY (idEpr) REFERENCES Epreuve(idEpr),
  FOREIGN KEY (matricule) REFERENCES Personne(matricule)
);
--------------- Algebre relationnel-----------
/*
1: Afficher les cours d’au moins 3 crédits obtenus par l’étudiant Félix Allard.

Personne   		 Inscription
   \     			      /
    \	       	     /
 nom='allard'     /
 prenom='Félix'  /
       \        /
   Jointure(matricule)
		    \
	  	   \	      Cours
	  	    \	  	   /
	  	     \	    /
	  	      \  	 /
		   Jointure(Sigle)
		        |
		        |
		        |
		        |
		Projection(sigle,titre)
  		      |
		        |

-----------------------------------------------------------------------------------
2: Afficher les prérequis qui manquent à l’étudiant Félix Allard pour s’inscrire au cours INF3303.

		                          PREREQUIS
		                             /
Personne   		 Inscription      /
   \     			      /        (sigle='INF3303')
    \	       	     /          /
 nom='allard'     /          /
 prenom='Félix'  /          /
       \        /      Projection(lePrerequis)
   Jointure(matricule)    /
		       \             /
		        \           /
		Projection(sigle)  /
		          \       /
		           \     /
		            \   /
		            MINUS
		              |
		              |
		              |

-----------------------------------------------------------------------------------
3: Afficher les étudiants inscrits en automne 2016 mais qui n’ont encore obtenu aucun cours de 3 crédits (ou plus).

 Personne     Inscription
    \           /
     \    (trim='16-3')
      \       /
       \     /               Personne    Inscription   Cours
        \   /                   |             \         /
    jointure(matricule)         |              \       /
          |                     |            jointure(sigle)
          |                     |               /
          |                     |              /
 projection(nom,prenom)         |             /
          \                  jointure(matricule)
           \                    /
            \                  /
             \    projection(nom,prenom)
              \        /
               |      /
               |     /
               |    /
               |   /
              MINUS
                |
                |
                |

--------------------------------------------------------------
8:

9:

*/
--------------- Requètes SQL------------------


--1: Afficher les cours d’au moins 3 crédits obtenus par l’étudiant Félix Allard.
SELECT sigle,titre FROM COURS C
WHERE C.sigle IN
      (
        SELECT sigle FROM INSCRIPTION I
        WHERE I.matricule =
              (
                SELECT P.matricule FROM PERSONNE P
                WHERE P.nom ='Allard' AND P.prenom = 'Félix'
              )
      ) AND C.NBCREDITS >=3;

--2: Afficher les prérequis qui manquent à l’étudiant Félix Allard pour s’inscrire au cours INF3303.
SELECT LEPREREQUIS FROM PREREQUIS P WHERE P.SIGLE = 'INF3303'
MINUS (SELECT sigle FROM INSCRIPTION I
WHERE I.matricule =
      (
        SELECT P.matricule FROM PERSONNE P
        WHERE P.nom ='Allard' AND P.prenom = 'Félix'
      ));


--3: Afficher les étudiants inscrits en automne 2016 mais qui n’ont encore obtenu aucun cours de 3 crédits (ou plus).
SELECT nom,prenom FROM PERSONNE P
WHERE P.MATRICULE IN
      (
        SELECT matricule FROM INSCRIPTION I
        WHERE I.trim = '16-3'
      ) MINUS
(
  SELECT nom,prenom FROM PERSONNE P
  WHERE P.MATRICULE IN
        (
          SELECT matricule FROM INSCRIPTION I
          WHERE sigle IN
                (
                  SELECT sigle FROM COURS C
                  WHERE C.NBCREDITS >=3
                )
        )
);

--4: Afficher les étudiants qui ont déjà obtenu au moins 10 crédits de cours.
SELECT * FROM PERSONNE
WHERE MATRICULE IN (
  SELECT MATRICULE FROM (
    SELECT MATRICULE, SOMME FROM (
      SELECT MATRICULE,SUM(NBCREDITS) AS SOMME FROM (
        SELECT * FROM COURS INNER JOIN INSCRIPTION ON COURS.SIGLE = INSCRIPTION.SIGLE
      ) GROUP BY MATRICULE
    ) WHERE SOMME >= 10
  )
);


--5:  Afficher pour chaque épreuve du cours CIV2310 : son type, son identifiant, ainsi que la note minimum, moyenne et maximum des étudiants, en hiver 2016.
SELECT TYPEPR,IDEPR,MAX(LANOTE), MIN(LANOTE), AVG(LANOTE) FROM
  (
    SELECT N.IDEPR,sigle,trim,lanote,TYPEPR FROM NOTE N
      JOIN EPREUVE E on(N.IDEPR = E.IDEPR)
  ) WHERE sigle='CIV2310' and TRIM = '16-1'
GROUP BY (TYPEPR,IDEPR);


--6: Afficher le cours auquel est inscrit en automne 2016 le plus grand nombre d’étudiants.
SELECT TYPEPR,IDEPR,MAX(LANOTE), MIN(LANOTE), AVG(LANOTE) FROM
  (
    SELECT N.IDEPR,sigle,trim,lanote,TYPEPR FROM NOTE N
      JOIN EPREUVE E on(N.IDEPR = E.IDEPR)
  ) WHERE sigle='CIV2310' and TRIM = '16-1'
GROUP BY (TYPEPR,IDEPR);


--7: Afficher les cours donnés en hiver 2016 dans lesquels au moins 10 étudiants ont obtenu une note de 12 ou plus dans au moins 3 épreuves notées.

--8: Afficher les étudiants qui ont repassé un cours et qui ont augmenté leur note (cumulatif) la deuxième fois. Afficher le sigle du cours, le prénom et le nom de l’étudiant, les deux sessions et les deux notes).

--9: Afficher les étudiants qui ont acquis tous les prérequis du cours INF3303

--10: Afficher les étudiants qui ont interrompu, puis repris leurs études : ils n’ont pas été inscrits consécutivement à toutes les sessions (d’automne et hiver).

----------------------------------------------TRIGGER_A-----------------------------------------------------

DROP TRIGGER bf_up_ct_TRIGGER_A;

CREATE OR REPLACE TRIGGER bf_up_ct_TRIGGER_A
  BEFORE UPDATE OR INSERT ON COURSTRIM
  FOR EACH ROW
  DECLARE
    typpersonne CHAR(1);
  BEGIN
    SELECT P.TYPPERS INTO typpersonne FROM PERSONNE P WHERE P.NAS = :NEW.RESPONSABLE;
    IF(typpersonne <> 'P') THEN
      RAISE_APPLICATION_ERROR(-20100,'On ne peut pas être responsable de cours sans être professeur.');
    END IF;
  END;

----------------------------------------TEST TRIGGER A------------------------------------------------------
UPDATE  COURSTRIM
SET RESPONSABLE = 658414972
WHERE SIGLE='CP510'
      AND TRIM = '19-3';

DELETE FROM COURSTRIM WHERE SIGLE = 'CP510' AND TRIM = '19-3';


INSERT INTO CoursTrim (sigle, trim, responsable) VALUES ('CP510', '19-3', 658414972);

INSERT INTO CoursTrim (sigle, trim, responsable) VALUES ('CP510', '19-3', 300456273);
DELETE FROM COURSTRIM CT WHERE CT.SIGLE = 'CP510' AND CT.TRIM = '19-3' AND CT.RESPONSABLE = 300456273;
COMMIT;
------------------------------------------------------------------------------------------------------------


-----------------------------------------------TRIGGER_B----------------------------------------------------

DROP TRIGGER bf_up_ins_TRIGGER_B;
CREATE OR REPLACE TRIGGER  bf_up_ins_TRIGGER_B
  BEFORE UPDATE OR INSERT ON PERSONNE
  FOR EACH ROW
  DECLARE
    mat VARCHAR(7);
    pmat VARCHAR(7);
    typpersonne CHAR(1);
  BEGIN
    typpersonne:= :NEW.TYPPERS;
    mat := :NEW.MATRICULE;
    pmat:= :NEW.PMATRICULE;

    IF (typpersonne = 'P' OR typpersonne = 'X') THEN -- PROFESSEUR OU EMPLOYÉ
      IF (mat IS NOT NULL) THEN
        RAISE_APPLICATION_ERROR(-20000,'Un professeur/employé ne peut pas avoir un matricule étudiant');
      END IF;
      IF (pmat IS NULL) THEN
        RAISE_APPLICATION_ERROR(-20001,'Un professeur/employé doit avoir un pmatricule');
      END IF;
      IF NOT REGEXP_LIKE (pmat,'^p\d{3,6}$') THEN
        RAISE_APPLICATION_ERROR(-20002,'Format tu pmatricule incorrecte, il doit être composé du caractère p  suivi de 3 à 6 chiffres.');
      END IF;
    ELSE -- ÉTUDIANT
      IF (pmat IS NOT NULL) THEN
        RAISE_APPLICATION_ERROR(-20003,'Un étudiant ne doit pas posséder un pmatricule');
      END IF;
      IF (mat IS NULL) THEN
        RAISE_APPLICATION_ERROR(-20004,'Un étudiant doit posséder un matricule');
      END IF;
      IF NOT REGEXP_LIKE (mat,'^\d{3,7}$') THEN
        RAISE_APPLICATION_ERROR(-20005,'Format du matricule incorrecte, il doit etre composé de 3 à 7 chiffres.');
      END IF;
    END IF ;
  END;
--------------------------------------------------------------------------------------------------------------------------------------


-----------------------------------------------TRIGGER_C------------------------------------------------------------------------------
DROP TRIGGER bf_up_ins_up_TRIGGER_C;
CREATE OR REPLACE TRIGGER bf_ins_up_TRIGGER_C
  BEFORE UPDATE OR INSERT ON INSCRIPTION
  FOR EACH ROW
  DECLARE
    maxCapacity NUMBER;
    curCapacity INTEGER;
  BEGIN
    SELECT S.CAPACITE INTO maxCapacity FROM SECTION S WHERE S.SIGLE = :NEW.SIGLE AND S.NUMSECT = :NEW.NUMSECT AND S.TRIM = :NEW.TRIM;
    SELECT COUNT(*) INTO curCapacity FROM INSCRIPTION I WHERE I.TRIM = :NEW.TRIM AND I.SIGLE = :NEW.SIGLE;
    IF (curCapacity >= maxCapacity ) THEN
      raise_application_error(-20009,'Section Pleine');
    END IF;
  END;
--------------------------------------------------------------------------------------------------------------------------------------





/*
----------------------------------------TEST TRIGGER B--------------------------------------------------------------------------------
--Pmatricule et matrcule à NULL
INSERT INTO Personne (nas, nom, prenom, typPers, matricule, pmatricule) VALUES (239075522, 'Lavoie', 'Thierry', 'P', NULL , NULL);

--Pmatricule et matricule valide pour le type P ou X
INSERT INTO Personne (nas, nom, prenom, typPers, matricule, pmatricule) VALUES (239075522, 'Lavoie', 'Thierry', 'X', 5454, 'p5454');

-- Un Professeur avec un matricule
INSERT INTO Personne (nas, nom, prenom, typPers, matricule, pmatricule) VALUES (239075522, 'Lavoie', 'Thierry', 'P', 7654 , NULL);

-- Professeur avec pmatricule pas valide
INSERT INTO Personne (nas, nom, prenom, typPers, matricule, pmatricule) VALUES (239075522, 'Lavoie', 'Thierry', 'P', NULL, '54p5454');

-- Professeur avec pmatricule valide
INSERT INTO Personne (nas, nom, prenom, typPers, matricule, pmatricule) VALUES (239075522, 'Lavoie', 'Thierry', 'P', NULL, 'p5454');

DELETE FROM PERSONNE WHERE NAS = 239075522;


-- Étudiant avec aucun matricule et aucun ppmatricule
INSERT INTO Personne (nas, nom, prenom, typPers, matricule, pmatricule) VALUES (666666644, 'Lavoie', 'Thierry', 'E', NULL, NULL);

-- Étudiant avec pmatricule sans matricule
INSERT INTO Personne (nas, nom, prenom, typPers, matricule, pmatricule) VALUES (666666644, 'Lavoie', 'Thierry', 'E', NULL, 'p9672');

-- Étudiant avec matricule et pmatricule
INSERT INTO Personne (nas, nom, prenom, typPers, matricule, pmatricule) VALUES (666666644, 'Lavoie', 'Thierry', 'E', 5541, 'p9898');

-- Étudiant avec matricule non valide
INSERT INTO Personne (nas, nom, prenom, typPers, matricule, pmatricule) VALUES (666666644, 'Lavoie', 'Thierry', 'E', 51, NULL);

-- Étudiant avec matricule valide
INSERT INTO Personne (nas, nom, prenom, typPers, matricule, pmatricule) VALUES (666666644, 'Lavoie', 'Thierry', 'E', 5541, NULL);
DELETE FROM PERSONNE WHERE NAS = 666666644;



-------------------------------------------TEST_TRIGGER_C----------------------------------------------------
INSERT INTO INSCRIPTION (sigle, trim, matricule, numSect, cumulatif, noteFinale) VALUES ('AE4715', '19-3', 1047004, 1, NULL, NULL);
INSERT INTO INSCRIPTION (sigle, trim, matricule, numSect, cumulatif, noteFinale) VALUES ('AE4715', '19-3', 826330, 1, NULL, NULL);
INSERT INTO INSCRIPTION (sigle, trim, matricule, numSect, cumulatif, noteFinale) VALUES ('AE4715', '19-3', 1249441, 1, NULL, NULL);
INSERT INTO INSCRIPTION (sigle, trim, matricule, numSect, cumulatif, noteFinale) VALUES ('AE4715', '19-3', 1233707, 1, NULL, NULL);

DELETE FROM INSCRIPTION WHERE TRIM = '19-3';
COMMIT;


*/

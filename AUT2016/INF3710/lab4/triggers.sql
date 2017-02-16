-----Nom D'utilisateur pour la BD : INF3710-163-21 

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

-----------------------------------------------TRIGGER_D------------------------------------------------------------------------------
DROP TRIGGER bf_ins_TRIGGER_D;
CREATE OR REPLACE TRIGGER bf_ins_TRIGGER_D
  BEFORE INSERT ON INSCRIPTION
  FOR EACH ROW
  DECLARE
    nbPreRequis INTEGER;
  BEGIN
    SELECT COUNT(*) INTO nbPreRequis FROM PREREQUIS PR
    WHERE PR.SIGLE = :NEW.SIGLE
    AND PR.LEPREREQUIS NOT IN (SELECT SIGLE FROM INSCRIPTION I
    WHERE I.MATRICULE = :NEW.MATRICULE
    AND I.TRIM <> :NEW.TRIM);

    IF (nbPreRequis > 0) THEN
      RAISE_APPLICATION_ERROR(-20010,'Vous devez poséder tous les prérequis du cours pour vous-y inscrire.');
    END IF;
  END;
------------------------------------------------------------------------------------------------------------------------------------


-------------------------------------------------TRIGGER_E--------------------------------------------------------------------------
DROP TRIGGER bf_up_ins_TRIGGER_E;
CREATE OR REPLACE TRIGGER bf_up_ins_TRIGGER_E
  BEFORE UPDATE OR INSERT ON INSCRIPTION
  FOR EACH ROW
  DECLARE
    pondera INTEGER;
    trueMean REAL;
  BEGIN
    SELECT SUM(E.PONDERATION) INTO pondera FROM EPREUVE E
    WHERE E.SIGLE = :NEW.SIGLE AND E.TRIM = :NEW.TRIM;
    IF(pondera != 100) THEN
      RAISE_APPLICATION_ERROR(-20011,'La pondération des épreuves pour le cours est érroné.');
    END IF;

    SELECT SUM((E.PONDERATION) * (N.LANOTE/100)) INTO trueMean FROM EPREUVE E, NOTE N
    WHERE E.SIGLE = :NEW.SIGLE
          AND E.TRIM = :NEW.TRIM
          AND N.IDEPR = E.IDEPR
          AND N.MATRICULE = :NEW.MATRICULE;

    IF (trueMean != :NEW.CUMULATIF) THEN
      RAISE_APPLICATION_ERROR(-20042,'La moyenne(cummulatif) entré ne correspond pas aux résultats obtenus');
    END IF;
  END;
------------------------------------------------------------------------------------------------------------------------------------

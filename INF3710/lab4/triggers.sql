DROP TRIGGER bf_up_ct_TRIGGER_A;

CREATE OR REPLACE TRIGGER bf_up_ct_TRIGGER_A
  BEFORE UPDATE OR INSERT ON COURSTRIM
  FOR EACH ROW
  DECLARE
    typpers CHAR(1);
  BEGIN
    SELECT P.TYPPERS INTO typpers FROM PERSONNE P WHERE P.NAS = :NEW.RESPONSABLE;
    IF(typpers <> 'P') THEN
      RAISE_APPLICATION_ERROR(-20100,'On ne peut pas être responsable de cours sans être professeur.');
    END IF;
  END;

----------------------------------------TEST TRIGGER A------------------------------------------------------
UPDATE  COURSTRIM
SET RESPONSABLE = 658414972
WHERE SIGLE='CP510'
      AND TRIM = '19-3';

INSERT INTO CoursTrim (sigle, trim, responsable) VALUES ('CP510', '19-3', 300456273);
DELETE FROM COURSTRIM CT WHERE CT.SIGLE = 'CP510' AND CT.TRIM = '19-3' AND CT.RESPONSABLE = 300456273;
COMMIT;
------------------------------------------------------------------------------------------------------------


DROP TRIGGER BF_UP_INS_TRIGGER_B;
CREATE OR REPLACE TRIGGER  BF_UP_INS_TRIGGER_B
  BEFORE UPDATE OR INSERT ON PERSONNE
  FOR EACH ROW
  DECLARE
    typpers CHAR(1);
  BEGIN
    typpers:= :NEW.TYPPERS;
    IF (typpers = 'P' OR typpers = 'X') THEN
      IF NOT REGEXP_LIKE (:NEW.PMATRICULE,'^p\d{3,6}$') THEN
        RAISE_APPLICATION_ERROR(-20100,'On ne peut pas être responsable de cours sans être reyeryQWWQQWrtytry.');
      END IF;
      ELSE IF (typpers = 'E') THEN
        IF NOT REGEXP_LIKE (:NEW.MATRICULE,'^\d{3,7}$') THEN
          RAISE_APPLICATION_ERROR(-20100,'On ne peut pas être responsable de cours sans être GSSDFFDSDAS.');
        END IF;
      END IF;
    END IF ;
  END;
----------------------------------------TEST TRIGGER B--------------------------------------------------------------------------------
INSERT INTO Personne (nas, nom, prenom, typPers, matricule, pmatricule) VALUES (239075522, 'Lavoie', 'Thierry', 'P', NULL, 'SSp239');
INSERT INTO Personne (nas, nom, prenom, typPers, matricule, pmatricule) VALUES (666666644, 'Lavoie', 'Thierry', 'E', NULL, '123456');
DELETE FROM PERSONNE WHERE NAS = 666666644;
DELETE FROM PERSONNE WHERE NAS = 239075522;
COMMIT;
--------------------------------------------------------------------------------------------------------------------------------------
import java.net.UnknownHostException;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import com.mongodb.client.FindIterable;
import com.mongodb.client.MongoCursor;
import com.mongodb.client.model.Sorts;
import com.mongodb.operation.BaseWriteOperation;
import org.bson.BsonDocument;
import org.bson.Document;
import org.json.simple.*;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;
import com.mongodb.*;
import com.mongodb.client.MongoDatabase;
import com.mongodb.client.MongoCollection;

public class simpleExemple {

    public static void importJsonIntoCollection(String fichier, String collection, MongoDatabase db) {
        try {
            MongoCollection<Document> coll = db.getCollection(collection);
            JSONParser parser = new JSONParser();
            JSONArray jsonarray = null;
            //Récupéation des données du fichier JSON
            jsonarray = (JSONArray) parser.parse(new FileReader(fichier));
            //Parcours du tableau pour récupérer chacun des documents et l'insérer dans la collection
            for (int i = 0; i < jsonarray.size(); i++) {
                Document doc = Document.parse(jsonarray.get(i).toString());
                coll.insertOne(doc);//Insertion dans la BD
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (ParseException e) {
            e.printStackTrace();
        } catch (NullPointerException e) {
            e.printStackTrace();
        }

    }

    //Implementation de la query a :
    //  a) Afficher la liste de tous les livres publiés depuis 2000 ;
    public static void numeroA(String collection, MongoDatabase db) {

        System.out.println("Executing query a)");
        MongoCollection<Document> coll = db.getCollection(collection);
        BasicDBObject clause1 = new BasicDBObject("year", new BasicDBObject("$gte", 2000));
        BasicDBObject clause2 = new BasicDBObject("type", "Book");
        BasicDBList and = new BasicDBList();
        and.add(clause1);
        and.add(clause2);
        BasicDBObject query = new BasicDBObject("$and", and);
        FindIterable<Document> ittr = coll.find(query);
        for (Document d : ittr) {
            System.out.println("Title : " + d.get("title") + " Type : " + d.get("type") + " Year : " + d.get("year"));
        }

    }

    //Implementation de la query b :
    //  b) Afficher la liste des publications parues depuis 2013 : le titre et le nombre de pages ;
    public static void numeroB(String collection, MongoDatabase db) {

        System.out.println("Executing query b)");
        MongoCollection<Document> coll = db.getCollection(collection);
        BasicDBObject cond1 = new BasicDBObject("year", new BasicDBObject("$gte", 2013));
        FindIterable<Document> ittr = coll.find(cond1);
        for (Document d : ittr) {
            if(d.get("pages") != null) {
                try {
                    Document p = d.get("pages", Document.class);
                    int pages = p.getInteger("end") - p.getInteger("start");
                    System.out.println("Title: " + d.get("title") + " Nombre de pages : " + pages);
                }
                catch (Exception e) {
                    System.out.println("Title: " + d.get("title") + " Nombre de pages : Inconnu de l'homme jusqu'à maintenant");
                }
            }
        }

    }

    //Implementation de la query c :
    //  c) Afficher la liste de tous les éditeurs (type ?publisher?) distincts ;
    public static void numeroC(String collection, MongoDatabase db) {

        System.out.println("Executing query c)");
        MongoCollection<Document> coll = db.getCollection(collection);
        MongoCursor<String> ittr = coll.distinct("publisher", String.class).iterator();  // <-- So long "ThisClark" and thanks for all the fish
        while (ittr.hasNext()) {
            System.out.println(ittr.next());
        }

    }

    //Implementation de la query d :
    //  d) Trier les publications de ?Ingrid Zukerman? ordonnés selon la date (le plus récent d?abord) ;
    public static void numeroD(String collection, MongoDatabase db) {

        System.out.println("Executing query d)");
        MongoCollection<Document> coll = db.getCollection(collection);
        BasicDBObject cond = new BasicDBObject();
        cond.put("authors", "Ingrid Zukerman");
        FindIterable<Document> ittr = coll.find(cond, Document.class);
        ittr.sort(Sorts.orderBy(Sorts.descending("year")));
        for (Document d : ittr) {
            System.out.println(d.get("year") + ", " + d.get("title") + " "+ d.get("authors"));
        }

    }

    //Implementation de la query e :
    //  e) Compter le nombre d?articles de ?Ingrid Zukerman? ;
    public static void numeroE(String collection, MongoDatabase db){

        System.out.println("Executing query e)");
        MongoCollection<Document> coll = db.getCollection(collection);
        BasicDBObject cond1 = new BasicDBObject("authors", "Ingrid Zukerman");
        BasicDBObject cond2 = new BasicDBObject("type", "Article");
        BasicDBList and = new BasicDBList();
        and.add(cond1);
        and.add(cond2);
        BasicDBObject query = new BasicDBObject("$and", and);
        Long count = coll.count(query);
        System.out.println("Number of article from Ingrid Zukerman: " + count);
    }

    //Implementation de la query f :
    //  f) Afficher les publications dont Ingrid Zuckerman et Fabian Bohnert sont les deux seuls auteurs ;
    public static void numeroF(String collection, MongoDatabase db){

        System.out.println("Executing query f)");
        MongoCollection<Document> coll = db.getCollection(collection);
        BasicDBObject cond1 = new BasicDBObject("authors", new BasicDBObject("$size", 2));
        BasicDBObject cond2 = new BasicDBObject("authors", "Ingrid Zukerman");
        BasicDBObject cond3 = new BasicDBObject("authors", "Fabian Bohnert");
        BasicDBList and = new BasicDBList();
        and.add(cond1);
        and.add(cond2);
        and.add(cond3);
        BasicDBObject query = new BasicDBObject("$and", and);
        FindIterable<Document> ittr = coll.find(query, Document.class);
        for (Document d : ittr) {
            System.out.println(d.get("title") + " " + d.get("authors"));
        }
    }

    //Implementation de la query g :
    //  g) Insérer un livre fictif dont vous êtes l'auteur unique ;
    public static void numeroG(String collection, MongoDatabase db){

        System.out.println("Executing query g)");
        MongoCollection<Document> coll = db.getCollection(collection);
        List<String> authors = new ArrayList<String>();
        authors.add("Kevin Pantelakis");
        List<String> isbn = new ArrayList<String>();
        isbn.add("000-1-234-42429-3");
        Document doc = new Document();
        doc.append("_id", "series/pantech/000001");
        doc.append("type", "Book");
        doc.append("editor", "Richer Archambault");
        doc.append("title", "JPMP - J'ai perdu mon papa");
        doc.append("year", "2015");
        doc.append("publisher", "CoopPoly");
        doc.append("series", "Survivre après le départ de ses parents");
        doc.append("booktitle", "JPMP");
        doc.append("url", "db/series/pantech/000002.html");
        doc.append("authors", authors);
        doc.append("isbn", isbn);
        coll.insertOne(doc);//Insertion dans la BD
    }

    //Implementation de la query h :
    //  g) Insérer un livre fictif dont vous êtes l'auteur unique ;
    public static void numeroH(String collection, MongoDatabase db){

        System.out.println("Executing query h)");
        MongoCollection<Document> coll = db.getCollection(collection);
        List<String> authors = new ArrayList<String>();
        authors.add("Kevin Pantelakis");
        authors.add("Richer Archambault");
        BasicDBObject doc1 = new BasicDBObject("_id", "series/pantech/000001");
        coll.updateOne(doc1, new Document("$set", new Document("authors", authors)));
    }

    //Insert query number (a,b,c,d,e,f) to execute the query on a collection of a Mongo Database
    public static void executeQuery(char queryNum, String collection, MongoDatabase db ){
        switch (queryNum){
            case 'a':
            case 'A':
                numeroA(collection, db);
                break;
            case 'b':
            case 'B':
                numeroB(collection, db);
                break;
            case 'c':
            case 'C':
                numeroC(collection, db);
                break;
            case 'd':
            case 'D':
                numeroD(collection, db);
                break;
            case 'e':
            case 'E':
                numeroE(collection, db);
                break;
            case 'f':
            case 'F':
                numeroF(collection, db);
                break;
            case 'g':
            case 'G':
                numeroG(collection, db);
                break;
            case 'h':
            case 'H':
                numeroH(collection, db);
                break;
        }

    }

    // Execute all queries in order on a collection of a Mongo Database
    public static void executeQueries(String collection, MongoDatabase db){

        numeroA(collection, db);
        numeroB(collection, db);
        numeroC(collection, db);
        numeroD(collection, db);
        numeroE(collection, db);
        numeroF(collection, db);
        numeroG(collection, db);
        numeroH(collection, db);

    }

    public static void connection(String dbname) {
        try {
            String uri = "mongodb://root:123@ds113678.mlab.com:13678/kevricherinf3710";
            String collection = "dblpv2";

            MongoClientURI clientUri = new MongoClientURI(uri);
            MongoClient client = new MongoClient(clientUri);
            MongoDatabase db = client.getDatabase(dbname);

            // uncomment this line to populate de collection.
            // importJsonIntoCollection("/Users/richerarc/git/poly/turbo-giggle/INF3710/lab5/materiels/dblp.json", collection, db);
            
            // Uncomment this line to execute desired query
            //executeQuery('h',collection,db);

            // uncomment this line to execute the queries  a) to f)
            executeQueries(collection,db);

            client.close();
        }
        catch (NullPointerException e) {
            e.printStackTrace();
        }

    }

    public static void main(String[] args) throws UnknownHostException {
        // TODO Auto-generated method stub
        connection("kevricherinf3710");
    }
}

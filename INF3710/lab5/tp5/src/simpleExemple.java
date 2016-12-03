import java.net.UnknownHostException;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

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
            //R�cup�ation des donn�es du fichier JSON
            jsonarray = (JSONArray) parser.parse(new FileReader(fichier));
            //Parcours du tableau pour r�cup�rer chacun des documents et l'ins�rer dans la collection
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

    public static void numeroA(String collection, MongoDatabase db) {

        System.out.println("Executing query a)");
        MongoCollection<Document> coll = db.getCollection(collection);
        BasicDBObject lol = new BasicDBObject();
        lol.put("year", new BasicDBObject("$gte", 2000));
        FindIterable<Document> ittr = coll.find(lol);
        for (Document d : ittr) {
            System.out.println("Title : " + d.get("title"));
        }

    }

    public static void numeroB(String collection, MongoDatabase db) {

        System.out.println("Executing query b)");
        MongoCollection<Document> coll = db.getCollection(collection);
        BasicDBObject cond = new BasicDBObject();
        cond.put("year", new BasicDBObject("$gte", 2013));
        FindIterable<Document> ittr = coll.find(cond);
        for (Document d : ittr) {
            if(d.get("pages") != null) {
                try {
                    Document p = d.get("pages", Document.class);
                    int pages = p.getInteger("end") - p.getInteger("start");
                    System.out.println("Title: " + d.get("title") + " Nombre de pages : " + pages);
                }
                catch (Exception e) {
                    System.out.println("Title: " + d.get("title") + " Nombre de pages : Inconnu de l'homme jusqu'� maintenant");
                }
            }
        }

    }

    public static void numeroC(String collection, MongoDatabase db) {

        System.out.println("Executing query c)");
        MongoCollection<Document> coll = db.getCollection(collection);
        MongoCursor<String> ittr = coll.distinct("publisher", String.class).iterator();  // <-- So long "ThisClark" and thanks for all the fish
        while (ittr.hasNext()) {
            System.out.println(ittr.next());
        }

    }

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

    public static void numeroE(String collection, MongoDatabase db){

        System.out.println("Executing query e)");
    }

    public static void numeroF(String collection, MongoDatabase db){

        System.out.println("Executing query f)");
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
            // executeQuery('a',collection,db);

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

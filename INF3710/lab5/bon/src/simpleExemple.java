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

    public static void numeroA(String collection, MongoDatabase db) {

        MongoCollection<Document> coll = db.getCollection(collection);
        BasicDBObject lol = new BasicDBObject();
        lol.put("year", new BasicDBObject("$gte", 2000));
        FindIterable<Document> ittr = coll.find(lol);
        for (Document d : ittr) {
            System.out.println(d);
        }

    }

    public static void numeroB(String collection, MongoDatabase db) {

        MongoCollection<Document> coll = db.getCollection(collection);
        BasicDBObject cond = new BasicDBObject();
        cond.put("year", new BasicDBObject("$gte", 2013));
        FindIterable<Document> ittr = coll.find(cond);
        for (Document d : ittr) {
            if(d.get("pages") != null) {
                try {
                    Document p = d.get("pages", Document.class);
                    int pages = p.getInteger("end") - p.getInteger("start");
                    System.out.println("Title : " + d.get("title") + "\n\tNombre de pages : " + pages + "\n");
                }
                catch (Exception e) {
                    System.out.println("Title : " + d.get("title") + "\n\tNombre de pages : Inconnu de l'homme jusqu'à maintenant\n");
                }
            }
        }

    }

    public static void numeroC(String collection, MongoDatabase db) {

        MongoCollection<Document> coll = db.getCollection(collection);
        MongoCursor<String> ittr = coll.distinct("publisher", String.class).iterator();  // <-- So long "ThisClark" and thanks for all the fish
        while (ittr.hasNext()) {
            System.out.println(ittr.next());
        }

    }

    public static void numeroD(String collection, MongoDatabase db) {

        MongoCollection<Document> coll = db.getCollection(collection);
        BasicDBObject cond = new BasicDBObject();
        cond.put("authors", "Ingrid Zukerman");
        FindIterable<Document> ittr = coll.find(cond, Document.class);
        ittr.sort(Sorts.orderBy(Sorts.descending("year")));
        for (Document d : ittr) {
            System.out.println(d);
        }

    }

    public static void connection(String dbname) {
        try {
            String uri = "mongodb://root:123@ds113678.mlab.com:13678/kevricherinf3710";
            String collection = "dblpv2";

            MongoClientURI clientUri = new MongoClientURI(uri);
            MongoClient client = new MongoClient(clientUri);
            MongoDatabase db = client.getDatabase(dbname);

            // uncomment this line to populate de collection.
            //importJsonIntoCollection("/Users/richerarc/git/poly/turbo-giggle/INF3710/lab5/materiels/dblp.json", collection, db);
            //


            // uncomment this line to execute the query for a)
            //numeroA(collection, db);

            // uncomment this line to execute the query for b)
            //numeroB(collection, db);

            // uncomment this line to execute the query for c)
            //numeroC(collection, db);


            numeroD(collection, db);


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

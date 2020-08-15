package com.example.stefano.progettomaturita;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Vector;

/**
 * Created by stefano on 25/07/16.
 */
public class Static_Gestione_File {

    //crea un nuovo file se non esiste
    public static void CreateFile(String filename){
        File f = new File(filename);
        if(!f.exists() && !f.isDirectory()) {
            try {
                f.createNewFile();
            }catch (Exception ex){

            }
        }
    }

    //recupera tutti i record salvati su un file di testo
    public static  Vector<String> GetSaved(String filename){

        Vector<String> saved=new Vector<String>();

        BufferedReader reader=null;
        try {
            reader = new BufferedReader(new FileReader(filename));
            String s= reader.readLine();
            while(s!=null){
                saved.add(s);
                s=reader.readLine();
            }
            reader.close();

        }catch(Exception e){

        }finally {
            try {
                reader.close();
            } catch (Exception e) {
            }
        }
        return saved;
    }


    //Rimuove dal file specificato tutti i record che iniziano con la stringa item
    public static void RemoveFromFile(String filename, String item){
        Vector<String> saved=GetSaved(filename);

        for(int i=0;i<saved.size();i++){
            if(saved.get(i).startsWith(item)) {
                saved.removeElementAt(i);
                i--;
            }
        }
        BufferedWriter writer = null;
        try {
            writer = new BufferedWriter(new FileWriter(filename,false));
            for(int i=0;i<saved.size();i++){
                writer.write(saved.get(i)+"\n");
            }
            writer.flush();
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                // Close the writer regardless of what happens...
                writer.close();
            } catch (Exception e) {

            }
        }
    }

    //aggiunge al file specificato  la stringa item
    public static void AppendToFile(String filename, String item){
        BufferedWriter writer = null;
        try {
            writer = new BufferedWriter(new FileWriter(filename,true));
            writer.write(item+"\n");

            writer.flush();
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                writer.close();
            }catch (IOException ex){

            }
        }
    }

    public static void EreaseFileContent(String filename){
        BufferedWriter writer = null;
        try {
            writer = new BufferedWriter(new FileWriter(filename,false));
            writer.write("");

            writer.flush();
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                writer.close();
            }catch (IOException ex){

            }
        }
    }

    public static  boolean Contains(String filename,String data)
    {
       Vector<String> supp= GetSaved(filename);
        for (int i=0;i<supp.size();i++)
            if(supp.get(i).startsWith(data))
                return  true;

        return  false;
    }

    public static String  Get(String filename,String data)
    {
        Vector<String> supp= GetSaved(filename);
        for (int i=0;i<supp.size();i++)
            if(supp.get(i).startsWith(data))
                return  supp.get(i);

        return  null;
    }

}

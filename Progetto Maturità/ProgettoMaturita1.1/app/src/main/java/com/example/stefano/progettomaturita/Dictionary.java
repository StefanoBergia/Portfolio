package com.example.stefano.progettomaturita;

import java.util.Vector;

/**
 * Created by stefano on 25/07/16.
 */

//gestisce un array ad indice stringa
public class Dictionary {

    //array contenete le chiavi
    private Vector<String> keys;

    //array contenete i valori
    private Vector< String> values;

    public Dictionary(){
        keys=new Vector<>();
        values=new Vector<>();
    }

    public void AddItem(String key,String value)
    {
        if(!keys.contains(key)) {
            keys.add(key);
            values.add(value);
        }
    }

    public void RemoveItem(String key)
    {
        if(!keys.contains(key)) {
            int pos=keys.indexOf(key);
            keys.remove(pos);
            values.remove(pos);
        }
    }

    public void RemoveItem(int pos)
    {;
        keys.remove(pos);
        values.remove(pos);
    }

    public String getItem(String key){
        if(keys.contains(key))
        {
            int pos=keys.indexOf(key);
            return values.get(pos);
        }
        return null;
    }

    public String getItemAt(int pos){
        return values.get(pos);
    }

    public String getKeyAt(int pos){
        return keys.get(pos);
    }

    public int getLength()
    {
       return keys.size();
    }
}

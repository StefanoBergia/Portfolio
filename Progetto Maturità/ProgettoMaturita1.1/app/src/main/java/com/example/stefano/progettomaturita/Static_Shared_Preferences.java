package com.example.stefano.progettomaturita;

import android.content.Context;
import android.content.SharedPreferences;
import android.preference.PreferenceManager;


//gestisce i valori condivisi tra tutte le activity dell'applicazione
public class Static_Shared_Preferences {

    public static void PutString (Context cx, String name, String item){
        SharedPreferences preferences= PreferenceManager.getDefaultSharedPreferences(cx);
        SharedPreferences.Editor editor= preferences.edit();
        try
        {
            editor.remove(name);
        }
        catch (Exception ex){}
        editor.putString(name,item);
        editor.apply();
    }

    public static String GetString (Context cx, String name){
        SharedPreferences preferences= PreferenceManager.getDefaultSharedPreferences(cx);
        String item=preferences.getString(name,"");
        return item;
    }
}
